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

#ifndef GNTL_ARCHETYPE_PARSER_LINK_HPP
#define GNTL_ARCHETYPE_PARSER_LINK_HPP

#include <gntl/concept/parser/link/link.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/range.hpp>

#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Bind, typename LinkParam>
struct link
{
};

} } 

namespace concept { namespace parser {

template <typename Bind, typename LinkParam>
struct link_traits<archetype::parser::link<Bind, LinkParam> >
{
  typedef archetype::parser::link<Bind, LinkParam> link;
  typedef boost::mpl::true_ is_link;
  struct identifier_type {};
  struct xconnector_type {};
  typedef boost::iterator_range<boost::input_iterator_archetype<Bind> > bind_range;
  typedef boost::iterator_range<boost::input_iterator_archetype<LinkParam> > link_param_range;

  static identifier_type identifier(link);
  static bool has_identifier(link);
  static xconnector_type xconnector(link);
  static bind_range bind(link);
  static link_param_range link_param(link);
};

} } }

#endif
