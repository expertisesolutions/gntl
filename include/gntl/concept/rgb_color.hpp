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

#ifndef GNTL_CONCEPT_COLOR_HPP
#define GNTL_CONCEPT_COLOR_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept {

template <typename T>
struct rgb_color_traits
{
  typedef boost::mpl::false_ is_rgb_color;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct RGB_Color : boost::CopyConstructible<X>
  , boost::EqualityComparable<X>, boost::Assignable<X>
{
  typedef rgb_color_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_rgb_color::value, ==, true);

  BOOST_CONCEPT_USAGE(RGB_Color)
  {
    
  }

  X i;
};
#endif
} }


#include <gntl/detail/pop_options.hpp>

#endif
