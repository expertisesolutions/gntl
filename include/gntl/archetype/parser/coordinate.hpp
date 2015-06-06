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

#ifndef GNTL_ARCHETYPE_PARSER_COORDINATE_HPP
#define GNTL_ARCHETYPE_PARSER_COORDINATE_HPP

#include <gntl/concept/parser/region/coordinate.hpp>

namespace gntl { namespace archetype { namespace parser {

struct coordinate
{
};

} }

namespace concept { namespace parser {

template <>
struct coordinate_traits<archetype::parser::coordinate>
{
  typedef boost::mpl::true_ is_coordinate;
  typedef archetype::parser::coordinate coordinate;
  struct pixel_type {};
  struct percentage_type {};

  static bool is_percentual (coordinate);
  static pixel_type pixel (coordinate);
  static percentage_type percentage (coordinate);
};

} } }

#endif
