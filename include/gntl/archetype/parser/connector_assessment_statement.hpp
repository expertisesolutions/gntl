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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_ASSESSMENT_STATEMENT_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_ASSESSMENT_STATEMENT_HPP

#include <gntl/concept/parser/connector/connector_assessment_statement.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename AttributeAssessment, typename Assessment>
struct connector_assessment_statement
{
};

} }

namespace concept { namespace parser {

template <typename AttributeAssessment, typename Assessment>
struct connector_assessment_statement_traits<archetype::parser
                                             ::connector_assessment_statement
                                             <AttributeAssessment, Assessment> >
{
  typedef archetype::parser
    ::connector_assessment_statement
    <AttributeAssessment, Assessment>
    connector_assessment_statement;
  typedef boost::mpl::true_ is_connector_assessment_statement;
  struct comparator_type {};
  typedef AttributeAssessment attribute_assessment_type;
  typedef Assessment assessment_type;
  
  static attribute_assessment_type first (connector_assessment_statement);
  static assessment_type second (connector_assessment_statement);
  static comparator_type comparator (connector_assessment_statement);
};

} } }

#endif
