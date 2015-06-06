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

#define BOOST_TEST_MODULE attribute_quotes
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"

const char xml_node[]
  = "<node attribute1=\"some&amp;thing\" />";

namespace parser = gntl::parser;

BOOST_AUTO_TEST_CASE (attribute_quotes)
{
    BOOST_REQUIRE_EQUAL(::xml_total_allocated, 0u);
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    ::xmlInitParser ();

    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_node)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership
        BOOST_CHECK (document.root ()["attribute1"].value () == "some&thing");
    }
    ::xmlCleanupParser ();
    BOOST_CHECK_EQUAL(::xml_total_allocated, 0u);
}
