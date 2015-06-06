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

#ifndef GNTL_ARCHETYPE_PARSER_COMPOSITE_RULE_HPP
#define GNTL_ARCHETYPE_PARSER_COMPOSITE_RULE_HPP

#include <gntl/rule_operator.hpp>
#include <gntl/archetype/parser/rule_fwd.hpp>
#include <gntl/concept/parser/rule/composite_rule.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename SimpleRule>
struct composite_rule
{
};

} }

namespace concept { namespace parser {

template <typename SimpleRule>
struct composite_rule_traits<archetype::parser::composite_rule<SimpleRule> >
{
  typedef archetype::parser::composite_rule<SimpleRule> composite_rule;

  typedef boost::mpl::true_ is_composite_rule;
  struct identifier_type {};
  struct operator_type {};
  typedef gntl::archetype::parser::rule<SimpleRule, composite_rule> rule_type;
  typedef boost::forward_iterator_archetype<rule_type> rule_iterator;
  typedef boost::iterator_range<rule_iterator> rule_range;

  static identifier_type identifier (composite_rule);
  static operator_type operator_ (composite_rule);
  static rule_range rule_all(composite_rule);
};

} } }

#endif
