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

#ifndef GNTL_CONCEPT_PARSER_COORDINATE_HPP
#define GNTL_CONCEPT_PARSER_COORDINATE_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct coordinate_traits
{
  typedef boost::mpl::false_ is_coordinate;
};

/*
template <typename T>
struct coordinate_traits
{
  typedef typename T::pixel_type pixel_type;
  typedef typename T::percentage_type percentage_type;
};
*/
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Coordinate
{
  typedef coordinate_traits<X> traits;
  typedef typename traits::pixel_type pixel_type;
  typedef typename traits::percentage_type percentage_type;

  BOOST_CONCEPT_USAGE(Coordinate)
  {
    convertible_to<bool>(traits::is_percentual(i));
    convertible_to<pixel_type>(traits::pixel(i));
    convertible_to<percentage_type>(traits::percentage(i));
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
