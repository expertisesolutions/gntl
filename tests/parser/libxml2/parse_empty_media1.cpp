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

#define BOOST_TEST_MODULE parse_empty_media1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/media/media.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_media[]
  = "<media id=\"id1\" src=\"source1\" refer=\"refer1\" "
    "       instance=\"inst1\" type=\"type/subtype\" descriptor=\"descriptor1\" />";

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_media)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_media)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::media media (document.root ());

        GNTL_CONCEPT_ASSERT ((concept::parser::Media<parser::libxml2::dom::media>));
        
        typedef concept::parser::media_traits<parser::libxml2::dom::media> media_traits;

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::identifier (media), "id1");
        GNTL_GLOBAL_ALLOC_REQUIRE (media_traits::has_source (media));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::source (media), "source1");
        GNTL_GLOBAL_ALLOC_REQUIRE (media_traits::has_refer (media));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::refer (media), "refer1");
        GNTL_GLOBAL_ALLOC_REQUIRE (media_traits::has_instance (media));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::instance (media), "inst1");
        GNTL_GLOBAL_ALLOC_REQUIRE (media_traits::has_type (media));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::type (media), "type/subtype");
        GNTL_GLOBAL_ALLOC_REQUIRE (media_traits::has_descriptor (media));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (media_traits::descriptor (media), "descriptor1");

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (boost::distance (media_traits::property_all (media)), 0);
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
