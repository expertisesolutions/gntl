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

#ifndef GNTL_ARCHETYPE_PARSER_TRANSITION_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_TRANSITION_BASE_HPP

#include <gntl/concept/parser/transition/transition_base.hpp>
#include <gntl/concept_check.hpp>
#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Transition>
struct transition_base
{
};

} }

namespace concept { namespace parser {

template <typename Transition>
struct transition_base_traits<gntl::archetype::parser::transition_base<Transition> >
{
  typedef gntl::archetype::parser::transition_base<Transition> transition_base;
  typedef boost::mpl::true_ is_transition_base;
  struct identifier_type {};
  typedef boost::forward_iterator_archetype<Transition> transition_iterator;
  typedef boost::iterator_range<transition_iterator> transition_range;
  
  static identifier_type identifier (transition_base);
  static bool has_identifier (transition_base);
  static transition_range transition_all (transition_base);
};

} } }

#endif
