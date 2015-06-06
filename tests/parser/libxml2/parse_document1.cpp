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

#define BOOST_TEST_MODULE parse_document1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/document/document.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/concept_check.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char xml_document[]
  = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
    "<ncl id=\"teste\" xmlns=\"http://www.ncl.org.br/NCL3.0/EDTVProfile\">\n"
    "<head>\n"
    " <connectorBase id=\"connectorbase\" />\n"
    "</head>\n"
    "<body>\n"
    "</body>\n"
    "</ncl>\n"
 ;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_document1)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_document)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        parser::libxml2::dom::document d (document.root ());

        GNTL_CONCEPT_ASSERT ((concept::parser::Document<parser::libxml2::dom::document>));

        xml_stabilized_allocations ();

        typedef concept::parser::document_traits
          <parser::libxml2::dom::document>
          document_traits;
        typedef concept::parser::head_traits
          <document_traits::head_type>
          head_traits;
        typedef concept::parser::connector_base_traits
          <parser::libxml2::dom::connector_base>
          connector_base_traits;

        document_traits::head_type
          head = document_traits::head (d);

         BOOST_REQUIRE (head_traits::has_connector_base (head));

         parser::libxml2::dom::connector_base cbase
             (head_traits::connector_base (head));

         BOOST_REQUIRE (connector_base_traits::has_identifier (cbase));
         BOOST_CHECK_EQUAL (connector_base_traits::identifier (cbase)
                            , "connectorbase");

         typedef
           document_traits::body_type 
           body_type;
         body_type body
             = document_traits::body (d);

         typedef concept::parser::body_traits<body_type>
           body_traits;

         typedef body_traits::context_type context_type;
         context_type context = body_traits::context (body);
         typedef concept::parser::context_traits<context_type> context_traits;

         GNTL_GLOBAL_ALLOC_CHECK_EQUAL (context_traits::identifier (context), "teste");
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
