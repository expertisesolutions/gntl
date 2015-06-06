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

#define BOOST_TEST_MODULE attribute_encoding_conversion
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"

const char xml_node_1[] 
  = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
    "<node attribute1=\"some";
const char xml_node_2[] = "thing\" />";

namespace parser = gntl::parser;

BOOST_AUTO_TEST_CASE (attribute_encoding_conversion)
{
    BOOST_REQUIRE_EQUAL(::xml_total_allocated, 0u);
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    ::xmlInitParser ();

    {
        std::string xml_node (xml_node_1);
        char c = 193;
        xml_node += c;
        xml_node += xml_node_2;

        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_node.c_str ())));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership
        std::string utf8_value = "some";
        c = 0xc3;
        utf8_value += c;
        c = 0x81;
        utf8_value += c;
        utf8_value += "thing";
        std::cout << utf8_value << std::endl;
        BOOST_CHECK (document.root ()["attribute1"].value () == utf8_value);
    }
    ::xmlCleanupParser ();
    BOOST_CHECK_EQUAL(::xml_total_allocated, 0u);
}
