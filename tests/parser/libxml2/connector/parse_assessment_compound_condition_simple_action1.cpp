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

#define BOOST_TEST_MODULE parse_assessment_compound_condition_connector_simple_action1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/connector/connector_base.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char connector_base[]
  = "<connectorBase id=\"connector1\">\n"
    "   <causalConnector id=\"causal1\">\n"
    "     <compoundCondition operator=\"and\" delay=\"5s\">\n"
    "       <simpleCondition role=\"start\" />\n"
    "       <assessmentStatement comparator=\"eq\">\n"
    "          <attributeAssessment role=\"role1\" eventType=\"eventtype1\" />\n"
    "          <attributeAssessment role=\"role2\" eventType=\"eventtype2\" />\n"
    "       </assessmentStatement>\n"
    "     </compoundCondition>\n"
    "     <simpleAction role=\"role1\" delay=\"5s\" eventType=\"presentation\" "
    "                   actionType=\"stop\" value=\"value1\" min=\"1\""
    "                   max=\"2\" qualifier=\"seq\" repeat=\"5\" repeatDelay=\"10s\""
    "                   duration=\"10s\" by=\"2\" />\n"
    "   </causalConnector>\n"
    "</connectorBase>"
;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_assessment_compound_condition_connector_simple_action1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(connector_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        typedef concept::parser::connector_base_traits
          <parser::libxml2::dom::connector_base>
          connector_base_traits;

        typedef concept::parser::causal_connector_traits
          <parser::libxml2::dom::causal_connector>
          causal_connector_traits;

        parser::libxml2::dom::connector_base connector_base(document.root());

        GNTL_CONCEPT_ASSERT ((concept::parser::ConnectorBase<parser::libxml2::dom::connector_base>));

        connector_base_traits::causal_connector_range
          causal_connector_range = connector_base_traits
          ::causal_connector_all(connector_base);

        GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance (causal_connector_range), 1);
        GNTL_GLOBAL_ALLOC_REQUIRE (connector_base_traits::has_identifier (connector_base));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_base_traits::identifier (connector_base), "connector1");

        typedef boost::range_iterator
          <connector_base_traits::causal_connector_range>::type
            iterator_type;
        iterator_type first_ = boost::begin (causal_connector_range);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (causal_connector_traits::identifier (*first_), "causal1");
        {
            typedef causal_connector_traits::condition_type
              condition_type;
          
            condition_type condition = causal_connector_traits::condition (*first_);

            {
            typedef concept::parser::connector_condition_expression_traits
              <parser::libxml2::dom::causal_condition_expression>
              causal_condition_expression_traits;
            typedef concept::parser::connector_compound_condition_traits
              <parser::libxml2::dom::connector_compound_condition>
              connector_compound_condition_traits;
            {
                GNTL_GLOBAL_ALLOC_REQUIRE (causal_condition_expression_traits
                                           ::is_type<parser::libxml2::dom::connector_compound_condition>
                                           (condition));
                parser::libxml2::dom::connector_compound_condition
                  c = causal_condition_expression_traits
                  ::get<parser::libxml2::dom::connector_compound_condition>
                  (condition);

                GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (connector_compound_condition_traits::operator_ (c), "and");
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_compound_condition_traits::has_delay (c));
                GNTL_GLOBAL_ALLOC_CHECK (connector_compound_condition_traits::delay (c) == boost::posix_time::seconds (5));

                typedef connector_compound_condition_traits
                  ::condition_expression_range condition_expression_range;
                condition_expression_range condition_expressions
                  = connector_compound_condition_traits::condition_expression_all (c);

                GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance (condition_expressions), 2);

                typedef boost::range_iterator<condition_expression_range>::type
                  condition_expression_iterator;
                condition_expression_iterator condition_iterator = boost::begin(condition_expressions);

                typedef concept::parser::connector_simple_condition_traits
                  <parser::libxml2::dom::connector_simple_condition>
                  connector_simple_condition_traits;
                typedef concept::parser::connector_condition_expression_traits
                  <parser::libxml2::dom::compound_condition_expression>
                  compound_condition_expression_traits;
                {
                    parser::libxml2::dom::compound_condition_expression
                      condition = *condition_iterator;
                    GNTL_GLOBAL_ALLOC_REQUIRE (compound_condition_expression_traits
                                               ::is_type<parser::libxml2::dom::connector_simple_condition>
                                               (condition));
                    parser::libxml2::dom::connector_simple_condition
                      c = compound_condition_expression_traits
                      ::get<parser::libxml2::dom::connector_simple_condition> (condition);
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::role (c), "start");
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_delay (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_event_type (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_key (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_transition (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_min (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_max (c));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_simple_condition_traits::has_qualifier (c));
                }
                ++condition_iterator;
                {
                  parser::libxml2::dom::compound_condition_expression
                    condition = *condition_iterator;
                  GNTL_GLOBAL_ALLOC_REQUIRE (compound_condition_expression_traits
                                             ::is_type<parser::libxml2::dom::connector_assessment_statement>
                                               (condition));
                  parser::libxml2::dom::connector_assessment_statement
                    s = compound_condition_expression_traits
                    ::get<parser::libxml2::dom::connector_assessment_statement> (condition);

                  typedef concept::parser::connector_assessment_statement_traits
                    <parser::libxml2::dom::connector_assessment_statement>
                    connector_assessment_statement_traits;
                    typedef concept::parser::connector_attribute_assessment_traits
                      <parser::libxml2::dom::connector_attribute_assessment>
                      connector_attribute_assessment_traits;
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_assessment_statement_traits::comparator (s), "eq");
                    parser::libxml2::dom::connector_attribute_assessment f = connector_assessment_statement_traits::first (s);
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_attribute_assessment_traits::role (f), "role1");
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_attribute_assessment_traits::event_type (f), "eventtype1");
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_key (f));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_attribute_type (f));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_offset (f));

                    GNTL_GLOBAL_ALLOC_REQUIRE (connector_assessment_statement_traits
                                               ::is_second
                                               <parser::libxml2::dom::connector_attribute_assessment>
                                               (s));
                    parser::libxml2::dom::connector_attribute_assessment sec
                      = connector_assessment_statement_traits::second
                      <parser::libxml2::dom::connector_attribute_assessment> (s);
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_attribute_assessment_traits::role (sec), "role2");
                    GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_attribute_assessment_traits::event_type (sec), "eventtype2");
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_key (sec));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_attribute_type (sec));
                    GNTL_GLOBAL_ALLOC_CHECK (!connector_attribute_assessment_traits::has_offset (sec));
                }
            }
            }

            typedef causal_connector_traits::action_type
              action_type;
            typedef gntl::concept::parser::connector_action_traits
              <action_type> action_traits;
          
            action_type action = causal_connector_traits::action (*first_);

    // "     <simpleAction role=\"role1\" delay=\"5s\" eventType=\"presentation\" "
    // "                   actionType=\"actiontype1\" value=\"value1\" min=\"1\""
    // "                   max=\"2\" qualifier=\"seq\" repeat=\"5\" repeatDelay=\"10s\""
    // "                   duration=\"10s\" by=\"2\" />\n"
            {
              GNTL_GLOBAL_ALLOC_REQUIRE(!action_traits::is_compound(action));

              typedef action_traits::simple_action_type
                simple_action_type;
              simple_action_type simple_action = action_traits::simple_action(action);
              typedef concept::parser::connector_simple_action_traits
                <simple_action_type> simple_action_traits;
              
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::role(simple_action), "role1");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_delay(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::delay(simple_action)
                                            , boost::posix_time::seconds(5));
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_event_type(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::event_type(simple_action), gntl::event_enum::presentation);
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_action_type(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::action_type(simple_action), gntl::action_enum::stop);
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_value(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::value(simple_action), "value1");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_min(simple_action));
              GNTL_GLOBAL_ALLOC_REQUIRE((simple_action_traits::min) (simple_action) != boost::none);
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(*(simple_action_traits::min) (simple_action), 1u);
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_max(simple_action));
              GNTL_GLOBAL_ALLOC_REQUIRE((simple_action_traits::max) (simple_action) != boost::none);
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(*(simple_action_traits::max)(simple_action), 2u);
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_qualifier(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::qualifier(simple_action), "seq");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_repeat(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::repeat(simple_action), "5");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_repeat_delay(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::repeat_delay(simple_action), "10s");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_duration(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::duration(simple_action), "10s");
              GNTL_GLOBAL_ALLOC_CHECK(simple_action_traits::has_by(simple_action));
              GNTL_GLOBAL_ALLOC_CHECK_EQUAL(simple_action_traits::by(simple_action), "2");
            }
        }
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
