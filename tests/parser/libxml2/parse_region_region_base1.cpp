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

#define BOOST_TEST_MODULE parse_region_region_base1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/region/region_base.hpp>
#include <gntl/parser/libxml2/dom/region_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char region_region_base[]
  = "<regionBase>\n"
    "  <region id=\"region1\" title=\"title1\" left=\"50\" right=\"50%\" top=\"0\" bottom=\"10\" "
    "          height=\"100\" width=\"101\" zIndex=\"2\" />\n"
    "  <region id=\"region2\" title=\"title2\" top=\"100\" zIndex=\"5\" />\n"
    "</regionBase>"
;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_region_region_base1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(region_region_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::region_base region_base(document.root());
        GNTL_CONCEPT_ASSERT ((concept::parser::RegionBase<parser::libxml2::dom::region_base>));

        typedef concept::parser::region_base_traits<parser::libxml2::dom::region_base> region_base_traits;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (boost::distance(region_base_traits::region_all (region_base)), 2);

        region_base_traits::region_range rrange = region_base_traits::region_all(region_base);

        typedef boost::range_iterator<region_base_traits::region_range>::type iterator_type;

        iterator_type first = boost::begin (rrange);

        typedef concept::parser::region_traits<parser::libxml2::dom::region> region_traits;
        typedef concept::parser::coordinate_traits<parser::libxml2::dom::coordinate> coordinate_traits;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::identifier (*first), "region1");
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_title (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::title (*first), "title1");
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_left (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::left (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::left (*first)), 50.0);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_right (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (coordinate_traits::is_percentual(region_traits::right (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::percentage(region_traits::right (*first)), 0.5);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_top (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::top (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::top (*first)), 0u);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_bottom (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::bottom (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::bottom (*first)), 10u);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_width (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::width (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::width (*first)), 101u);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_height (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::height (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::height (*first)), 100u);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_zindex (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::zindex (*first), 2);

        ++first;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::identifier (*first), "region2");
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_title (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::title (*first), "title2");
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_top (*first));
        GNTL_GLOBAL_ALLOC_REQUIRE (!coordinate_traits::is_percentual(region_traits::top (*first)));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (coordinate_traits::pixel(region_traits::top (*first)), 100u);
        GNTL_GLOBAL_ALLOC_REQUIRE (region_traits::has_zindex (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (region_traits::zindex (*first), 5);
        GNTL_GLOBAL_ALLOC_CHECK (!region_traits::has_left (*first));
        GNTL_GLOBAL_ALLOC_CHECK (!region_traits::has_right (*first));
        GNTL_GLOBAL_ALLOC_CHECK (!region_traits::has_bottom (*first));
        GNTL_GLOBAL_ALLOC_CHECK (!region_traits::has_height (*first));
        GNTL_GLOBAL_ALLOC_CHECK (!region_traits::has_width (*first));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
