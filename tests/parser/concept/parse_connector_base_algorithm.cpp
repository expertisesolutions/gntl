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

#include <gntl/archetype/parser/connector_condition_expression.hpp>
#include <gntl/archetype/parser/connector_statement.hpp>
#include <gntl/archetype/parser/connector_assessment_statement.hpp>
#include <gntl/archetype/parser/connector_compound_statement.hpp>
#include <gntl/archetype/parser/connector_attribute_assessment.hpp>
#include <gntl/archetype/parser/connector_value_assessment.hpp>
#include <gntl/archetype/parser/connector_assessment.hpp>
#include <gntl/archetype/parser/connector_simple_condition.hpp>
#include <gntl/archetype/parser/connector_compound_condition.hpp>
#include <gntl/archetype/parser/connector_action.hpp>
#include <gntl/archetype/parser/connector_simple_action.hpp>
#include <gntl/archetype/parser/connector_compound_action.hpp>
#include <gntl/archetype/parser/connector_parameter.hpp>
#include <gntl/archetype/parser/causal_connector.hpp>
#include <gntl/archetype/parser/connector_base.hpp>
#include <gntl/concept/parser/connector/connector_base.hpp>

#include <boost/concept/assert.hpp>

namespace archetype = gntl::archetype;
namespace concept = gntl::concept;

void compile_time_specific ()
{
    typedef archetype::parser::connector_base
        <archetype::parser::causal_connector
        <archetype::parser::connector_condition_expression
          <
            boost::mpl::vector
            <
             archetype::parser::connector_simple_condition
           , archetype::parser::connector_compound_condition
             <
                archetype::parser::connector_statement
                <
                   archetype::parser::connector_assessment_statement
                       <
                          archetype::parser::connector_attribute_assessment
                        , archetype::parser::connector_assessment
                          <
                              archetype::parser::connector_attribute_assessment
                            , archetype::parser::connector_value_assessment
                          >
                       >
                 , archetype::parser::connector_compound_statement
                   <
                       archetype::parser::connector_assessment_statement
                       <
                          archetype::parser::connector_attribute_assessment
                        , archetype::parser::connector_assessment
                          <
                              archetype::parser::connector_attribute_assessment
                            , archetype::parser::connector_value_assessment
                          >
                       >
                   >
                >
              , archetype::parser::connector_simple_condition
             >
            >
          >
        , archetype::parser::connector_action
          <
            archetype::parser::connector_simple_action
            , archetype::parser::connector_compound_action
            <
              archetype::parser::connector_simple_action
            >
          >
         , archetype::parser::connector_parameter>, int> connector_base_type;
    BOOST_CONCEPT_ASSERT ((concept::parser::ConnectorBase<connector_base_type>));
}

int main() {}
