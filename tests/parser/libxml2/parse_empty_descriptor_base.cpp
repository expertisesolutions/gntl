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

#define BOOST_TEST_MODULE parse_empty_descriptor_base
#include <boost/test/included/unit_test.hpp>

#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_descriptor_base[]
= "<descriptorBase />";

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_descriptor_base)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_descriptor_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::descriptor_base descriptor_base(document.root());
        GNTL_CONCEPT_ASSERT ((concept::parser::DescriptorBase<parser::libxml2::dom::descriptor_base>));

        typedef concept::parser::descriptor_base_traits
          <parser::libxml2::dom::descriptor_base>
          descriptor_base_traits;

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        descriptor_base_traits::descriptor_range drange 
          = descriptor_base_traits::descriptor_all(descriptor_base);

        GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL (std::distance (boost::begin (drange)
                                                        , boost::end (drange)), 0);
        GNTL_GLOBAL_ALLOC_CHECK (!descriptor_base_traits::has_identifier (descriptor_base));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
