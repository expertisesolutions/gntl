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

#ifndef GNTL_ALGORITHM_STRUCTURE_RULE_EVALUATE_HPP
#define GNTL_ALGORITHM_STRUCTURE_RULE_EVALUATE_HPP

#include <gntl/concept/parser/rule/rule.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/rule_comparator.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace rule {

template <typename Rule, typename Document>
bool evaluate(Rule rule, Document document);

namespace rule_detail {

template <typename SimpleRule, typename Document>
bool evaluate_aux(SimpleRule rule, Document document, boost::mpl::false_)
{
  typedef typename unwrap_parameter<SimpleRule>::type rule_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::parser::simple_rule_traits<rule_type> rule_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  GNTL_DEBUG_LOG("simple rule" << std::endl)

  typedef typename rule_traits::variable_type variable_type;

  variable_type var = rule_traits::variable(rule);

  GNTL_DEBUG_LOG("variable " << var << std::endl)

  typedef typename document_traits::property_type property_value_type;
  typedef typename unwrap_parameter<property_value_type>::type property_type;
  typedef concept::structure::property_traits<property_type> property_traits;
  if(rule_traits::comparator(rule) == gntl::rule_comparator::equal)
  {
    if(document_traits::has_property(document, var))
    {
      GNTL_DEBUG_LOG("variable exists" << std::endl)
      property_value_type property = document_traits::get_property(document, var);
      if(property_traits::has_value(property))
      {
        GNTL_DEBUG_LOG("property is not empty" << std::endl)
        GNTL_DEBUG_LOG("property value " << property_traits::value_as_string(property) << std::endl)
        return property_traits::value_as_string(property) == rule_traits::value(rule);
      }
    }
  }
  else
  {
    if(document_traits::has_property(document, var))
    {
      property_value_type property = document_traits::get_property(document, var);
      if(!property_traits::has_value(property))
        return true;
      else
        return property_traits::value_as_string(property) != rule_traits::value(rule);
    }  
  }
  return false;
}

template <typename CompositeRule, typename Document>
bool evaluate_aux(CompositeRule rule, Document document, boost::mpl::true_)
{
  typedef typename unwrap_parameter<CompositeRule>::type rule_type;
  typedef concept::parser::composite_rule_traits<rule_type> rule_traits;
  GNTL_DEBUG_LOG("composite rule" << std::endl)
  
  typedef typename rule_traits::rule_range rule_value_range;
  rule_value_range rules = rule_traits::rule_all(rule);
  typedef typename unwrap_parameter<rule_value_range>::type rule_range;
  typedef typename boost::range_iterator<rule_range>::type rule_iterator;

  bool empty = true;
  gntl::rule_operator_type operator_ = rule_traits::operator_(rule);
  bool r = (operator_ == gntl::rule_operator::and_);
  for(rule_iterator first = boost::begin(rules), last = boost::end(rules)
        ;first != last; ++first)
  {
    if(rule::evaluate(*first, document))
    {
      if(operator_ == gntl::rule_operator::and_)
        r &= true;
      else
        return true;
    }
    else
    {
      if(operator_ == gntl::rule_operator::and_)
        return false;
      else
        r |= false;
    }
    empty = false;
  }

  return r && !empty;
}

}

template <typename Rule, typename Document>
bool evaluate(Rule rule, Document document)
{
  typedef typename unwrap_parameter<Rule>::type rule_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::parser::rule_traits<rule_type> rule_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  if(rule_traits::is_composite(rule))
    return rule_detail::evaluate_aux(rule_traits::composite_rule(rule), document, boost::mpl::true_());
  else
    return rule_detail::evaluate_aux(rule_traits::simple_rule(rule), document, boost::mpl::false_());
}

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
