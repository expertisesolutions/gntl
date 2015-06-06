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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_CALCULATE_FOCUSED_BORDER_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_CALCULATE_FOCUSED_BORDER_HPP

#include <gntl/concept/structure/descriptor.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Presentation, typename Descriptor>
std::pair
<typename concept::structure::descriptor_traits
 <typename boost::unwrap_reference<Descriptor>::type>
::width_type
 , typename concept::structure::descriptor_traits
 <typename boost::unwrap_reference<Descriptor>::type>
 ::color_type>
calculate_focused_border(Presentation p, Descriptor descriptor, bool selected)
{
  typedef typename boost::unwrap_reference<Descriptor>::type descriptor_type;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  typedef typename descriptor_traits::color_type color_type;
  typedef typename descriptor_traits::width_type width_type;
  {
    width_type size = 1;
    if(descriptor_traits::has_focus_border_width(descriptor))
      size = descriptor_traits::focus_border_width(descriptor);
    color_type color (0u, 0u, 0xFFu);
    if(!selected && descriptor_traits::has_focus_border_color(descriptor))
      color = descriptor_traits::focus_border_color(descriptor);
    else if(selected && descriptor_traits::has_selection_border_color(descriptor))
      color = descriptor_traits::selection_border_color(descriptor);
    return std::make_pair(size, color);
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
