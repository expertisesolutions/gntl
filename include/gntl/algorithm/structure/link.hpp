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

#ifndef GNTL_ALGORITHM_STRUCTURE_LINK_HPP
#define GNTL_ALGORITHM_STRUCTURE_LINK_HPP

#include <gntl/parameter.hpp>
#include <gntl/algorithm/parser/link.hpp>
#include <gntl/algorithm/structure/link/evaluate.hpp>
#include <gntl/algorithm/structure/condition.hpp>
#include <gntl/algorithm/structure/condition/set_matching_conditions.hpp>
#include <gntl/algorithm/structure/condition/evaluate_bound_simple_condition.hpp>
#include <gntl/algorithm/structure/condition/evaluate_assessment_statement.hpp>
#include <gntl/algorithm/structure/condition/reset_condition.hpp>
#include <gntl/algorithm/structure/action.hpp>
#include <gntl/algorithm/structure/action/default_operation.hpp>
#include <gntl/concept/structure/link.hpp>
#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/condition/bound_assessment_statement.hpp>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace link {

template <typename Context, typename Key>
struct key_selection_condition_predicate
{
  key_selection_condition_predicate(Context context, Key key)
    : context(context), key(key) {}

  typedef bool result_type;
  template <typename BoundCondition>
  result_type operator()(BoundCondition condition) const
  {
    GNTL_DEBUG_LOG("Should check if condition is a selection for key" << std::endl)
    typedef typename unwrap_parameter<BoundCondition>::type bound_condition_type;
    typedef concept::structure::bounded_simple_condition_traits
      <bound_condition_type> traits;

    gntl::event_type ev;
    gntl::transition_type tc;
    if(traits::has_event_type (condition) && traits::has_transition (condition))
    {
      ev = traits::event_type(condition);
      tc = traits::transition(condition);
    }
    else if(boost::optional<std::pair<gntl::event_type, gntl::transition_type> > p
            = gntl::algorithm::structure::condition::default_from_role
            <gntl::event_type, gntl::transition_type>(traits::role(condition)))
    {
      ev = p->first;
      tc = p->second;
    }
    else
    {
      GNTL_DEBUG_LOG("Couldn't find what transition and event type this condition is to" << std::endl)
      return false;
    }

    if (ev == gntl::event_enum::selection && tc == gntl::transition_enum::starts)
    {
      GNTL_DEBUG_LOG("is selection, looking for key in components" << std::endl)
      typedef typename traits::component_range component_range;
      component_range components = traits::components(condition);
      for(typename boost::range_iterator<component_range>::type
            Iter = boost::begin(components)
            , EndIter = boost::end(components)
            ;Iter != EndIter
            ;++Iter)
      {
        typedef typename boost::range_value<component_range>::type
          component_type;
        typedef concept::structure::condition_bound_component_traits
          <component_type> component_traits;
        // if media is occurring
        typedef typename component_traits::component_type media_identifier_type;
        media_identifier_type media_id = component_traits::component(*Iter);
        GNTL_DEBUG_LOG("should check if media " << media_id << " is occurring" << std::endl)

        bool occurring = false;
        typedef typename unwrap_parameter<Context>::type context_type;
        typedef concept::structure::context_traits<context_type> context_traits;
        typedef typename context_traits::media_const_range media_range;
        typedef typename context_traits::media_range mutable_media_range;
        typedef typename boost::range_value<mutable_media_range>::type mutable_media_type;
        media_range medias = context_traits::media_all(context);
        for(typename boost::range_iterator<media_range>::type
              first = boost::begin(medias)
              , last = boost::end(medias)
              ;!occurring && first != last;++first)
        {
          typedef typename boost::range_value<media_range>::type media_value_type;
          typedef typename unwrap_parameter<media_value_type>::type media_type;
          typedef concept::structure::media_traits<media_type> media_traits;
          if(concept::identifier(*first) == media_id)
          {
            typedef typename media_traits::presentation_range presentation_range;
            presentation_range presentations = media_traits::presentation_all
              (const_cast<mutable_media_type&>(*first));
            for(typename boost::range_iterator<presentation_range>::type
                  first = boost::begin(presentations), last = boost::end(presentations)
                  ;!occurring && first != last;++first)
            {
              typedef typename boost::range_value<presentation_range>::type presentation_value_type;
              typedef typename unwrap_parameter<presentation_value_type>::type presentation_type;
              typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
              if(presentation_traits::is_occurring(*first))
                occurring = true;
            }
          }
        }
        
        if(occurring)
        {
          if(component_traits::has_key(*Iter) && component_traits::key(*Iter) == key)
          {
            GNTL_DEBUG_LOG("key matches" << std::endl)
            component_type component = *Iter;
            component_traits::set(component);
            return true;
          }
          else
            GNTL_DEBUG_LOG("key doesn't match" << std::endl)
        }
      }
    }
    return false;
  }

  Context context;
  Key key;
};

template <typename Key, typename Context, typename UnaryFunction>
struct if_key_selection_link
{
  if_key_selection_link (Key key, Context context, UnaryFunction f)
    : key(key), context(context), f(f) {}

  typedef void result_type;
  template <typename Link>
  result_type operator()(Link link) const
  {
    GNTL_DEBUG_LOG("should check if link contains condition for key selection" << std::endl)
    if(structure::condition::contains_matching_condition
       (concept::structure::link_traits<Link>::condition_expression(link)
        , key_selection_condition_predicate<Context, Key>(context, key)))
      f(link);
  }

  Key key;
  Context context;
  UnaryFunction f;
};

template <typename UnaryFunction, typename Context, typename Key>
void for_each_key_selection_link (Context c, Key key, UnaryFunction f = UnaryFunction())
{
  if_key_selection_link<Key, Context, UnaryFunction>
    p(key, c, f);
  for_each_link(c, p);
}

struct for_each_key_selection_link_functor
{
  typedef void result_type;
  template <typename UnaryFunction, typename Context, typename Key>
  result_type operator()(Context c, Key key, UnaryFunction f = UnaryFunction()) const
  {
    for_each_key_selection_link (c, key, f);
  }
};


template <typename Link, typename Document, typename Context
          , typename Function>
void execute_if_evaluate (Link link, Document document, Context context, Function f)
{
  GNTL_DEBUG_LOG("evaluating" << std::endl)
  typedef typename unwrap_parameter<Link>::type structure_link;
  typedef gntl::concept::structure::link_traits <structure_link> link_traits;
  if(gntl::algorithm::structure::condition
     ::evaluate(link_traits::condition_expression(link)
                , boost::bind(link_detail::evaluate_bound_simple_condition_functor(), _1
                              , document, context)))
  {
    gntl::algorithm::structure::condition
      ::reset_condition(link_traits::condition_expression(link));
    GNTL_DEBUG_LOG("evaluation returns true" << std::endl)
    f(link, document, context);
  }
}

struct execute_if_evaluate_functor
{
  typedef void result_type;
  template <typename Link, typename Document, typename Context, typename Function>
  void operator()(Link link, Document document, Context context, Function f) const
  {
    return execute_if_evaluate(link, document, context, f);
  }
};

struct execute_action
{
  typedef void result_type;
  template <typename Action, typename Document, typename Context, typename ContextLocation
            , typename Dimensions>
  void operator()(Action action, Document document, Context context
                  , ContextLocation context_location, Dimensions full_screen) const
  {
    structure::action::execute (action
                                , boost::bind
                                  (structure::action::default_operation_functor ()
                                   , _1, document, context, context_location, full_screen));
  }
};

template <typename Link, typename Document, typename Context, typename Dimensions>
void execute_link(Link l, Document document, Context context, Dimensions full_screen)
{
  GNTL_DEBUG_LOG("execute_link" << std::endl)
  typedef typename unwrap_parameter<Link>::type link_type;
  typedef gntl::concept::structure::link_traits<link_type> link_traits;
  gntl::algorithm::structure::action::execute
    (link_traits::action_expression(l), boost::bind(execute_action(), _1, document, context
                                                    , full_screen));
}

struct execute_link_functor
{
  typedef void result_type;
  template <typename Link, typename Document, typename Context, typename Dimensions>
  void operator()(Link l, Document document, Context context, Dimensions full_screen) const
  {
    GNTL_DEBUG_LOG("execute_link_functor::operator()" << std::endl)
    link::execute_link(l, document, context, full_screen);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
