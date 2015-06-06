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

#ifndef GNTL_PARSER_LIBXML2_DOM_SWITCH_PORT_HPP
#define GNTL_PARSER_LIBXML2_DOM_SWITCH_PORT_HPP

#include <gntl/concept/parser/switch/switch_port.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct switch_port
{
  switch_port(xml_node node)
    : node(node) {}

  typedef xml_string<> identifier_type;

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct switch_port_traits<gntl::parser::libxml2::dom::switch_port>
{
  typedef boost::mpl::true_ is_switch_port;
  typedef gntl::parser::libxml2::dom::switch_port switch_port_type;
  typedef switch_port_type::identifier_type identifier_type;

  static identifier_type identifier(switch_port_type s)
  {
    return s.node["id"].value();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
