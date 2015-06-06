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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ACTION_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ACTION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/concept/parser/connector/connector_action.hpp>

#include <gntl/parser/libxml2/dom/connector_simple_action.hpp>
#include <gntl/parser/libxml2/dom/connector_compound_action.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_action
{
  connector_action(xml_node node)
    : node(node) {}

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_action_traits<gntl::parser::libxml2::dom::connector_action>
{
  typedef boost::mpl::true_ is_connector_action;
  typedef gntl::parser::libxml2::dom::connector_action
    connector_action;
  typedef gntl::parser::libxml2::dom::connector_simple_action
    simple_action_type;
  typedef gntl::parser::libxml2::dom::connector_compound_action
    compound_action_type;

  static bool is_compound(connector_action a)
  {
    return a.node.name() == "compoundAction";
  }

  static simple_action_type simple_action(connector_action a)
  { return a.node; }
  static compound_action_type compound_action(connector_action a)
  { return a.node; }
};

template <>
struct connector_compound_action_traits<gntl::parser::libxml2::dom::connector_compound_action>
{
  typedef boost::mpl::true_ is_connector_compound_action;
  typedef gntl::parser::libxml2::dom::connector_compound_action
    connector_compound_action;

  typedef boost::iterator_range<connector_compound_action
                                ::action_iterator> 
    connector_action_range;

  static connector_action_range
    connector_action_all(connector_compound_action c)
  {
    return connector_action_range(c.node.begin()
                                  , c.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
