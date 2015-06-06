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

#define BOOST_TEST_MODULE parse_import_ncl_import_documents
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/import_document_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include <cstring>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char import_document_base[]
  = "<importedDocumentBase>"
    "  <importNCL documentURI=\"other.ncl\" alias=\"other\"/>"
    "</importedDocumentBase>"
  ;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_import_ncl_import_documents)
{
  ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                  , &::xml_realloc, &::xml_strdup);

  ::xmlInitParser();

  {
    ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(import_document_base)));
    parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

    using namespace gntl::concept::parser;

    GNTL_CONCEPT_ASSERT((concept::parser::ImportNCL
                                         <parser::libxml2::dom::import_ncl>));
    GNTL_CONCEPT_ASSERT((concept::parser::ImportDocumentBase
                                         <parser::libxml2::dom::import_document_base>));

    typedef concept::parser::import_ncl_traits
      <parser::libxml2::dom::import_ncl>
      import_ncl_traits;

    xml_stabilized_allocations ();
    global_stabilized_allocations ();

    // typedef concept::parser::has_import_ncl_traits
    //   <parser::libxml2::dom::import_document_base>
    //   has_import_ncl_traits;

    // has_import_ncl_traits::import_ncl_range
    //   import_ncl_range = has_import_ncl_traits::import_ncl(import_document_base);
    // GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (boost::distance(import_ncl_range), 1);
    // GNTL_GLOBAL_ALLOC_REQUIRE (import_ncl_traits::document_uri
    //                            (*boost::begin(import_ncl_range)) == "other.ncl");
    // GNTL_GLOBAL_ALLOC_REQUIRE (import_ncl_traits::alias
    //                            (*boost::begin(import_ncl_range)) == "other");
    // GNTL_GLOBAL_ALLOC_REQUIRE (import_ncl_traits::document_uri
    //                            (*boost::begin(import_ncl_range)) != "foo");
    // GNTL_GLOBAL_ALLOC_REQUIRE (import_ncl_traits::alias
    //                            (*boost::begin(import_ncl_range)) != "foo");
  }  
  ::xmlCleanupParser();
  GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

  global_destabilized_allocations ();
}
