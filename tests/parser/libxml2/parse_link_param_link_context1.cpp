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

#define BOOST_TEST_MODULE parse_link_param_link_context1
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/range.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char context[]
  = "<context id=\"id1\">\n"
    "  <link id=\"link1\" xconnector=\"connector1\">\n"
    "    <linkParam name=\"name1\" value=\"value1\" />"
    "  </link>\n"
    "</context>\n"
    ;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_link_param_link_context1)
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

        typedef concept::parser::link_traits
          <parser::libxml2::dom::link>
          link_traits;

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (context_traits::identifier (context), "id1");
        GNTL_GLOBAL_ALLOC_CHECK (!context_traits::has_refer (context));

        typedef context_traits::context_range context_range;

        GNTL_CONCEPT_ASSERT ((boost::ForwardRangeConcept<context_range>));
        context_range crange = context_traits::context_all (context);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (gntl::range::distance (crange), 0u);

        context_traits::link_range links = context_traits::link_all (context);

        typedef boost::range_value<context_traits::link_range>::type link_type;
        GNTL_CONCEPT_ASSERT((concept::parser::Link<link_type>));

        GNTL_GLOBAL_ALLOC_REQUIRE (boost::distance(links) > 0);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (link_traits::identifier(*boost::begin(links)), "link1");
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (link_traits::xconnector(*boost::begin(links)), "connector1");
        GNTL_GLOBAL_ALLOC_CHECK (boost::empty(link_traits::bind(*boost::begin(links))));

        typedef link_traits::link_param_range link_param_range;
        link_param_range link_param = link_traits::link_param (*boost::begin(links));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (boost::distance(link_param), 1);
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
