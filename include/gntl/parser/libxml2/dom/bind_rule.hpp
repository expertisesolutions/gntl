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

#ifndef GNTL_PARSER_LIBXML2_DOM_BIND_RULE_HPP
#define GNTL_PARSER_LIBXML2_DOM_BIND_RULE_HPP

#include <gntl/concept/parser/switch/bind_rule.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct bind_rule
{
  bind_rule(xml_node node)
    : node(node) {}

  typedef xml_string<> constituent_type;
  typedef xml_string<> rule_type;

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct bind_rule_traits<gntl::parser::libxml2::dom::bind_rule>
{
  typedef boost::mpl::true_ is_bind_rule;
  typedef gntl::parser::libxml2::dom::bind_rule bind_rule_type;
  typedef bind_rule_type::constituent_type constituent_type;
  typedef bind_rule_type::rule_type rule_type;

  static constituent_type constituent(bind_rule_type s)
  {
    return s.node["constituent"].value();
  }

  static rule_type rule(bind_rule_type s)
  {
    return s.node["rule"].value();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
