/* (c) Copyright 2011-2014 Felipe Magno de Almeida
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_EVALUATE_LINKS_IPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_EVALUATE_LINKS_IPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/algorithm/structure/switch/evaluate_links.hpp>
#include <gntl/algorithm/structure/link/set_condition.hpp>
#include <gntl/algorithm/structure/link/evaluate.hpp>
#include <gntl/algorithm/structure/action.hpp>
#include <gntl/algorithm/structure/action/default_operation.hpp>
#include <gntl/algorithm/structure/condition/reset_condition.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

namespace context_detail {

struct set_condition
{
  typedef void result_type;
  template <typename Link, typename ComponentIdentifier
            , typename OptionalInterface>
  result_type operator()(Link link, ComponentIdentifier component
                         , OptionalInterface interface_
                         , gntl::transition_type transition
                         , gntl::event_type event) const
  {
    algorithm::structure::link
      ::set_condition(link, component, interface_, transition, event);
  }
};

struct set_key_select_condition
{
  typedef void result_type;
  template <typename Link, typename Key, typename Context>
  result_type operator()(Link link, Key key, Context context
                         , gntl::transition_type transition
                         , gntl::event_type event) const
  {
    algorithm::structure::link
      ::set_key_select_condition(link, key, context, transition, event);
  }
};

struct execute_action
{
  typedef void result_type;
  template <typename Action, typename Document, typename Context
            , typename ContextLocation, typename Dimensions>
  result_type operator()(Action action, Document document, Context context
                         , ContextLocation context_location, Dimensions full_screen) const
  {
    structure::action::execute(action
                               , boost::bind
                               (structure::action::default_operation_functor()
                                , _1, document, context, context_location
                                , full_screen));
  }
};

struct evaluate
{
  typedef void result_type;
  template <typename Link, typename Document, typename Context
            , typename ContextLocation, typename Dimensions>
  result_type operator()(Link link, Document document, Context context
                         , ContextLocation context_location, Dimensions full_screen) const
  {
    if(link::evaluate(link, document, context))
    {
      typedef typename unwrap_parameter<Link>::type link_type;
      typedef concept::structure::link_traits<link_type> link_traits;
      GNTL_DEBUG_LOG("evaluate true" << std::endl)
      gntl::algorithm::structure::condition
        ::reset_condition(link_traits::condition_expression(link));
      structure::action::execute (link_traits::action_expression(link)
                                  , boost::bind
                                  (execute_action()
                                   , _1, document, context, context_location, full_screen)
                                  );
    }
  }
};

}

template <typename Context, typename ContextLocation, typename Document, typename Event, typename Dimensions>
void evaluate_links(Context context, ContextLocation context_location
                    , Document document, Event event, Dimensions screen_dimensions)
{
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef concept::structure::context_traits<context_type> context_traits;
  if(context_traits::is_presentation_occurring(context))
  {
    GNTL_DEBUG_LOG("context " << context_traits::identifier(context) << " is occurring "
                   "(links: " << boost::distance(context_traits::link_all(context)) << ")" << std::endl)
    gntl::range::for_each(context_traits::link_all(context)
                          , boost::bind(context_detail::set_condition()
                                        , _1, event.component_identifier
                                        , event.interface_
                                        , event.transition, event.event_));

    gntl::range::for_each(context_traits::link_all(context)
                          , boost::bind(context_detail::evaluate()
                                        , _1, document, context, context_location
                                        , screen_dimensions));

    typedef typename context_traits::context_range context_value_range;
    context_value_range contexts = context_traits::context_all(context);
    typedef typename unwrap_parameter<context_value_range>::type context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;
    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last; ++first)
    {
      context::evaluate_links(gntl::ref_once(*first), context_location
                              , document, event, screen_dimensions);
    }

  //   typedef typename context_traits::switch_range switch_value_range;
  //   switch_value_range switches = context_traits::switch_all(context);
  //   typedef typename unwrap_parameter<switch_value_range>::type switch_range;
  //   typedef typename boost::range_iterator<switch_range>::type switch_iterator;
  //   for(switch_iterator first = boost::begin(switches), last = boost::end(switches)
  //         ;first != last;++first)
  //   {
  //     switch_::evaluate_links(gntl::ref_once(*first), document, event, screen_dimensions);
  //   }
  }
  else
    GNTL_DEBUG_LOG("context " << context_traits::identifier(context) << " is sleeping" << std::endl)
}

template <typename Context, typename ContextLocation, typename Document
          , typename Key, typename Dimensions>
void evaluate_select_links(Context context, ContextLocation context_location
                           , Document document, Key key, Dimensions screen_dimensions)
{
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef concept::structure::context_traits<context_type> context_traits;
  if(context_traits::is_presentation_occurring(context))
  {
    GNTL_DEBUG_LOG("context " << context_traits::identifier(context) << " is occurring" << std::endl)
    gntl::range::for_each(context_traits::link_all(context)
                          , boost::bind(context_detail::set_key_select_condition()
                                        , _1, key, context
                                        , gntl::transition_enum::starts
                                        , gntl::event_enum::selection));

    gntl::range::for_each(context_traits::link_all(context)
                          , boost::bind(context_detail::evaluate()
                                        , _1, document, context, context_location
                                        , screen_dimensions));

    typedef typename context_traits::context_range context_value_range;
    context_value_range contexts = context_traits::context_all(context);
    typedef typename unwrap_parameter<context_value_range>::type context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;
    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last; ++first)
    {
      context::evaluate_select_links(gntl::ref_once(*first)
                                     , context_location, document, key, screen_dimensions);
    }

    // typedef typename context_traits::switch_range switch_value_range;
    // switch_value_range switches = context_traits::switch_all(context);
    // typedef typename unwrap_parameter<switch_value_range>::type switch_range;
    // typedef typename boost::range_iterator<switch_range>::type switch_iterator;
    // for(switch_iterator first = boost::begin(switches), last = boost::end(switches)
    //       ;first != last;++first)
    // {
    //   //switch_::evaluate_links(*first, document, event, screen_dimensions);
    // }
    
  }  
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
