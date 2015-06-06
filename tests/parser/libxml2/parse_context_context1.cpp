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

#define BOOST_TEST_MODULE parse_context_context1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char context[]
  = "<context id=\"id1\">\n"
    "  <context id=\"inner1\" />\n"
    "</context>"
    ;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_context_context)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(::context)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        typedef parser::libxml2::dom::context context_type;
        context_type context (document.root ());
        typedef concept::parser::context_traits<context_type> context_traits;

        GNTL_CONCEPT_ASSERT ((concept::parser::Context<context_type>));

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (context_traits::identifier (context), "id1");
        GNTL_GLOBAL_ALLOC_CHECK (!context_traits::has_refer (context));

        typedef context_traits::context_range context_range;
        context_range contexts = context_traits::context_all (context);

        GNTL_CONCEPT_ASSERT ((boost::ForwardRangeConcept<context_range>));

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (boost::distance(contexts), 1u);

        parser::libxml2::dom::context inner = *boost::begin(contexts);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (context_traits::identifier (inner), "inner1");
        GNTL_GLOBAL_ALLOC_CHECK (!context_traits::has_refer (context));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
