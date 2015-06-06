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

#define BOOST_TEST_MODULE parse_transition_transition_base1
#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <gntl/concept/parser/transition/transition_base.hpp>
#include <gntl/parser/libxml2/dom/transition_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char transition_transition_base[]
  = "<transitionBase>\n"
    "  <transition id=\"transition1\" type=\"type1\" subtype=\"subtype1\" dur=\"1s\" "
    "     startProgress=\"0.5\" "
    "     endProgress=\"1.0\" direction=\"forward\" fadeColor=\"black\"" 
    "     horRepeat=\"2\" vertRepeat=\"3\" borderWidth=\"5\"/>\n"
    "</transitionBase>"
;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_transition_transition_base1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(transition_transition_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        parser::libxml2::dom::transition_base transition_base(document.root());
        GNTL_CONCEPT_ASSERT ((concept::parser::TransitionBase<parser::libxml2::dom::transition_base>));

        typedef concept::parser::transition_base_traits<parser::libxml2::dom::transition_base>
          transition_base_traits;

        GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance (transition_base_traits::transition_all (transition_base)), 1);

        typedef transition_base_traits::transition_range transition_range;
        typedef boost::range_iterator<transition_range>::type iterator_type;
        transition_range transitions = transition_base_traits::transition_all(transition_base);
        
        iterator_type first = boost::begin (transitions);

        typedef concept::parser::transition_traits
          <parser::libxml2::dom::transition> transition_traits;
        
        GNTL_GLOBAL_ALLOC_CHECK (transition_traits::identifier (*first) == "transition1");
        GNTL_GLOBAL_ALLOC_CHECK (transition_traits::type (*first) == "type1");
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_duration (*first));
        GNTL_GLOBAL_ALLOC_CHECK (transition_traits::duration (*first) == boost::posix_time::seconds (1));
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_start_progress (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::start_progress (*first), 0.5);
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_end_progress (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::end_progress (*first), 1.0);
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_direction (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::direction (*first), "forward");
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_fade_color (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::fade_color (*first), "black");
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_horizontal_repeat (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::horizontal_repeat (*first), 2u);
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_vertical_repeat (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::vertical_repeat (*first), 3u);
        GNTL_GLOBAL_ALLOC_REQUIRE (transition_traits::has_border_width (*first));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (transition_traits::border_width (*first), 5u);
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
