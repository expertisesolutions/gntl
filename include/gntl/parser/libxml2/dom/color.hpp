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

#ifndef GNTL_PARSER_LIBXML2_DOM_COLOR_HPP
#define GNTL_PARSER_LIBXML2_DOM_COLOR_HPP

#include <gntl/concept/rgb_color.hpp>

#include <boost/integer.hpp>
#include <boost/mpl/bool.hpp>

#include <ostream>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct color
{
  typedef boost::uint_t<8>::least channel_type;
  color(channel_type r, channel_type g, channel_type b)
    : r(r), g(g), b(b) {}
  color()
    : r(0), g(0), b(0) {}
  channel_type r,g,b;
};

inline bool operator==(color const& lhs, color const& rhs)
{
  return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

inline bool operator!=(color const& lhs, color const& rhs)
{
  return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& s, color c)
{
  unsigned int red = c.r;
  unsigned int green = c.g;
  unsigned int blue = c.b;
  return s << "[R: " << red << " G: " << green << " B: " << blue << ']';
}

} } }

namespace concept {

template <>
struct rgb_color_traits<gntl::parser::libxml2::dom::color>
{
  typedef boost::mpl::true_ is_rgb_color;
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
