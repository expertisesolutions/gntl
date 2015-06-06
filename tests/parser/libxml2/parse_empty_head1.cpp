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

#define BOOST_TEST_MODULE parse_empty_head1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/head/head.hpp>
#include <gntl/parser/libxml2/dom/head.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_head[]
  = "<head />";

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_head)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_head)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::head head (document.root ());

        GNTL_CONCEPT_ASSERT ((concept::parser::Head<parser::libxml2::dom::head>));
        typedef concept::parser::head_traits<parser::libxml2::dom::head> head_traits;

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        GNTL_GLOBAL_ALLOC_CHECK (!head_traits::has_import_document_base (head));
        GNTL_GLOBAL_ALLOC_CHECK (!head_traits::has_rule_base (head));
        GNTL_GLOBAL_ALLOC_CHECK (!head_traits::has_transition_base (head));
        GNTL_GLOBAL_ALLOC_CHECK (boost::empty(head_traits::region_base_all(head)));
        GNTL_GLOBAL_ALLOC_CHECK (!head_traits::has_descriptor_base (head));
        GNTL_GLOBAL_ALLOC_CHECK (!head_traits::has_connector_base (head));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
