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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_INTERFACE_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_INTERFACE_HPP

#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept/structure/media.hpp>

#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

namespace media_detail {

template <typename I>
struct area_identifier_predicate
{
  area_identifier_predicate(I i)
    : i (i) {}
  typedef bool result_type;
  template <typename Area>
  bool operator()(Area a) const
  {
    typedef typename boost::unwrap_reference<Area>::type area_type;
    typedef gntl::concept::parser::area_traits<area_type> area_traits;
    GNTL_CONCEPT_ASSERT((gntl::concept::parser::Area<area_type>));
    return area_traits::identifier(a) == i;
  }
  I i;
};

}

template <typename Media, typename Interface>
bool has_interface(Media media, Interface interface_)
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef gntl::concept::structure::media_traits<media_type> media_traits;
  typedef typename media_traits::area_range area_range;
  area_range areas = concept::area(media);
  return gntl::range::find_if(areas, media_detail::area_identifier_predicate<Interface>(interface_))
    != boost::end(areas);
}

template <typename Media, typename Interface>
bool interface_active (Media media, Interface interface_);
// {
//   typedef typename boost::unwrap_reference<Media>::type media_type;
//   typedef gntl::concept::parser::has_area_traits<media_type>
//     area_traits;
//   typedef typename area_traits::area_range
//     area_range;
//   area_range areas = area_traits::area(media);

//   typedef typename boost::range_iterator<area_range>::type
//     area_iterator;

//   area_iterator area_it = boost::range::find_if
//     (areas, media_detail::area_identifier_predicate<Interface>(interface_));

//   if(area_it != boost::end(areas))
//   {
//     typedef typename boost::range_value<area_range>::type
//       area_type;
//     typedef gntl::concept::parser::area_traits<area_type> traits;
//     typedef gntl::concept::structure::media_traits<media_type> structure_media_traits;
//     typedef typename structure_media_traits::executor_type executor_type;
//     typedef gntl::concept::structure::executor_traits<executor_type> executor_traits;

//     area_type area = *area_it;

//     if(traits::has_begin(area))
//     {
//       if(traits::has_end(area))
//       {
//         return executor_traits::time_area_active_between
//           (structure_media_traits::executor(media), traits::begin(area), traits::end(area));
//       }
//       else
//       {
//         return executor_traits::time_area_active_after
//           (structure_media_traits::executor(media), traits::begin(area));
//       }
//     }
//     else if(traits::has_end(area))
//     {
//       return executor_traits::time_area_active_before
//         (structure_media_traits::executor(media), traits::end(area));
//     }

//     return false;
//   }
//   else
//     return false;
// }

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
