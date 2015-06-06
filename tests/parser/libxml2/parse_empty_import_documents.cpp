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
 
#define BOOST_TEST_MODULE parse_empty_import_documents
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/import_document_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/concept/parser/import/import_document_base.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_import_document_base[]
  = "<importedDocumentBase />"; 

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_import_documents)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);

    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_import_document_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership
        parser::libxml2::dom::import_document_base import_document_base(document.root());
#ifndef GNTL_DISABLE_CONCEPTS
        BOOST_CONCEPT_ASSERT ((concept::parser::ImportDocumentBase<parser::libxml2::dom::import_document_base>));
#endif

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        // parser::generic::simple_import_document_base_factory
        //   <parser::libxml2::dom::import_document_base, parser::libxml2::dom::import_document_base>
        //       import_document_base_factory;
        // GNTL_GLOBAL_ALLOC_CHECK (parser::generic::parse_import_documents(import_document_base, import_document_base_factory) == import_document_base);
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
