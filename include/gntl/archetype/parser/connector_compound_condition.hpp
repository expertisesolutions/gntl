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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_CONDITION_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_CONDITION_HPP

#include <gntl/archetype/parser/connector_condition_fwd.hpp>
#include <gntl/archetype/parser/connector_condition_sequence.hpp>
#include <gntl/archetype/parser/connector_statement_sequence.hpp>
#include <gntl/archetype/parser/connector_condition_expression.hpp>
#include <gntl/concept/parser/connector/connector_compound_condition.hpp>

#include <boost/concept_archetype.hpp>
#include <boost/mpl/vector.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Statement, typename SimpleCondition>
struct connector_compound_condition
{
};

} }

namespace concept { namespace parser {

template <typename Statement, typename SimpleCondition>
struct connector_compound_condition_traits<archetype::parser
                                           ::connector_compound_condition
                                           <Statement, SimpleCondition> >
{
  typedef archetype::parser::connector_compound_condition<Statement, SimpleCondition>
    connector_compound_condition;
  typedef boost::mpl::true_ is_connector_compound_condition;
  struct operator_type {};
  struct delay_type {};
  typedef archetype::parser::connector_condition_expression
    <boost::mpl::vector<SimpleCondition, connector_compound_condition> >
    connector_condition;
  typedef boost::iterator_range<boost::input_iterator_archetype<connector_condition> >
    connector_condition_range;

  static operator_type operator_ (connector_compound_condition);
  static delay_type delay (connector_compound_condition);
  static bool has_delay (connector_compound_condition);
  static connector_condition_range connector_condition_all (connector_compound_condition);
};

} } }

#endif
