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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_CONDITION_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_CONDITION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/time_duration_parser.hpp>
#include <gntl/parser/libxml2/dom/connector_compound_statement.hpp>
#include <gntl/parser/libxml2/dom/connector_statement.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_statement_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_simple_condition_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_compound_condition_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_assessment_statement_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_compound_statement_predicate.hpp>
#include <gntl/concept/parser/connector/has_connector_statement.hpp>
#include <gntl/concept/parser/connector/connector_compound_condition.hpp>
#include <gntl/concept/parser/connector/connector_condition.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct compound_condition_expression;

struct connector_compound_condition
{
    connector_compound_condition (xml_node node)
        : node (node) {}

    typedef xml_string<> operator_type;
    typedef boost::posix_time::time_duration delay_type;

    struct xml_condition_predicate
    {
        typedef bool result_type;
        result_type operator()(xml_node& node) const
        {
            return xml_simple_condition_predicate()(node) || xml_compound_condition_predicate()(node)
              || xml_assessment_statement_predicate()(node) || xml_compound_statement_predicate()(node);
        }
    };

    typedef compound_condition_expression condition_type;
    typedef xml_element_node_iterator<condition_type, xml_condition_predicate> condition_iterator;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_condition_traits<gntl::parser::libxml2::dom
                                  ::connector_compound_condition>
{
  typedef boost::mpl::true_ is_connector_condition;
  typedef compound_condition_tag category_tag;
};

} } }

#include <gntl/detail/pop_options.hpp>

#include <gntl/parser/libxml2/dom/compound_condition_expression.hpp>

#endif
