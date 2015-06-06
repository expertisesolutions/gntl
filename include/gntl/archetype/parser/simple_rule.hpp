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

#ifndef GNTL_ARCHETYPE_PARSER_SIMPLE_RULE_HPP
#define GNTL_ARCHETYPE_PARSER_SIMPLE_RULE_HPP

#include <gntl/concept/parser/rule/simple_rule.hpp>

namespace gntl { namespace archetype { namespace parser {

struct simple_rule
{
};

} }

namespace concept { namespace parser {

template <>
struct simple_rule_traits<gntl::archetype::parser::simple_rule>
{
  typedef gntl::archetype::parser::simple_rule simple_rule;

  typedef boost::mpl::true_ is_simple_rule;
  struct identifier_type {};
  struct variable_type {};
  struct value_type {};
  struct comparator_type {};

  static identifier_type identifier (simple_rule);
  static variable_type variable (simple_rule);
  static value_type value (simple_rule);
  static comparator_type comparator (simple_rule);
};

} } }

#endif
