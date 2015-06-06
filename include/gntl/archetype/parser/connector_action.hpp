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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_ACTION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_ACTION_HPP

#include <gntl/concept/parser/connector/connector_action.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename SimpleAction, typename CompoundAction>
struct connector_action
{};

} }

namespace concept { namespace parser {

template <typename SimpleAction, typename CompoundAction>
struct connector_action_traits<archetype::parser
                               ::connector_action<SimpleAction, CompoundAction> >
{
  typedef boost::mpl::true_ is_connector_action;
  typedef archetype::parser
    ::connector_action<SimpleAction, CompoundAction>
    connector_action;
  typedef SimpleAction simple_action_type;
  typedef CompoundAction compound_action_type;

  static bool is_compound(connector_action);
  static SimpleAction simple_action(connector_action);
  static CompoundAction compound_action(connector_action);
};

} } }

#endif
