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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_STATEMENT_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_COMPOUND_STATEMENT_HPP

#include <gntl/archetype/parser/connector_statement.hpp>
#include <gntl/archetype/parser/connector_statement_sequence.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename AssessmentStatement>
struct connector_compound_statement
  : connector_statement_sequence
    <
      connector_statement
      <
        AssessmentStatement, connector_compound_statement<AssessmentStatement>
      >
    >
{
};

} }

namespace concept { namespace parser {

template <typename AssessmentStatement>
struct connector_compound_statement_traits<archetype::parser
                                           ::connector_compound_statement<AssessmentStatement> >
{
  typedef boost::mpl::true_ is_connector_compound_statement;
  struct operator_type {};
  struct is_negated_type {};
  typedef archetype::parser::connector_compound_statement<AssessmentStatement>
    compound_statement;

  static operator_type operator_(compound_statement);
  static bool has_is_negated(compound_statement);
  static is_negated_type is_negated(compound_statement);
};

} } }

#endif
