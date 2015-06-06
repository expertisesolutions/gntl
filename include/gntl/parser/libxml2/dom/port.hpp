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

#ifndef GNTL_PARSER_LIBXML2_DOM_PORT_HPP
#define GNTL_PARSER_LIBXML2_DOM_PORT_HPP

#include <gntl/concept/parser/port/port.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct port
{
    port (xml_node node)
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef xml_string<> component_type;
    typedef xml_string<> interface_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct port_traits<gntl::parser::libxml2::dom
                   ::port>
{
  typedef boost::mpl::true_ is_port;
  typedef gntl::parser::libxml2::dom::port port;
  typedef port::identifier_type identifier_type;
  typedef port::component_type component_type;
  typedef port::interface_type interface_type;

  static identifier_type identifier (port p)
  {
    return p.node["id"].value ();
  }

  static component_type component (port p)
  {
    return p.node["component"].value ();
  }

  static bool has_interface (port p)
  {
    return p.node["interface"];
  }

  static interface_type interface_ (port p)
  {
    return p.node["interface"].value ();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
