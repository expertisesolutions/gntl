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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_STATEMENT_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_STATEMENT_HPP

#include <gntl/concept/parser/connector/connector_statement.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename AssessmentStatement, typename CompoundStatement>
struct connector_statement
{
    typedef AssessmentStatement assessment_statement_type;
    typedef CompoundStatement compound_statement_type;
};

} }

namespace concept { namespace parser {

template <typename AssessmentStatement, typename CompoundStatement>
struct connector_statement_traits<archetype::parser::connector_statement
                                  <AssessmentStatement, CompoundStatement> >
{
  typedef archetype::parser::connector_statement<AssessmentStatement
                                                 , CompoundStatement>
    connector_statement;
  typedef boost::mpl::true_ is_connector_statement;
  typedef typename connector_statement::assessment_statement_type
    assessment_statement_type;
  typedef typename connector_statement::compound_statement_type
    compound_statement_type;

  static bool is_compound(connector_statement);
  static assessment_statement_type assessment_statement(connector_statement);
  static compound_statement_type compound_statement(connector_statement);
};

} } }

#endif
