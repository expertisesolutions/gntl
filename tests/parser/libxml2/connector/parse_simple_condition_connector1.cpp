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

#define BOOST_TEST_MODULE parse_connector_connector_base1
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
    "     <simpleCondition role=\"start\" delay=\"5s\" eventType=\"presentation\""
    "                      key=\"ENTER\" transition=\"starts\" min=\"1\" max=\"1\" "
    "                      qualifier=\"seq\" />\n"
    "   </causalConnector>\n"
    "</connectorBase>"
;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_connector_connector_base1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(connector_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::connector_base connector_base(document.root());

        typedef concept::parser::connector_base_traits
          <parser::libxml2::dom::connector_base>
          connector_base_traits;

        typedef concept::parser::causal_connector_traits
          <parser::libxml2::dom::causal_connector>
          causal_connector_traits;

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
        iterator_type first = boost::begin (causal_connector_range);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (causal_connector_traits::identifier (*first), "causal1");
        {
            causal_connector_traits::condition_type
              condition = causal_connector_traits::condition (*first);

            typedef concept::parser::connector_condition_expression_traits
              <parser::libxml2::dom::causal_condition_expression>
              causal_condition_expression_traits;
            typedef concept::parser::connector_simple_condition_traits
              <parser::libxml2::dom::connector_simple_condition>
              connector_simple_condition_traits;
            {
                GNTL_GLOBAL_ALLOC_REQUIRE (causal_condition_expression_traits
                                           ::is_type<parser::libxml2::dom::connector_simple_condition>
                                           (condition));
                parser::libxml2::dom::connector_simple_condition 
                  c = causal_condition_expression_traits
                  ::get<parser::libxml2::dom::connector_simple_condition> (condition);

                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::role (c), "start");
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_delay (c));
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::delay (c), boost::posix_time::seconds (5));
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_event_type (c));
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::event_type (c), gntl::event_enum::presentation);
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_key (c));
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::key (c), "ENTER");
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_transition (c));
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::transition (c), gntl::transition_enum::starts);
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_min (c));
                GNTL_GLOBAL_ALLOC_REQUIRE ((connector_simple_condition_traits::min) (c) != boost::none);
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (*(connector_simple_condition_traits::min) (c), 1u);
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_max (c));
                GNTL_GLOBAL_ALLOC_REQUIRE ((connector_simple_condition_traits::max) (c) != boost::none);
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (*(connector_simple_condition_traits::max) (c), 1u);
                GNTL_GLOBAL_ALLOC_REQUIRE (connector_simple_condition_traits::has_qualifier (c));
                GNTL_GLOBAL_ALLOC_CHECK_EQUAL (connector_simple_condition_traits::qualifier (c), "seq");
            }
        }
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
