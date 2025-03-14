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

#ifndef GNTL_ALGORITHM_STRUCTURE_ACTION_DEFAULT_OPERATION_HPP
#define GNTL_ALGORITHM_STRUCTURE_ACTION_DEFAULT_OPERATION_HPP

#include <gntl/concept/structure/action/bound_simple_action.hpp>
#include <gntl/concept/structure/action/action_bound_component.hpp>
#include <gntl/algorithm/structure/document/search.hpp>
#include <gntl/algorithm/structure/action/defaults.hpp>
#include <gntl/algorithm/structure/component/lookup.hpp>
#include <gntl/algorithm/structure/component/set.hpp>
#include <gntl/algorithm/structure/component/start.hpp>
#include <gntl/algorithm/structure/component/stop.hpp>
#include <gntl/algorithm/structure/component/abort.hpp>
#include <gntl/algorithm/structure/component/pause.hpp>
#include <gntl/algorithm/structure/component/resume.hpp>
#include <gntl/algorithm/structure/switch_functor.hpp>
#include <gntl/algorithm/structure/context/register_interface.hpp>

#include <boost/ref.hpp>

#include <typeinfo>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace action {

namespace action_detail {

struct adapted_start
{
  typedef void result_type;
  template <typename Component, typename Location, typename OptionalInterface
            , typename Descriptor, typename Value, typename Document, typename Dimensions
            , typename...Args>
  result_type operator()(Component component, Location l, OptionalInterface i
                         , Descriptor descriptor, boost::optional<Value> v
                         , Document document, Dimensions screen_dimensions
                         , Args...args) const
  {
    algorithm::structure::component::start(component, l, i, descriptor, v, document
                                           , screen_dimensions, args...);
    // algorithm::structure::context::register_interface_for_component
    //   (context, component, document, gntl::transition_enum::starts
    //    , gntl::event_enum::presentation);
  }
};

struct adapted_stop
{
  typedef void result_type;
  template <typename Component, typename Location, typename OptionalInterface
            , typename Descriptor, typename Value, typename Document, typename Dimensions
            , typename...Args>
  result_type operator()(Component component, Location l, OptionalInterface i
                         , Descriptor descriptor, boost::optional<Value>, Document document
                         , Dimensions, Args...args) const
  {
    algorithm::structure::component::stop(component, descriptor, document, args...);
    // algorithm::structure::context::register_interface_for_component
    //   (context, component, document, gntl::transition_enum::stops
    //    , gntl::event_enum::presentation);
  }
};

struct adapted_pause
{
  typedef void result_type;
  template <typename Component, typename Location, typename OptionalInterface
            , typename Descriptor, typename Value, typename Document, typename Dimensions
            , typename...Args>
  result_type operator()(Component component, Location l, OptionalInterface i
                         , Descriptor descriptor, boost::optional<Value>
                         , Document document, Dimensions, Args...args) const
  {
    algorithm::structure::component::pause(component, descriptor, document, args...);
    // algorithm::structure::context::register_interface_for_component
    //   (context, component, document, gntl::transition_enum::pauses
    //    , gntl::event_enum::presentation);
  }
};

struct adapted_resume
{
  typedef void result_type;
  template <typename Component, typename Location, typename OptionalInterface
            , typename Descriptor, typename Value, typename Document, typename Dimensions
            , typename...Args>
  result_type operator()(Component component, Location l, OptionalInterface i
                         , Descriptor descriptor, boost::optional<Value>, Document document
                         , Dimensions, Args...args) const
  {
    algorithm::structure::component::resume(component, descriptor, document, args...);
    // algorithm::structure::context::register_interface_for_component
    //   (context, component, document, gntl::transition_enum::resumes
    //    , gntl::event_enum::presentation);
  }
};

struct adapted_abort
{
  typedef void result_type;
  template <typename Component, typename Location, typename OptionalInterface
            , typename Descriptor, typename Value, typename Document, typename Dimensions
            , typename...Args>
  result_type operator()(Component component, Location l, OptionalInterface
                         , Descriptor descriptor, boost::optional<Value>, Document document
                         , Dimensions, Args...args) const
  {
    algorithm::structure::component::abort(component, descriptor, document, args...);
    // algorithm::structure::context::register_interface_for_component
    //   (context, component, document, gntl::transition_enum::aborts
    //    , gntl::event_enum::presentation);
  }
};

template <typename Functor, typename Component, typename...Args>
void generic_visitor (Functor f, Component c, Args...args)
{
  f(c, args...);
}

template <typename Functor, BOOST_VARIANT_ENUM_PARAMS(typename T), typename...Args>
void generic_visitor (Functor f, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> v
                      , Args...args)
{
  boost::apply_visitor(f, gntl::unwrap_ref(v), args...);
}

template <typename Dimensions>
struct default_operation_for_concrete_component
{
  default_operation_for_concrete_component(Dimensions full_screen)
    : full_screen(full_screen) {}
  typedef void result_type;
  template <typename Component
            , typename Location
            , typename Context
            , typename OptionalInterface
            , typename Descriptor
            , typename Value
            , typename Document
            , typename BoundSimpleAction
            , typename ActionBoundComponent
            , typename...Args>
  result_type operator()(Component component
                         , Context context
                         , Location location
                         , OptionalInterface interface_
                         , Descriptor descriptor
                         , boost::optional<Value> value
                         , Document document
                         , BoundSimpleAction bound_simple_action
                         , ActionBoundComponent bound_component
                         , Args...args) const
  {
    GNTL_DEBUG_LOG("found component" << std::endl)

    typedef gntl::algorithm::structure::switch_functor
      <gntl::action_type
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::start>
              , adapted_start/*algorithm::structure::component::start_functor*/>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::stop>, adapted_stop>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::abort>, adapted_abort>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::pause>, adapted_pause>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::resume>, adapted_resume>
      >
      presentation_s;

    typedef gntl::algorithm::structure::switch_functor
      <gntl::action_type
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::start>
              , algorithm::structure::component::set_start_functor>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::stop>, adapted_stop>
      , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::abort>, adapted_abort>
      // , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::pause>, int>
      // , case_<boost::mpl::integral_c<gntl::action_type, gntl::action_enum::resume>, int>
      >
      attribution_s;

    typedef gntl::algorithm::structure::switch_functor
      <gntl::event_type
      , case_<boost::mpl::integral_c<gntl::event_type, gntl::event_enum::presentation>, presentation_s>
      // , case_<boost::mpl::integral_c<gntl::event_type, gntl::event_enum::selection>, int>
      , case_<boost::mpl::integral_c<gntl::event_type, gntl::event_enum::attribution>, attribution_s>
      >
      switch_functor;

    typedef typename boost::unwrap_reference<BoundSimpleAction>::type
      bound_simple_action_type;
    typedef typename boost::unwrap_reference<ActionBoundComponent>::type
      action_bound_component_type;
    typedef concept::structure::bound_simple_action_traits
      <bound_simple_action_type> bound_simple_action_traits;
    typedef concept::structure::action_bound_component_traits
      <action_bound_component_type> action_bound_component_traits;

    gntl::event_type ev;
    gntl::action_type ac;
    if(bound_simple_action_traits::has_event_type (bound_simple_action)
       && bound_simple_action_traits::has_action_type (bound_simple_action))
    {
      ev = bound_simple_action_traits::event_type(bound_simple_action);
      ac = bound_simple_action_traits::action_type(bound_simple_action);
    }
    else if(boost::optional<std::pair<gntl::event_type, gntl::action_type> > p
            = gntl::algorithm::structure::action::default_from_role
            <gntl::event_type, gntl::action_type>
            (bound_simple_action_traits::role(bound_simple_action)))
    {
      ev = p->first;
      ac = p->second;
    }
    else
    {
      GNTL_DEBUG_LOG("Couldn't infer event type and action type from role, nor"
                     " they were specified. Ignoring action" << std::endl)
      return;
    }
    
    switch_functor f;
    action_detail::generic_visitor(boost::bind(f, ev, ac, _1, location, interface_, descriptor
                                               , value, document, full_screen, args...)
                                   , component);
  }

  Dimensions full_screen;
};

}

template <typename BoundSimpleAction, typename ActionBoundComponent
          , typename Document, typename Context, typename ContextLocation
          , typename Dimensions, typename...Args>
void default_operation_for_component(BoundSimpleAction action
                                     , ActionBoundComponent component
                                     , Document document
                                     , Context context
                                     , ContextLocation context_location
                                     , Dimensions full_screen
                                     , Args...args)
{
  typedef typename boost::unwrap_reference<BoundSimpleAction>::type
    bound_simple_action_type;
  typedef typename boost::unwrap_reference<ActionBoundComponent>::type
    action_bound_component_type;
  typedef typename boost::unwrap_reference<ContextLocation>::type
    context_location_type;
  typedef concept::structure::bound_simple_action_traits
    <bound_simple_action_type> bound_simple_action_traits;
  typedef concept::structure::action_bound_component_traits
    <action_bound_component_type> action_bound_component_traits;
  typedef concept::structure::component_location_traits
    <context_location_type> component_location_traits;

  GNTL_DEBUG_LOG("component " << action_bound_component_traits::component(component) << std::endl)

  boost::optional<typename action_bound_component_traits::interface_type>
    interface_;
  if(action_bound_component_traits::has_interface(component))
    interface_ = action_bound_component_traits::interface_ (component);

  boost::optional<typename action_bound_component_traits::string_type>
    value;
  if(action_bound_component_traits::has_value(component))
    value = action_bound_component_traits::value (component);

  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef typename document_traits::descriptor_lookupable
    descriptor_lookupable;
  descriptor_lookupable descriptors
    = document_traits::descriptor_lookup (document);
  typedef concept::lookupable_traits<descriptor_lookupable> descriptor_lookupable_traits;
  typedef typename document_traits::descriptor_type descriptor_type;
  descriptor_type descriptor;
  if(action_bound_component_traits::has_descriptor(component))
  {
    GNTL_DEBUG_LOG("has a descriptor " << action_bound_component_traits::descriptor(component) << std::endl)
    typedef typename descriptor_lookupable_traits::result_type descriptor_lookup_type;
    descriptor_lookup_type descriptor_lookup
      = descriptor_lookupable_traits::lookup(descriptors, action_bound_component_traits::descriptor(component));
    if(descriptor_lookup != descriptor_lookupable_traits::not_found(descriptors))
    {
      GNTL_DEBUG_LOG("Found descriptor" << std::endl)
      descriptor = *descriptor_lookup;
    }
    else
      GNTL_DEBUG_LOG("Not found descriptor" << std::endl)
  }

  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename concept::structure::context_traits<context_type> context_traits;

  try
  {
    typedef typename document_traits::component_location_type component_location_type;
    component_location_type location = component_location_traits::compose
      (context_location, action_bound_component_traits::component(component));
    component::lookup(action_bound_component_traits::component(component)
                      , boost::bind(action_detail::default_operation_for_concrete_component<Dimensions>(full_screen)
                                    , _1, context, location, interface_, descriptor, value, document, action, component
                                    , args...)
                      , context_traits::media_lookup(context)
                      , context_traits::context_lookup(context)
                      , context_traits::switch_lookup(context)
                      , context_traits::port_lookup(context));
  }
  catch(structure::component::lookup_failed_error const& e)
  {
    GNTL_DEBUG_LOG("Error lookup " << __FILE__ ":" << __LINE__ << std::endl)
      GNTL_DEBUG_LOG(" component " << action_bound_component_traits::component(component)
                     << std::endl)
      GNTL_DEBUG_LOG(" context " << context_traits::identifier(context) << std::endl)
  }
}

template <typename BoundSimpleAction, typename Document, typename Context
          , typename ContextLocation, typename Dimensions, typename...Args>
void default_operation (BoundSimpleAction action, Document document, Context context
                        , ContextLocation context_location, Dimensions full_screen
                        , Args...args)
{
  GNTL_DEBUG_LOG("default_operation " << typeid(BoundSimpleAction).name() << std::endl)
  typedef typename boost::unwrap_reference<BoundSimpleAction>::type
    bound_simple_action_type;
  typedef concept::structure::bound_simple_action_traits
    <bound_simple_action_type> bound_simple_action_traits;

  typedef typename bound_simple_action_traits::component_range
    component_range;

  component_range components = bound_simple_action_traits::component_all(action);

  std::size_t size = boost::distance(components);

  std::size_t min = 1, max = 1;
  if(bound_simple_action_traits::has_min(action))
    min = bound_simple_action_traits::min(action)?*bound_simple_action_traits::min(action)
      :(std::numeric_limits<std::size_t>::max)();
  if(size < min)
  {
    GNTL_DEBUG_LOG("Components bound(" << size << ") are less than the minimum allowed(" << min << ")");
    return; // should we throw?
  }

  if(bound_simple_action_traits::has_max(action))
    max = bound_simple_action_traits::max(action)?*bound_simple_action_traits::max(action)
      :(std::numeric_limits<std::size_t>::max)();
  if(size > max)
  {
    GNTL_DEBUG_LOG("Components bound(" << size << ") are more than the maximum allowed(" << max << ")");
    return; // should we throw?
  }

  if(min > max)
  {
    GNTL_DEBUG_LOG("Minimum components allowed(" << min << ") are more than the maximum allowed(" << max << ")");
    return;
  }

  for(typename boost::range_iterator<component_range>::type 
        Iter = boost::begin(components)
        , EndIter = boost::end(components)
        ;Iter != EndIter
        ;++Iter)
  {
    default_operation_for_component(action, *Iter, document, context, context_location
                                    , full_screen, args...);
  }
}

struct default_operation_functor
{
  typedef void result_type;
  template <typename BoundSimpleAction, typename Document, typename Context
            , typename ContextLocation, typename Dimensions
            , typename...Args>
  result_type operator()(BoundSimpleAction action, Document document, Context context
                         , ContextLocation context_location, Dimensions full_screen
                         , Args...args) const
  {
    default_operation(action, document, context, context_location, full_screen, args...);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif

