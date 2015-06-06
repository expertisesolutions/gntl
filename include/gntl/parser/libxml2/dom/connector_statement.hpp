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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_STATEMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_STATEMENT_HPP

#include <gntl/parser/libxml2/dom/connector_assessment_statement.hpp>
#include <gntl/concept/parser/connector/connector_statement.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_compound_statement;

struct connector_statement
{
    connector_statement (xml_node node)
        : node (node) {}

    typedef connector_assessment_statement assessment_statement_type;
    typedef connector_compound_statement compound_statement_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_statement_traits<gntl::parser::libxml2::dom
                                  ::connector_statement>
{
  typedef boost::mpl::true_ is_connector_statement;
  typedef gntl::parser::libxml2::dom::connector_statement
    connector_statement;
  typedef connector_statement::assessment_statement_type
  assessment_statement_type;
  typedef connector_statement::compound_statement_type
    compound_statement_type;
  
  static bool is_compound (connector_statement c)
  {
    return c.node.name () == "compoundStatement";
  }

  static assessment_statement_type assessment_statement (connector_statement c)
  {
    return c.node;
  }
  
  static compound_statement_type compound_statement (connector_statement c);
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
