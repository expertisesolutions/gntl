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

#ifndef GNTL_STRUCTURE_COMPOSED_BIND_RULE_HPP
#define GNTL_STRUCTURE_COMPOSED_BIND_RULE_HPP

#include <gntl/concept/parser/switch/bind_rule.hpp>
#include <gntl/concept/structure/bind_rule.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserBindRule>
struct bind_rule : ParserBindRule
{
  bind_rule(ParserBindRule base)
    : ParserBindRule(base) {}
  bind_rule() {}
};

} }

namespace concept { namespace structure {

template <typename ParserBindRule>
struct bind_rule_traits<gntl::structure::composed::bind_rule<ParserBindRule> >
  : concept::parser::bind_rule_traits<ParserBindRule>
{};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
