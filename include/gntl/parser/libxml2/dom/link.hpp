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

#ifndef GNTL_PARSER_LIBXML2_DOM_LINK_HPP
#define GNTL_PARSER_LIBXML2_DOM_LINK_HPP

#include <gntl/parser/libxml2/dom/bind.hpp>
#include <gntl/parser/libxml2/dom/link_param.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/xml_bind_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_link_param_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/concept/parser/link/link.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser {
namespace libxml2 { namespace dom {

struct link
{
  link(xml_node node)
    : node (node)
  {}

  typedef xml_string<> identifier_type;
  typedef xml_string<> xconnector_type;

  typedef xml_element_node_iterator<dom::bind, xml_bind_predicate> bind_iterator;
  typedef xml_element_node_iterator<dom::link_param, xml_link_param_predicate> link_param_iterator;

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct link_traits<gntl::parser::libxml2::dom
                   ::link>
{
  typedef gntl::parser::libxml2::dom::link link;
  typedef boost::mpl::true_ is_link;
  typedef link::identifier_type identifier_type;
  typedef link::xconnector_type xconnector_type;
  typedef boost::iterator_range<link::bind_iterator> bind_range;
  typedef boost::iterator_range<link::link_param_iterator> link_param_range;

  static identifier_type identifier(link l)
  {
    return l.node["id"].value();
  }

  static bool has_identifier(link l)
  {
    return l.node["id"];
  }

  static xconnector_type xconnector(link l)
  {
    return l.node["xconnector"].value();
  }

  static bind_range bind(link l)
  {
    return bind_range(l.node.begin(), l.node.end());
  }

  static link_param_range link_param (link l)
  {
    return link_param_range (l.node.begin(), l.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
