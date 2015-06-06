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

#ifndef GNTL_PARSER_LIBXML2_DOM_RULE_HPP
#define GNTL_PARSER_LIBXML2_DOM_RULE_HPP

#include <gntl/concept/parser/rule/rule.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_rule_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_composite_rule_predicate.hpp>
#include <gntl/rule_comparator.hpp>
#include <gntl/rule_operator.hpp>
#include <gntl/range.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct simple_rule
{
    simple_rule (xml_node node)
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef xml_string<> variable_type;
    typedef xml_string<> value_type;

    xml_node node;
};

namespace rule_detail {
struct rule_predicate
{
    typedef bool result_type;
    result_type operator()(xml_node& node) const
    {
      return xml_rule_predicate()(node) || xml_composite_rule_predicate()(node);
    }
};
}

struct rule;
typedef xml_element_node_iterator<rule, rule_detail::rule_predicate> rule_iterator;

struct composite_rule
{
    composite_rule (xml_node node)
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef dom::rule_iterator rule_iterator;
    typedef dom::rule rule_type;

    xml_node node;
};

struct rule
{
  typedef xml_string<> identifier_type;
  typedef dom::simple_rule simple_rule_type;
  typedef dom::composite_rule composite_rule_type;

  rule(xml_node node)
    : node(node) {}

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct composite_rule_traits<gntl::parser::libxml2::dom::composite_rule>
{
  typedef boost::mpl::true_ is_composite_rule;
  typedef gntl::parser::libxml2::dom::composite_rule composite_rule_type;
  typedef composite_rule_type::identifier_type identifier_type;
  typedef gntl::rule_operator_type operator_type;
  typedef gntl::parser::libxml2::dom::rule_iterator rule_iterator;
  typedef boost::iterator_range<rule_iterator> rule_range;

  static identifier_type identifier(composite_rule_type b)
  {
    return b.node["id"].value();
  }
  static operator_type operator_(composite_rule_type b)
  {
    return operator_type(b.node["operator"].value() != "and");
  }
  static rule_range rule_all (composite_rule_type b)
  {
    return rule_range (b.node.begin(), b.node.end());
  }
};

template <>
struct simple_rule_traits<gntl::parser::libxml2::dom::simple_rule>
{
  typedef boost::mpl::true_ is_simple_rule;
  typedef gntl::parser::libxml2::dom::simple_rule simple_rule_type;
  typedef simple_rule_type::identifier_type identifier_type;
  typedef simple_rule_type::value_type value_type;
  typedef simple_rule_type::variable_type variable_type;
  typedef gntl::rule_comparator_type comparator_type;

  static identifier_type identifier(simple_rule_type r)
  {
    return r.node["id"].value();
  }
  static value_type value(simple_rule_type r)
  {
    return r.node["value"].value();
  }
  static variable_type variable(simple_rule_type r)
  {
    return r.node["var"].value();
  }
  static comparator_type comparator(simple_rule_type r)
  {
    return r.node["comparator"].value() == "eq"?
      rule_comparator::equal:rule_comparator::not_equal ;
  }
};

template <>
struct rule_traits<gntl::parser::libxml2::dom::rule>
{
  typedef boost::mpl::true_ is_rule;
  typedef gntl::parser::libxml2::dom::rule rule_type;
  typedef rule_type::identifier_type identifier_type;
  typedef rule_type::simple_rule_type simple_rule_type;
  typedef rule_type::composite_rule_type composite_rule_type;
  
  static bool is_composite(rule_type r)
  {
    return r.node.name() == "compositeRule";
  }
  static identifier_type identifier(rule_type r)
  {
    return r.node["id"].value();
  }
  static simple_rule_type simple_rule(rule_type r)
  {
    return simple_rule_type(r.node);
  }
  static composite_rule_type composite_rule(rule_type r)
  {
    return composite_rule_type(r.node);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
