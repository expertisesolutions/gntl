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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_SIMPLE_CONDITION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_SIMPLE_CONDITION_HPP

#include <gntl/concept/parser/connector/connector_simple_condition.hpp>

namespace gntl { namespace archetype { namespace parser {

struct connector_simple_condition
{
};

} }

namespace concept { namespace parser {

template <>
struct connector_simple_condition_traits
  <archetype::parser::connector_simple_condition>
{
    typedef archetype::parser::connector_simple_condition
      connector_simple_condition;
    typedef boost::mpl::true_ is_connector_simple_condition;
    struct role_type {};
    struct delay_type {};
    struct event_type_type {};
    struct key_type {};
    struct transition_type {};
    struct min_type {};
    struct max_type {};
    struct qualifier_type {};

    static role_type role (connector_simple_condition);
    static bool has_delay (connector_simple_condition);
    static delay_type delay (connector_simple_condition);
    static bool has_event_type (connector_simple_condition);
    static event_type_type event_type (connector_simple_condition);
    static bool has_key (connector_simple_condition);
    static key_type key (connector_simple_condition);
    static bool has_transition (connector_simple_condition);
    static transition_type transition (connector_simple_condition);
    static bool has_min (connector_simple_condition);
    static min_type min (connector_simple_condition);
    static bool has_max (connector_simple_condition);
    static max_type max (connector_simple_condition);
    static bool has_qualifier (connector_simple_condition);
    static qualifier_type qualifier (connector_simple_condition);
};

} } }

#endif
