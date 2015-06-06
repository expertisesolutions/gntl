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

#ifndef GNTL_ARCHETYPE_PARSER_RULE_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_RULE_BASE_HPP

#include <gntl/concept/parser/rule/rule_base.hpp>
#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Rule>
struct rule_base
{
};

} }

namespace concept { namespace parser {

template <typename Rule>
struct rule_base_traits<archetype::parser::rule_base<Rule> >
{
  typedef archetype::parser::rule_base<Rule> rule_base;

  typedef boost::mpl::true_ is_rule_base;
  struct identifier_type {};
  typedef boost::forward_iterator_archetype<Rule> rule_iterator;
  typedef boost::iterator_range<rule_iterator> rule_range;

  static rule_range rule (rule_base);
  static bool has_identifier (rule_base);
  static identifier_type identifier(rule_base);
  static rule_range rule_all(rule_base);
};

} } }

#endif
