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

#ifndef GNTL_ARCHETYPE_PARSER_BIND_RULE_HPP
#define GNTL_ARCHETYPE_PARSER_BIND_RULE_HPP

#include <gntl/concept/parser/switch/bind_rule.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

struct bind_rule
{
};

} }

namespace concept { namespace parser {

template <>
struct bind_rule_traits<archetype::parser::bind_rule>
{
  typedef archetype::parser::bind_rule bind_rule;
  typedef boost::mpl::true_ is_bind_rule;
  struct constituent_type {};
  struct rule_type {};

  static constituent_type constituent(bind_rule);
  static rule_type rule(bind_rule);
};

} } }

#endif
