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

#define BOOST_TEST_MODULE parse_descriptor_descriptor_base1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char descriptor_descriptor_base[]
  = "<descriptorBase id=\"descriptorbase1\">\n"
    "  <descriptor id=\"descriptor1\" explicitDur=\"5s\" freeze=\"false\" "
    "              region=\"region1\" "
    "              moveLeft=\"4\" moveRight=\"6\" moveUp=\"8\" "
    "              moveDown=\"2\" focusIndex=\"5\" focusBorderColor=\"black\" "
    "              focusBorderWidth=\"10\" focusBorderTransparency=\"1.0\" "
    "              focusSrc=\"src1\" focusSelSrc=\"src2\" selBorderColor=\"white\" "
    "              transIn=\"trans1,trans2\" transOut=\"trans2,trans1\" />\n"
    "</descriptorBase>"
;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_descriptor_descriptor_base1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(descriptor_descriptor_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::descriptor_base descriptor_base(document.root());
        GNTL_CONCEPT_ASSERT
          ((concept::parser::DescriptorBase<parser::libxml2::dom::descriptor_base>));

        typedef concept::parser::descriptor_base_traits
          <parser::libxml2::dom::descriptor_base>
          descriptor_base_traits;
        typedef concept::parser::descriptor_traits
          <parser::libxml2::dom::descriptor>
          descriptor_traits;

        descriptor_base_traits::descriptor_range drange 
          = descriptor_base_traits::descriptor_all(descriptor_base);

        GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (std::distance (boost::begin (drange)
                                                        , boost::end (drange)), 1);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_base_traits::has_identifier (descriptor_base));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_base_traits::identifier (descriptor_base), "descriptorbase1");

        typedef descriptor_base_traits::descriptor_range descriptor_range;
        typedef boost::range_value<descriptor_range>::type descriptor_type;

        descriptor_type first = *boost::begin (drange);
        
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::identifier (first), "descriptor1");
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_explicit_duration (first));
        GNTL_GLOBAL_ALLOC_CHECK (descriptor_traits::explicit_duration (first) == boost::posix_time::seconds (5));
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_region (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::region (first), "region1");
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_freeze (first));
        GNTL_GLOBAL_ALLOC_CHECK (!descriptor_traits::freeze (first));
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_move_left (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::move_left (first), 4);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_move_right (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::move_right (first), 6);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_move_up (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::move_up (first), 8);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_move_down (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::move_down (first), 2);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_index (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::focus_index (first), 5);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_border_color (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::focus_border_color (first)
                                       , gntl::parser::libxml2::dom::color());
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_border_width (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::focus_border_width (first), 10);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_border_transparency (first));
        // GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_focus_border_transparency (first), 1.0f);
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_source (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::focus_source (first), "src1");
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_focus_selection_source (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::focus_selection_source (first), "src2");
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_selection_border_color (first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_traits::selection_border_color (first)
                                       , gntl::parser::libxml2::dom::color(255,255,255));
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_transition_in (first));
        //GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_transition_in (first), "trans2,trans1");
        GNTL_GLOBAL_ALLOC_REQUIRE (descriptor_traits::has_transition_out (first));
        //GNTL_GLOBAL_ALLOC_CHECK_EQUAL (descriptor_transition_out (first), "trans1,trans2");
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
