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

#ifndef GNTL_CONCEPT_PARSER_AREA_HPP
#define GNTL_CONCEPT_PARSER_AREA_HPP

#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct area_traits
{
  typedef boost::mpl::false_ is_area;
};

/*
template <typename T>
struct area_traits
{
    typedef typename T::identifier_type identifier_type;
    typedef typename T::coordinate_type coordinate_type;
    typedef typename T::begin_type begin_type;
    typedef typename T::end_type end_type;
    typedef typename T::text_type text_type;
    typedef typename T::first_type first_type;
    typedef typename T::last_type last_type;
    typedef typename T::label_type label_type;
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Area
{
    typedef area_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_area::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::coordinate_type coordinate_type;
    typedef typename traits::time_type time_type;
    typedef typename traits::text_type text_type;
    typedef typename traits::frame_type frame_type;
    typedef typename traits::label_type label_type;

    BOOST_CONCEPT_USAGE(Area)
    {
      convertible_to<identifier_type>(traits::identifier(i));
      convertible_to<bool>(traits::has_begin(i));
      convertible_to<time_type>(traits::begin(i));
      convertible_to<bool>(traits::has_end(i));
      convertible_to<time_type>(traits::end(i));
      convertible_to<bool>(traits::has_first(i));
      convertible_to<frame_type>(traits::first(i));
      convertible_to<bool>(traits::has_last(i));
      convertible_to<frame_type>(traits::last(i));
    }

    X i;

    template <typename To, typename From>
    void convertible_to(From const&)
    {
      BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
    }
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
