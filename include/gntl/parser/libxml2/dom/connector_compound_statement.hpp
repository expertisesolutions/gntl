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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_STATEMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_STATEMENT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_statement_predicate.hpp>
#include <gntl/parser/libxml2/dom/compound_statement_expression.hpp>
#include <gntl/concept/parser/connector/connector_compound_statement.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_compound_statement
{
    connector_compound_statement (xml_node node)
        : node (node) {}

    typedef compound_statement_expression statement_type;
    typedef xml_element_node_iterator<statement_type, xml_statement_predicate> statement_iterator;

    typedef xml_string<> operator_type;
    typedef bool is_negated_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_compound_statement_traits<gntl::parser::libxml2::dom
                                           ::connector_compound_statement>
{
  typedef boost::mpl::true_ is_connector_compound_statement;
  typedef gntl::parser::libxml2::dom::connector_compound_statement
    connector_compound_statement;
  typedef connector_compound_statement::operator_type
    operator_type;
  typedef connector_compound_statement::is_negated_type
    is_negated_type;
  typedef boost::iterator_range<connector_compound_statement
                                ::statement_iterator> 
    condition_expression_range;

  static operator_type operator_ (connector_compound_statement c)
  {
    return c.node["operator"].value ();
  }

  static bool has_is_negated (connector_compound_statement c)
  {
    return c.node["isNegated"];
  }

  static bool is_negated (connector_compound_statement c)
  {
    gntl::parser::libxml2::dom::xml_string<> 
      v = c.node["isNegated"].value ();
    return v == "true" || v == "isNegated";
  }

  static condition_expression_range condition_expression_all
    (connector_compound_statement c)
  {
    return condition_expression_range(c.node.begin()
                                      , c.node.end());
  }
};

template <>
struct connector_condition_traits<gntl::parser::libxml2::dom
                                  ::connector_compound_statement>
{
  typedef boost::mpl::true_ is_connector_condition;
  typedef compound_statement_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
