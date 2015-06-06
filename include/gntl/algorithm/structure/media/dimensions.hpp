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

#ifndef GNTL_ALGORITHM_MEDIA_STRUCTURE_DIMENSIONS_HPP
#define GNTL_ALGORITHM_MEDIA_STRUCTURE_DIMENSIONS_HPP

#include <gntl/algorithm/parser/region.hpp>
#include <gntl/algorithm/structure/document.hpp>

#include <boost/utility/value_init.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/optional.hpp>

#include <ostream>
#include <numeric>
#include <cassert>
#include <vector>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

struct dimensions
{
    std::size_t x,y,width,height;
    int zindex;
};

inline bool operator==(dimensions const& lhs, dimensions const& rhs)
{
  return lhs.x == rhs.x
    && lhs.y == rhs.y
    && lhs.width == rhs.width
    && lhs.height == rhs.height
    && lhs.zindex == rhs.zindex;
}

inline std::ostream& operator<<(std::ostream& s, dimensions const& d)
{
  return s << "{ x: " 
           << d.x << " y: " << d.y
           << " w: " << d.width
           << " h: " << d.height
           << " z: " << d.zindex << " }";
}

namespace calculate_dimensions_detail {

template <typename Coordinate>
std::size_t absolute(Coordinate c, std::size_t size)
{
  typedef concept::parser::coordinate_traits<Coordinate> traits;
  if(traits::is_percentual(c))
    return traits::percentage(c)*size;
  else
  {
    return traits::pixel(c);
  }
}

template <typename Top, typename Size, typename Bottom
          , typename TopPredicate, typename SizePredicate, typename BottomPredicate
          , typename Region>
std::pair<std::size_t, std::size_t>
calculate (std::size_t const top, std::size_t const size
           , Top get_top, Size get_size, Bottom get_bottom
           , TopPredicate top_pred, SizePredicate size_pred
           , BottomPredicate bottom_pred
           , Region region)
{
    std::size_t new_top = top, new_size = size;
    if(top_pred (region))
    {
      // top
      new_top = calculate_dimensions_detail::absolute
        (get_top (region), size) + top;

      if(size_pred(region))
        new_size = calculate_dimensions_detail::absolute
          (get_size (region), size);
      else if(bottom_pred (region))
      {
        std::size_t bottom_intermediate
          = calculate_dimensions_detail::absolute
          (get_bottom (region), size);
        std::size_t bottom = 
          size >= bottom_intermediate
          ?size - bottom_intermediate:0u;
        if(bottom > new_top)
          new_size = bottom - new_top;
      }
    }
    else
    {
      if(size_pred (region))
        new_size = calculate_dimensions_detail::absolute(get_size (region), size);

      if(bottom_pred (region))
      {
        std::size_t bottom_intermediate
          = calculate_dimensions_detail::absolute
          (get_bottom (region), size);
        std::size_t bottom = 
          size >= bottom_intermediate
          ?size - bottom_intermediate:0u;
        if(new_size >= bottom)
          new_size = bottom;
        new_top = top + bottom - new_size;
      }

	}
    if(new_top >= top + size)
      new_top = top+size;
    if(new_top + new_size >= top+size)
      new_size = top+size - new_top;
    assert(new_top >= top);
    assert(new_size <= size);
    return std::make_pair(new_top, new_size);
}

struct get_top
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::top(region);
  }
};

struct get_height
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::height(region);
  }
};

struct get_bottom
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::bottom (region);
  }
};

struct get_left
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::left (region);
  }
};

struct get_width
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::width (region);
  }
};

struct get_right
{
  template <typename Region>
  typename concept::parser::region_traits<Region>::coordinate_type
  operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::right (region);
  }
};

struct top_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_top (region);
  }
};

struct bottom_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_bottom (region);
  }
};

struct height_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_height (region);
  }
};

struct left_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_left (region);
  }
};

struct width_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_width (region);
  }
};

struct right_predicate
{
  template <typename Region>
  bool operator()(Region region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    return traits::has_right (region);
  }
};

}

struct calculate_dimensions
{
  dimensions* parent;

  calculate_dimensions(dimensions* parent = 0)
    : parent(parent)
  {}

  template <typename Region>
  dimensions operator()(dimensions d, Region const& region) const
  {
    typedef concept::parser::region_traits<Region> traits;
    typedef typename concept::parser::region_traits<Region>::coordinate_type
      coordinate;

    if(parent) {
      *parent = d;
    }

    std::size_t x = d.x, y = d.y
      , w = d.width, h = d.height;

    GNTL_DEBUG_LOG("Value from parent: " << d << std::endl)

    boost::tie (y, h)
      = calculate_dimensions_detail::calculate
      (d.y, d.height, calculate_dimensions_detail::get_top()
       , calculate_dimensions_detail::get_height()
       , calculate_dimensions_detail::get_bottom()
       , calculate_dimensions_detail::top_predicate()
       , calculate_dimensions_detail::height_predicate()
       , calculate_dimensions_detail::bottom_predicate()
       , region);
    assert(y >= d.y);
    assert(h <= d.height);
    assert(y + h <= d.y + d.height);

    boost::tie (x, w)
      = calculate_dimensions_detail::calculate
      (d.x, d.width, calculate_dimensions_detail::get_left()
       , calculate_dimensions_detail::get_width()
       , calculate_dimensions_detail::get_right()
       , calculate_dimensions_detail::left_predicate()
       , calculate_dimensions_detail::width_predicate()
       , calculate_dimensions_detail::right_predicate()
       , region);
    assert(x >= d.x);
    assert(w <= d.width);
    assert(x + w <= d.x + d.width);

    dimensions new_dimensions = {x, y, w, h
                                 , traits::has_zindex(region)
                                 ?traits::zindex(region)
                                 :d.zindex};

    GNTL_DEBUG_LOG("NEW value: " << new_dimensions << std::endl)
    return new_dimensions;
  }
};

template <typename RegionLookupable, typename RegionName>
boost::optional<dimensions>
calculate_dimensions_from_region_name(RegionLookupable regions
                                      , RegionName region_name
                                      , dimensions d
                                      , dimensions* parent = 0)
{
  typedef typename boost::unwrap_reference<RegionLookupable>::type region_lookupable;
  typedef concept::lookupable_traits<region_lookupable> region_lookupable_traits;
  typedef typename region_lookupable_traits::value_type region_range;
  typedef typename boost::range_value<region_range>::type region_type;

  typedef typename region_lookupable_traits::result_type result_type;
  result_type r = region_lookupable_traits::lookup(regions, region_name);
  if(r != region_lookupable_traits::not_found(regions))
  {
    region_range region_path = *r;
    d = std::accumulate(boost::begin(region_path), boost::end(region_path), d, calculate_dimensions(parent));
    return d;
  }
  else
  {
    GNTL_DEBUG_LOG("Not found region" << std::endl)
    return boost::none;
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
