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
 
#define BOOST_TEST_MODULE parse_rule_rule_base1
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/rule_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char rule_base[]
  = "<ruleBase id=\"identifier1\">\n"
    "  <Rule id=\"rule1\" var=\"var1\" comparator=\"eq\" value=\"0\"/>\n"
    "  <compositeRule id=\"crule1\" operator=\"and\">\n"
    "    <Rule id=\"rule2\" var=\"var2\" comparator=\"eq\" value=\"5\"/>\n"
    "    <Rule id=\"rule3\" var=\"var3\" comparator=\"eq\" value=\"10\"/>\n"
    "  </compositeRule>\n"
    "</ruleBase>\n"
 ; 

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_rule_rule_base1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(rule_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        parser::libxml2::dom::rule_base rule_base(document.root());

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        typedef concept::parser::rule_base_traits<parser::libxml2::dom::rule_base>
          rule_base_traits;

        GNTL_GLOBAL_ALLOC_CHECK (rule_base_traits::identifier (rule_base) == "identifier1");
        GNTL_GLOBAL_ALLOC_CHECK (rule_base_traits::identifier (rule_base) != "foo");

        std::cout << "distance " << boost::distance(rule_base_traits::rule_all (rule_base)) << std::endl;
        GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance(rule_base_traits::rule_all (rule_base)), 2);

        typedef rule_base_traits::rule_range rule_range;
        rule_range rrange = rule_base_traits::rule_all (rule_base);
        typedef boost::range_iterator<rule_range>::type iterator_type;
        typedef boost::range_value<rule_range>::type rule_type;
        typedef concept::parser::rule_traits<rule_type> rule_traits;

        iterator_type first = boost::begin (rrange);
        GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*first) == "rule1");
        GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*first) != "foo");
        GNTL_GLOBAL_ALLOC_REQUIRE (!rule_traits::is_composite (*first));
        typedef parser::libxml2::dom::rule::simple_rule_type simple_rule_type;
        typedef concept::parser::simple_rule_traits<simple_rule_type> simple_rule_traits;
        simple_rule_type simple_rule = rule_traits::simple_rule (*first);
        GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::variable (simple_rule) == "var1");
        GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::variable (simple_rule) != "foo");
        GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::comparator (simple_rule) == gntl::rule_comparator::equal);
        GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::value (simple_rule) == "0");
        GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::value (simple_rule) != "foo");

        ++first;

        GNTL_GLOBAL_ALLOC_REQUIRE (rule_traits::is_composite (*first));

        {
            typedef parser::libxml2::dom::rule::composite_rule_type composite_rule_type;
            composite_rule_type composite_rule = rule_traits::composite_rule (*first);

            typedef concept::parser::composite_rule_traits<composite_rule_type> composite_rule_traits;
            typedef composite_rule_traits::rule_range range_type;
            range_type composite_range = composite_rule_traits::rule_all(composite_rule);
            typedef boost::range_iterator<range_type>::type iterator_type;

            iterator_type inner_first = boost::begin (composite_range);
            GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance (composite_range), 2);

            GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*inner_first) == "rule2");

            simple_rule = rule_traits::simple_rule (*inner_first);

            GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*inner_first)
                                     == simple_rule_traits::identifier (simple_rule));

            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::variable (simple_rule) == "var2");
            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::comparator (simple_rule) == gntl::rule_comparator::equal);
            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::value (simple_rule) == "5");

            ++inner_first;
            simple_rule = rule_traits::simple_rule (*inner_first);

            GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*inner_first) == "rule3");

            GNTL_GLOBAL_ALLOC_CHECK (rule_traits::identifier (*inner_first) == simple_rule_traits::identifier (simple_rule));

            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::variable (simple_rule) == "var3");
            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::comparator (simple_rule) == gntl::rule_comparator::equal);
            GNTL_GLOBAL_ALLOC_CHECK (simple_rule_traits::value (simple_rule) == "10");
        }
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
