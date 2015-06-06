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

#ifndef GNTL_ARCHETYPE_RGB_COLOR_HPP
#define GNTL_ARCHETYPE_RGB_COLOR_HPP

#include <gntl/concept/rgb_color.hpp>

namespace gntl { namespace archetype {

struct rgb_color
{
};

bool operator==(rgb_color, rgb_color);
bool operator!=(rgb_color, rgb_color);

}

namespace concept {

template <>
struct rgb_color_traits<archetype::rgb_color>
{
  typedef boost::mpl::true_ is_rgb_color;
};

} }

#endif
