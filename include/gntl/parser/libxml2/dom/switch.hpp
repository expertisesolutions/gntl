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

#ifndef GNTL_PARSER_LIBXML2_DOM_SWITCH_HPP
#define GNTL_PARSER_LIBXML2_DOM_SWITCH_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/context_fwd.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/bind_rule.hpp>
#include <gntl/parser/libxml2/dom/switch_port.hpp>
#include <gntl/parser/libxml2/dom/xml_context_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_switch_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_media_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_bind_rule_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_switch_port_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_default_component_predicate.hpp>
#include <gntl/concept/parser/switch/switch.hpp>
#include <gntl/concept/parser/context/context.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct switch_
{
  switch_() {}
  switch_(xml_node node)
    : node(node) {}

  xml_node node;

  typedef xml_string<> string_type;

  typedef dom::context context_type;
  typedef xml_element_node_iterator<context_type, dom::xml_context_predicate> context_iterator;

  typedef dom::switch_ switch_type;
  typedef xml_element_node_iterator<switch_type, dom::xml_switch_predicate> switch_iterator;

  typedef dom::media media_type;
  typedef xml_element_node_iterator<media_type, dom::xml_media_predicate> media_iterator;

  typedef dom::bind_rule bind_rule_type;
  typedef xml_element_node_iterator<bind_rule_type, dom::xml_bind_rule_predicate> bind_rule_iterator;

  typedef dom::switch_port switch_port_type;
  typedef xml_element_node_iterator<switch_port_type, dom::xml_switch_port_predicate> switch_port_iterator;

  typedef dom::xml_default_component_predicate xml_default_component_predicate;
};

} } }

namespace concept { namespace parser {

template <>
struct switch_traits<gntl::parser::libxml2::dom::switch_>
{
  typedef boost::mpl::true_ is_switch;
  typedef gntl::parser::libxml2::dom::switch_ switch_type;
  typedef switch_type::string_type string_type;
  typedef string_type refer_type;
  typedef string_type identifier_type;
  typedef switch_type::context_iterator context_iterator;
  typedef switch_type::media_iterator media_iterator;
  typedef switch_type::switch_iterator switch_iterator;
  typedef switch_type::switch_port_iterator switch_port_iterator;
  typedef switch_type::bind_rule_iterator bind_rule_iterator;
  typedef boost::iterator_range<switch_port_iterator> switch_port_range;
  typedef boost::iterator_range<bind_rule_iterator> bind_rule_range;
  typedef boost::iterator_range<media_iterator> media_range;
  typedef boost::iterator_range<context_iterator> context_range;
  typedef boost::iterator_range<switch_iterator> switch_range;
  typedef switch_type::xml_default_component_predicate xml_default_component_predicate;

  static identifier_type identifier(switch_type s)
  {
    return s.node["id"].value();
  }
  static bool has_refer(switch_type s)
  {
    return s.node["refer"];
  }
  static refer_type refer(switch_type s)
  {
    return s.node["refer"].value();
  }
  typedef gntl::parser::libxml2::dom::xml_node xml_node;
  static bool has_default_component(switch_type s)
  {
    typedef gntl::parser::libxml2::dom::xml_element_node_iterator<xml_node, xml_default_component_predicate> iterator;
    iterator first = s.node.begin()
      , last = s.node.end();
    return std::distance(first, last) != 0;
  }
  static identifier_type default_component(switch_type s)
  {
    typedef gntl::parser::libxml2::dom::xml_element_node_iterator<xml_node, xml_default_component_predicate> iterator;
    iterator first = s.node.begin();
    return (*first)["component"].value();
  }
  static switch_port_range switch_port_all(switch_type s);
  static bind_rule_range bind_rule_all(switch_type s)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(s.node != end)
      return bind_rule_range(s.node.begin(), s.node.end());
    else
      return bind_rule_range(end, end);
  }
  static media_range media_all(switch_type s)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(s.node != end)
      return media_range(s.node.begin(), s.node.end());
    else
      return media_range(end, end);
  }
  static context_range context_all(switch_type s);
  static switch_range switch_all(switch_type s);
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
