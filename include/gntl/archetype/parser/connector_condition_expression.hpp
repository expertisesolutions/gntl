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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_EXPRESSION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_EXPRESSION_HPP

#include <gntl/concept/parser/connector/connector_condition_expression.hpp>
#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Sequence>
struct connector_condition_expression
{};

} }

namespace concept { namespace parser {

template <typename Sequence>
struct connector_condition_expression_traits
  <archetype::parser::connector_condition_expression<Sequence> >
{
  typedef archetype::parser::connector_condition_expression<Sequence>
    connector_condition_expression;
  typedef Sequence condition_list_type;
  typedef boost::mpl::true_ is_connector_condition_expression;

  template <typename T>
  static T get(connector_condition_expression);
  template <typename T>
  static bool is_type(connector_condition_expression);
};

} } }

#endif
