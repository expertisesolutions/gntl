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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_SET_MATCHING_CONDITIONS_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_SET_MATCHING_CONDITIONS_HPP

#include <gntl/algorithm/structure/condition/contains_matches.hpp>
#include <gntl/algorithm/structure/component/is_occurring.hpp>
#include <gntl/algorithm/structure/component/lookup.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

namespace condition_detail {

template <typename ComponentId>
struct component_predicate
{
  component_predicate(ComponentId component_id)
    : component_id(component_id) {}

  typedef bool result_type;
  template <typename BoundComponent>
  bool operator()(BoundComponent c) const
  {
    typedef typename boost::unwrap_reference<BoundComponent>::type
      bound_component;
    typedef typename concept::structure::condition_bound_component_traits
      <bound_component> traits;
    return traits::component(c) == component_id;
  }

  ComponentId component_id;
};

template <typename Component, typename OptionalInterface
          , typename EventType, typename Transition>
struct set_matching_conditions_predicate
{
  set_matching_conditions_predicate (Component component
                                     , OptionalInterface interface_
                                     , EventType event_type
                                     , Transition transition)
    : component(component), interface_(interface_)
    , event_type(event_type), transition(transition) {}

  typedef bool result_type;
  template <typename SimpleCondition>
  result_type operator()(SimpleCondition c) const
  {
    typedef concept::structure::bounded_simple_condition_traits
      <SimpleCondition> traits;
    typedef typename traits::component_range component_range;
    component_range components = traits::components(c);
    typename boost::range_iterator<component_range>::type
      iterator = gntl::range::find_if(components, component_predicate<Component>(component));
    typedef typename boost::range_value<component_range>::type
      component_type;
    typedef concept::structure::condition_bound_component_traits
      <component_type> component_traits;
    bool r = (iterator != boost::end(components)
              && (!component_traits::has_interface(*iterator) && !interface_
                  ? true
                  : (
                     component_traits::has_interface(*iterator) && interface_
                     ? component_traits::interface_ (*iterator) == *interface_
                     : false
                    )
                  )
              && event_transition_compare (c, event_type, transition));
    if(r)
    {
      GNTL_DEBUG_LOG("setting component condition" << std::endl)
      component_type component = *iterator;
      component_traits::set(component);
    }
    return r;
  }

  Component component;
  OptionalInterface interface_;
  EventType event_type;
  Transition transition;
};

struct is_occurring
{
  typedef bool result_type;
  template <typename Component>
  result_type operator()(Component component) const
  {
    return algorithm::structure::component::is_occurring(component);
  }
};

template <typename Key, typename Context, typename EventType, typename Transition>
struct set_key_matching_conditions_predicate
{
  set_key_matching_conditions_predicate(Key k, Context c, EventType e, Transition t)
    : k(k), context(c), e(e), t(t) {}

  typedef bool result_type;
  template <typename SimpleCondition>
  result_type operator()(SimpleCondition c) const
  {
    GNTL_DEBUG_LOG("set_key_matching_conditions_predicate::operator()" << std::endl)
    typedef concept::structure::bounded_simple_condition_traits
      <SimpleCondition> traits;
    typedef typename traits::component_range component_range;
    component_range components = traits::components(c);
    typedef typename boost::range_iterator<component_range>::type component_iterator;
    if(event_transition_compare (c, e, t))
    {
      GNTL_DEBUG_LOG("compares equal" << std::endl)
      for(component_iterator first = boost::begin(components)
            , last = boost::end(components);first != last; ++first)
      {
        typedef typename boost::range_value<component_range>::type component_type;
        typedef concept::structure::condition_bound_component_traits<component_type>
          component_traits;
        GNTL_DEBUG_LOG("component " << component_traits::component(*first) << std::endl)
        if(component_traits::has_key(*first))
          GNTL_DEBUG_LOG("key " << component_traits::key(*first) << std::endl)
        else
          GNTL_DEBUG_LOG("key [no-key]" << std::endl)
        if(!component_traits::has_interface(*first)
           && component_traits::has_key(*first)
           && component_traits::key(*first) == k)
        {
          GNTL_DEBUG_LOG("Component has key" << std::endl)

          typedef typename unwrap_parameter<Context>::type context_type;
          typedef concept::structure::context_traits<context_type> context_traits;

          // if started
          try
          {
            if(algorithm::structure::component::lookup
               (component_traits::component(*first)
                , condition_detail::is_occurring()
                , context_traits::media_lookup(context)
                , context_traits::context_lookup(context)
                , context_traits::switch_lookup(context)))
            {
              GNTL_DEBUG_LOG("is occurring" << std::endl)
              component_type component = *first;
              component_traits::set(component);
            }
          }
          catch(algorithm::structure::component::lookup_failed_error& e)
          {
            GNTL_DEBUG_LOG("Error lookup " << __LINE__ << std::endl)
          }
        }
      }
    }
    return false;
  }

  Key k;
  Context context;
  EventType e;
  Transition t;
};

}

template <typename Condition, typename Component, typename OptionalInterface
          , typename EventType, typename Transition>
bool set_matching_conditions (Condition c, Component component, OptionalInterface interface_
                              , EventType event_type, Transition transition)
{
  return contains_matching_condition
    (c
     , condition_detail::set_matching_conditions_predicate
       <Component, OptionalInterface, EventType, Transition>
       (component, interface_, event_type, transition));
}

template <typename Condition, typename Key, typename Context, typename EventType
          , typename Transition>
bool set_key_matching_conditions (Condition c, Key key, Context context
                                  , EventType event_type, Transition transition)
{
  return contains_matching_condition
    (c
     , condition_detail::set_key_matching_conditions_predicate
     <Key, Context, EventType, Transition>
     (key, context, event_type, transition));
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
