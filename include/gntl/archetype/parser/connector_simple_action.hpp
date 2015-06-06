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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_SIMPLE_ACTION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_SIMPLE_ACTION_HPP

#include <gntl/concept/parser/connector/connector_simple_action.hpp>

namespace gntl { namespace archetype { namespace parser {

struct connector_simple_action
{};

} }

namespace concept { namespace parser {

template <>
struct connector_simple_action_traits<archetype::parser
                                      ::connector_simple_action>
{
  typedef boost::mpl::true_ is_connector_simple_action;
  typedef archetype::parser::connector_simple_action
    connector_simple_action;

  struct role_type {};
  struct delay_type {};
  struct event_type_type {};
  struct action_type_type {};
  struct string_type {};
  struct min_type {};
  struct max_type {};
  struct qualifier_type {};
  struct repeat_type {};
  struct repeat_delay_type {};
  struct duration_type {};
  struct by_type {};

  static bool has_delay(connector_simple_action a);
  static bool has_event_type(connector_simple_action a);
  static bool has_action_type(connector_simple_action a);
  static bool has_value(connector_simple_action a);
  static bool has_min(connector_simple_action a);
  static bool has_max(connector_simple_action a);
  static bool has_qualifier(connector_simple_action a);
  static bool has_repeat(connector_simple_action a);
  static bool has_repeat_delay(connector_simple_action a);
  static bool has_duration(connector_simple_action a);
  static bool has_by(connector_simple_action a);
  static role_type role(connector_simple_action a);
  static delay_type delay(connector_simple_action a);
  static event_type_type event_type(connector_simple_action a);
  static action_type_type action_type(connector_simple_action a);
  static string_type value(connector_simple_action a);
  static min_type min(connector_simple_action a);
  static max_type max(connector_simple_action a);
  static qualifier_type qualifier(connector_simple_action a);
  static repeat_type repeat(connector_simple_action a);
  static repeat_delay_type repeat_delay(connector_simple_action a);
  static duration_type duration(connector_simple_action a);
  static by_type by(connector_simple_action a);
};

} } }

#endif
