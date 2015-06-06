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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_ACTION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_ACTION_HPP

#include <gntl/archetype/parser/connector_action_fwd.hpp>
#include <gntl/concept/parser/connector/connector_compound_action.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename SimpleAction>
struct connector_compound_action
{};

} }

namespace concept { namespace parser {

template <typename SimpleAction>
struct connector_compound_action_traits<archetype::parser
                                        ::connector_compound_action<SimpleAction> >
{
  typedef boost::mpl::true_ is_connector_compound_action;
  typedef archetype::parser::connector_compound_action<SimpleAction>
    connector_compound_action;
  typedef archetype::parser::connector_action
    <SimpleAction, connector_compound_action>
    connector_action;
  typedef boost::iterator_range<boost::input_iterator_archetype<connector_action> >
    connector_action_range;

  static connector_action_range connector_action_all(connector_compound_action);
};

} } }

#endif
