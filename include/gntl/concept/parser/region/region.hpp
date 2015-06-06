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

#ifndef GNTL_CONCEPT_PARSER_REGION_HPP
#define GNTL_CONCEPT_PARSER_REGION_HPP

#include <gntl/concept/parser/region/coordinate.hpp>
#include <gntl/concept_check.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct region_traits
{
  typedef boost::mpl::false_ is_region;
};

/*
template <>
struct region_traits<region-type>
{
    typedef typename T::identifier_type identifier_type;
    typedef typename T::title_type title_type;
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::zindex_type zindex_type;
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Region
{
    typedef region_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_region::value, == , true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::title_type title_type;
    typedef typename traits::coordinate_type coordinate_type;
    typedef typename traits::zindex_type zindex_type;

    BOOST_CONCEPT_ASSERT ((Coordinate<coordinate_type>));

    BOOST_CONCEPT_USAGE (Region)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<bool>(traits::has_title (i));
        convertible_to<title_type>(traits::title (i));
        convertible_to<bool>(traits::has_left (i));
        convertible_to<bool>(traits::has_right (i));
        convertible_to<bool>(traits::has_top (i));
        convertible_to<bool>(traits::has_bottom (i));
        convertible_to<bool>(traits::has_height (i));
        convertible_to<bool>(traits::has_width (i));
        convertible_to<bool>(traits::has_zindex (i));
        convertible_to<coordinate_type>(traits::left (i));
        convertible_to<coordinate_type>(traits::right (i));
        convertible_to<coordinate_type>(traits::top (i));
        convertible_to<coordinate_type>(traits::bottom (i));
        convertible_to<coordinate_type>(traits::height (i));
        convertible_to<coordinate_type>(traits::width (i));
        convertible_to<zindex_type>(traits::zindex (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1, T0>));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
