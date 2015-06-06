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

#ifndef GNTL_PARSER_LIBXML2_DOM_BIND_HPP
#define GNTL_PARSER_LIBXML2_DOM_BIND_HPP

#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/bind_param.hpp>
#include <gntl/parser/libxml2/dom/xml_bind_param_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser {
namespace libxml2 { namespace dom {

struct bind
{
  bind(xml_node node)
    : node(node) 
  {}

  typedef xml_string<> role_type;
  typedef xml_string<> component_type;
  typedef xml_string<> interface_type;
  typedef xml_string<> descriptor_type;

  typedef xml_element_node_iterator<bind_param, xml_bind_param_predicate>
    bind_param_iterator;

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct bind_traits<gntl::parser::libxml2::dom
                   ::bind>
{
  typedef gntl::parser::libxml2::dom::bind bind;  
  typedef bind::bind_param_iterator bind_param_iterator;  
  typedef boost::mpl::true_ is_bind;
  typedef bind::role_type role_type;
  typedef bind::component_type component_type;
  typedef bind::interface_type interface_type;
  typedef bind::descriptor_type descriptor_type;
  typedef boost::iterator_range<bind_param_iterator> bind_param_range;

  static role_type role(bind b)
  {
    return b.node["role"].value();
  }

  static role_type component(bind b)
  {
    return b.node["component"].value();
  }

  static role_type interface_ (bind b)
  {
    return b.node["interface"].value();
  }

  static role_type descriptor(bind b)
  {
    return b.node["descriptor"].value();
  }

  static bool has_interface(bind b)
  {
    return b.node["interface"];
  }

  static bool has_descriptor(bind b)
  {
    return b.node["descriptor"];
  }

  static bind_param_range bind_param(bind b)
  {
    return bind_param_range(b.node.begin(), b.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
