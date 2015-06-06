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

#ifndef GNTL_UNWRAP_PARAMETER_HPP
#define GNTL_UNWRAP_PARAMETER_HPP

#include <gntl/ref.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_const.hpp>
#include <gntl/detail/push_options.hpp>

namespace gntl {

template <typename P>
struct unwrap_parameter
  : 
    boost::remove_cv
    <
      typename boost::remove_reference
      <
        typename boost::unwrap_reference
        <
          typename boost::remove_cv
          <
            typename boost::remove_reference<P>::type
          >::type
        >::type
      >::type
    >
{};

template <typename P>
struct is_parameter_const
  : boost::is_const
    <
      typename boost::unwrap_reference
      <
        typename boost::remove_reference<P>::type
      >::type
    >::type
{};

}

#include <gntl/detail/pop_options.hpp>

#endif
