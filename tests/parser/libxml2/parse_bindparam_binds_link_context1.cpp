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

#define BOOST_TEST_MODULE parse_bindparam_binds_link_context1
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
    "  <link id=\"link1\" xconnector=\"connector1\">\n"
    "    <bind role=\"role1\" component=\"component1\">\n"
    "      <bindParam name=\"name1\" value=\"value1\" />"
    "    </bind>"
    "    <bind role=\"role2\" component=\"component1\" interface=\"interface1\" />\n"
    "    <bind role=\"role2\" component=\"component1\" interface=\"interface2\" descriptor=\"descriptor1\" />\n"
    "  </link>\n"
    "</context>"
    ;

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_bindparam_binds_link_context1)
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

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (std::distance (boost::begin (crange)
                                                      , boost::end (crange)), 0);

        context_traits::link_range links = context_traits::link_all (context);

        GNTL_GLOBAL_ALLOC_REQUIRE (boost::distance(links) > 0);

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (link_traits::identifier(*boost::begin(links)), "link1");
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (link_traits::xconnector(*boost::begin(links)), "connector1");

        link_traits::bind_range bind_range = link_traits::bind(*boost::begin(links));

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL (boost::distance(bind_range), 3);

        boost::range_iterator<link_traits::bind_range>::type bind_iterator = boost::begin (bind_range);
        typedef boost::range_value<link_traits::bind_range>::type bind_type;
        
        GNTL_CONCEPT_ASSERT((concept::parser::Bind<bind_type>));

        typedef concept::parser::bind_traits<bind_type> bind_traits;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::role(*bind_iterator), "role1");
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::component(*bind_iterator), "component1");
        GNTL_GLOBAL_ALLOC_CHECK(!bind_traits::has_descriptor(*bind_iterator));
        GNTL_GLOBAL_ALLOC_CHECK(!bind_traits::has_interface(*bind_iterator));
        {
          bind_traits::bind_param_range bind_param = bind_traits::bind_param(*bind_iterator);
          GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL(boost::distance(bind_param), 1);
          typedef boost::range_value<bind_traits::bind_param_range>::type bind_param_type;
          bind_param_type bind_p = *boost::begin(bind_param);
          
          typedef concept::parser::bind_param_traits<bind_param_type>
            bind_param_traits;
          
          GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_param_traits::name(bind_p), "name1");
          GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_param_traits::value(bind_p), "value1");
        }

        ++bind_iterator;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::role(*bind_iterator), "role2");
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::component(*bind_iterator), "component1");
        GNTL_GLOBAL_ALLOC_REQUIRE(bind_traits::has_interface(*bind_iterator));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::interface_ (*bind_iterator), "interface1");
        GNTL_GLOBAL_ALLOC_CHECK(!bind_traits::has_descriptor(*bind_iterator));
        GNTL_GLOBAL_ALLOC_CHECK(boost::empty(bind_traits::bind_param(*bind_iterator)));

        ++bind_iterator;

        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::role(*bind_iterator), "role2");
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::component(*bind_iterator), "component1");
        GNTL_GLOBAL_ALLOC_REQUIRE(bind_traits::has_interface(*bind_iterator));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::interface_ (*bind_iterator), "interface2");
        GNTL_GLOBAL_ALLOC_REQUIRE(bind_traits::has_descriptor(*bind_iterator));
        GNTL_GLOBAL_ALLOC_CHECK_EQUAL(bind_traits::descriptor(*bind_iterator), "descriptor1");
        GNTL_GLOBAL_ALLOC_CHECK(boost::empty(bind_traits::bind_param(*bind_iterator)));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
