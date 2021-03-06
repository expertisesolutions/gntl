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

#ifndef GNTL_PARSER_LIBXML2_DOM_LINK_PARAM_HPP
#define GNTL_PARSER_LIBXML2_DOM_LINK_PARAM_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/concept/parser/link/link_param.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser {
namespace libxml2 { namespace dom {

struct link_param
{
  link_param(xml_node node)
    : node(node) {}

  typedef xml_string<> name_type;
  typedef xml_string<> value_type;

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct link_param_traits<gntl::parser::libxml2::dom
                         ::link_param>
{
  typedef gntl::parser::libxml2::dom::link_param link_param;
  typedef boost::mpl::true_ is_link_param;
  typedef link_param::name_type name_type;
  typedef link_param::value_type value_type;

  static name_type name (link_param b)
  {
    return b.node["name"].value();
  }

  static value_type value (link_param b)
  {
    return b.node["value"].value();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
