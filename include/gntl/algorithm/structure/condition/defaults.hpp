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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_DEFAULTS_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_DEFAULTS_HPP

#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/event_enum.hpp>
#include <gntl/transition_enum.hpp>

#include <utility>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

template <typename EventType, typename Transition, typename Role>
boost::optional<std::pair<EventType, Transition> >
default_from_role(Role r)
{
  if(r == "onBegin")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::transition_enum::starts);
  else if(r == "onEnd")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::transition_enum::stops);
  else if(r == "onAbort")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::transition_enum::aborts);
  else if(r == "onPause")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::transition_enum::pauses);
  else if(r == "onResume")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::transition_enum::resumes);
  else if(r == "onSelection")
    return std::make_pair(gntl::event_enum::selection
                          , gntl::transition_enum::starts);
  else if(r == "onBeginAttribution")
    return std::make_pair(gntl::event_enum::attribution
                          , gntl::transition_enum::starts);
  else if(r == "onEndAttribution")
    return std::make_pair(gntl::event_enum::attribution
                          , gntl::transition_enum::stops);
  else
    return boost::none;
}

template <typename EventType, typename Transition>
boost::optional<const char*> role_from_event_transition(EventType e, Transition t)
{
  switch(e)
  {
  case gntl::event_enum::presentation:
    switch(t)
    {
    case gntl::transition_enum::starts:
      return "onBegin";
    case gntl::transition_enum::stops:
      return "onEnd";
    case gntl::transition_enum::aborts:
      return "onAbort";
    case gntl::transition_enum::pauses:
      return "onPause";
    case gntl::transition_enum::resumes:
      return "onResume";
    default:
      break;
    }
    break;
  case gntl::event_enum::selection:
    if(t == gntl::transition_enum::starts)
      return "onSelection";
    break;
  case gntl::event_enum::attribution:
    switch(t)
    {
    case gntl::transition_enum::starts:
      return "onBeginAttribution";
    case gntl::transition_enum::stops:
      return "onEndAttribution";
    default:
      break;
    }
  default:
    break;
  }
  return boost::none;
}

template <typename SimpleCondition, typename EventType, typename Transition>
bool event_transition_compare(SimpleCondition c, EventType event_type, Transition transition)
{
  typedef concept::structure::bounded_simple_condition_traits
    <SimpleCondition> traits;
  
  bool has_event = traits::has_event_type(c)
    , has_transition = traits::has_transition(c);
  if(has_event && has_transition)
    return traits::event_type(c) == event_type
      && traits::transition(c) == transition;
  else if(!has_event && !has_transition)
  {
    GNTL_DEBUG_LOG("comparing " << traits::role(c)
              << " with event_type " << event_type
                   << " and transition " << transition << std::endl)
    // defaults by role
    boost::optional<const char*> role = role_from_event_transition
      (event_type, transition);
    if(role)
      return traits::role(c) == *role;
  }
  return false;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif

