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

#ifndef GNTL_ARCHETYPE_PARSER_CAUSAL_CONNECTOR_HPP
#define GNTL_ARCHETYPE_PARSER_CAUSAL_CONNECTOR_HPP

#include <gntl/concept/parser/connector/causal_connector.hpp>
#include <gntl/archetype/parser/connector_condition_expression.hpp>
#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Condition, typename Action, typename Parameter>
struct causal_connector
{
};

} }

namespace concept { namespace parser {

template <typename Condition, typename Action, typename Parameter>
struct causal_connector_traits<archetype::parser
                               ::causal_connector<Condition, Action, Parameter> >
{
  typedef boost::mpl::true_ is_causal_connector;
  typedef archetype::parser
    ::causal_connector<Condition, Action, Parameter> causal_connector;
  struct identifier_type {};
  typedef Condition condition_type;
  typedef Action action_type;
  typedef boost::input_iterator_archetype<Parameter>
    connector_parameter_iterator;
  typedef Parameter connector_parameter_type;

  static identifier_type identifier(causal_connector);
  static condition_type condition(causal_connector);
  static action_type action(causal_connector);
};

} } }

#endif
