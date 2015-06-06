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

#ifndef GNTL_PARSER_LIBXML2_DOM_RULE_BASE_HPP
#define GNTL_PARSER_LIBXML2_DOM_RULE_BASE_HPP

#include <gntl/concept/parser/rule/rule_base.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/rule.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct rule_base
{
    typedef xml_string<> identifier_type;

    rule_base (xml_node node)
        : node (node) {}

    xml_node node;
};

inline bool operator==(rule_base const& lhs, rule_base const& rhs)
{
    return lhs.node == rhs.node;
}

} } }

 namespace concept { namespace parser {

template <>
struct rule_base_traits<gntl::parser::libxml2::dom::rule_base>
{
  typedef boost::mpl::true_ is_rule_base;
  typedef gntl::parser::libxml2::dom::rule_base rule_base;
  typedef gntl::parser::libxml2::dom::rule_iterator rule_iterator;
  typedef boost::iterator_range<rule_iterator> rule_range;
  typedef rule_base::identifier_type identifier_type;

  static rule_range rule_all (rule_base b)
  {
    return rule_range (b.node.begin(), b.node.end());
  }
  static identifier_type identifier(rule_base b)
  {
    return b.node["id"].value();
  }
  static bool has_identifier(rule_base b)
  {
    return b.node["id"];
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
