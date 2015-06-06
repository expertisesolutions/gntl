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

#ifndef GNTL_ARCHETYPE_PARSER_RULE_HPP
#define GNTL_ARCHETYPE_PARSER_RULE_HPP

#include <gntl/concept_check.hpp>
#include <gntl/archetype/parser/rule_fwd.hpp>
#include <gntl/concept/parser/rule/rule.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename SimpleRule, typename CompositeRule>
struct rule
{
};

} }

namespace concept { namespace parser {

template <typename SimpleRule, typename CompositeRule>
struct rule_traits<gntl::archetype::parser::rule<SimpleRule, CompositeRule> >
{
  typedef gntl::archetype::parser::rule<SimpleRule, CompositeRule> rule;

  typedef boost::mpl::true_ is_rule;
  struct identifier_type {};
  typedef SimpleRule simple_rule_type;
  typedef CompositeRule composite_rule_type;

  static identifier_type identifier(rule);
  static bool is_composite(rule);
  static SimpleRule simple_rule(rule);
  static CompositeRule composite_rule(rule);
};

} } }

#endif
