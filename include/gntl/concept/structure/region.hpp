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

#ifndef GNTL_CONCEPT_STRUCTURE_REGION_HPP
#define GNTL_CONCEPT_STRUCTURE_REGION_HPP

#include <gntl/concept/parser/region/region.hpp>
#include <gntl/concept_check.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct region_traits
{
  typedef typename T::identifier_type identifier_type;
  typedef typename T::title_type title_type;
  typedef typename T::coordinate_type coordinate_type;
  typedef typename T::zindex_type zindex_type;
};

namespace region {

template <typename Region>
typename region_traits<Region>::identifier_type identifier(Region const& r)
{
  return region_identifier(r);
}

template <typename Region>
bool has_title(Region const& r)
{
  return  region_has_title(r);
}

template <typename Region>
typename region_traits<Region>::identifier_type title(Region const& r)
{
  return region_title(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type left(Region const& r)
{
  return region_left(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type right(Region const& r)
{
  return region_right(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type top(Region const& r)
{
  return region_top(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type bottom(Region const& r)
{
  return region_bottom(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type height(Region const& r)
{
  return region_height(r);
}

template <typename Region>
typename region_traits<Region>::coordinate_type width(Region const& r)
{
  return region_width(r);
}

template <typename Region>
typename region_traits<Region>::zindex_type zindex(Region const& r)
{
  return region_zindex(r);
}

}
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Region
{
    typedef typename region_traits<X>::identifier_type identifier_type;
    typedef typename region_traits<X>::title_type title_type;
    typedef typename region_traits<X>::coordinate_type coordinate_type;
    typedef typename region_traits<X>::zindex_type zindex_type;

    BOOST_CONCEPT_USAGE (Region)
    {
        convertible_to<identifier_type>(region::identifier (i));
        convertible_to<bool>(region::has_title (i));
        convertible_to<title_type>(region::title (i));
        convertible_to<coordinate_type>(region::left (i));
        convertible_to<coordinate_type>(region::right (i));
        convertible_to<coordinate_type>(region::top (i));
        convertible_to<coordinate_type>(region::bottom (i));
        convertible_to<coordinate_type>(region::height (i));
        convertible_to<coordinate_type>(region::width (i));
        convertible_to<zindex_type>(region::zindex (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_STATIC_ASSERT ((boost::is_convertible<T1, T0>::type::value));
    }

    X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
