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

#define BOOST_TEST_MODULE parse_empty_body1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/body/body.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/concept_check.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_body[]
  = "<body />";

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_body)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_body)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        typedef parser::libxml2::dom::body<std::string> body_type;
        typedef concept::parser::body_traits<body_type> body_traits;

        body_type body (document.root (), "id1");
        GNTL_CONCEPT_ASSERT ((concept::parser::Body<body_type>));

        xml_stabilized_allocations ();

        typedef concept::parser::context_traits<body_traits::context_type>
          context_traits;
        body_traits::context_type
            context = body_traits::context (body);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (context_traits::identifier (context), "id1");
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
