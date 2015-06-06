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
 
#define BOOST_TEST_MODULE parse_empty_rule_base
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/libxml2/dom/rule_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>

#include "xml_allocations.hpp"
#include "xml_allocations_definitions.hpp"
#include "global_allocations.hpp"
#include "global_allocations_definitions.hpp"

const char empty_rule_base[]
  = "<ruleBase id=\"identifier1\"/>"; 

namespace parser = gntl::parser;
namespace concept = gntl::concept;

BOOST_AUTO_TEST_CASE (parse_empty_import_documents)
{
    ::xmlGcMemSetup(&::xml_free, &::xml_malloc, &::xml_malloc
                    , &::xml_realloc, &::xml_strdup);
    
    ::xmlInitParser ();
    {
        ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(empty_rule_base)));
        parser::libxml2::dom::xml_document document(xmldoc); // gets ownership

        using namespace gntl::concept::parser;

        parser::libxml2::dom::rule_base rule_base(document.root());
        GNTL_CONCEPT_ASSERT ((concept::parser::RuleBase<parser::libxml2::dom::rule_base>));

        xml_stabilized_allocations ();
        global_stabilized_allocations ();

        // typedef concept::parser::has_rule_traits
        //   <result_type> has_rule_traits;
        // GNTL_GLOBAL_ALLOC_CHECK (rule_base::identifier (rule_base) == "identifier1");
        // GNTL_GLOBAL_ALLOC_CHECK (boost::empty(has_rule_traits::rule (rule_base)));
    }
    ::xmlCleanupParser ();
    GNTL_GLOBAL_ALLOC_CHECK_EQUAL(::xml_total_allocated, 0u);

    global_destabilized_allocations ();
}
