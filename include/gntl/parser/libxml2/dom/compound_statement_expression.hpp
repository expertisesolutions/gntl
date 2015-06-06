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

#ifndef GNTL_PARSER_LIBXML2_DOM_COMPOUND_STATEMENT_EXPRESSION_HPP
#define GNTL_PARSER_LIBXML2_DOM_COMPOUND_STATEMENT_EXPRESSION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/connector_assessment_statement.hpp>
#include <gntl/parser/libxml2/dom/connector_compound_statement.hpp>
#include <gntl/concept/parser/connector/connector_condition_expression.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_compound_statement;

struct compound_statement_expression
{
  compound_statement_expression(xml_node node)
    : node(node) {}

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_condition_expression_traits<gntl::parser::libxml2::dom
                                             ::compound_statement_expression>
{
  typedef boost::mpl::true_ is_connector_condition_expression;
  typedef gntl::parser::libxml2::dom::compound_statement_expression
    compound_statement_expression;
  typedef gntl::parser::libxml2::dom::connector_assessment_statement
    assessment_statement_type;
  typedef gntl::parser::libxml2::dom::connector_compound_statement
    compound_statement_type;

  typedef boost::mpl::vector<assessment_statement_type
                             , compound_statement_type>
    condition_list_type;

  template <typename T>
  struct tag {};

  static bool is_type_aux (compound_statement_expression c
                           , tag<assessment_statement_type>)
  {
    return c.node.name() == "assessmentStatement";
  }
  static bool is_type_aux (compound_statement_expression c
                           , tag<compound_statement_type>)
  {
    return c.node.name() == "compoundStatement";
  }

  template <typename T>
  static bool is_type (compound_statement_expression c)
  {
    return is_type_aux(c, tag<T>());
  }

  template <typename T>
  static T get (compound_statement_expression c)
  {
    return T(c.node);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
