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

#ifndef GNTL_ALGORITHM_STRUCTURE_LINK_SET_CONDITION_HPP
#define GNTL_ALGORITHM_STRUCTURE_LINK_SET_CONDITION_HPP

#include <gntl/algorithm/structure/condition/set_matching_conditions.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace link {

template <typename Link, typename ComponentIdentifier, typename OptionalInterface
          , typename EventType, typename Transition>
void set_condition(Link link, ComponentIdentifier component
                   , OptionalInterface interface, Transition transition
                   , EventType event)
{
  bool b 
    = algorithm::structure::condition::set_matching_conditions
    (concept::structure::link_traits<typename unwrap_parameter<Link>::type>::condition_expression(link)
     , component, interface, event, transition);
  GNTL_DEBUG_LOG("set_condition: " << b << std::endl)
  (void)b;  // silence warning in clang 2.9
}

template <typename Link, typename Key, typename Context, typename EventType
          , typename Transition>
void set_key_select_condition(Link link, Key key, Context context, Transition transition
                              , EventType event)
{
  bool b 
    = algorithm::structure::condition::set_key_matching_conditions
    (concept::structure::link_traits<typename unwrap_parameter<Link>::type>::condition_expression(link)
     , key, context, event, transition);
  (void)b;
  GNTL_DEBUG_LOG("set_key_condition: " << b << std::endl)
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
