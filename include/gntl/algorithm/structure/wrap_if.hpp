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

#ifndef GNTL_ALGORITHM_STRUCTURE_WRAP_IF_HPP
#define GNTL_ALGORITHM_STRUCTURE_WRAP_IF_HPP

#include <gntl/ref.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure {

template <typename P, typename T>
struct wrapper_if
 : boost::mpl::if_<P, gntl::reference_wrapper<T>, T>
{};

template <bool P, typename T>
struct wrapper_if_c
 : boost::mpl::if_c<P, gntl::reference_wrapper<T>, T>
{};

template <typename P, typename T>
gntl::reference_wrapper<T> wrap_if(T& object, typename boost::enable_if<P, void>::type* = 0)
{
  return gntl::ref(object);
}

template <typename P, typename T>
T wrap_if(T object, typename boost::disable_if<P, void>::type* = 0)
{
  return object;
}

template <bool P, typename T>
gntl::reference_wrapper<T> wrap_if(T& object, typename boost::enable_if_c<P, void>::type* = 0)
{
  return gntl::ref(object);
}

template <bool P, typename T>
T wrap_if(T object, typename boost::disable_if_c<P, void>::type* = 0)
{
  return object;
}

} } }

#include <gntl/detail/pop_options.hpp>

#endif
