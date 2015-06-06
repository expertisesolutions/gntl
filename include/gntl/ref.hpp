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

#ifndef GNTL_REF_HPP
#define GNTL_REF_HPP

#include <boost/ref.hpp>
#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl {

template <typename T>
struct reference_wrapper : boost::reference_wrapper<T>
{
  typedef boost::reference_wrapper<T> base_type;
  explicit reference_wrapper(T& t) : base_type(t) {}
};

template <typename T>
inline reference_wrapper<T> ref(T& t)
{
  return reference_wrapper<T>(t);
}

template <typename T>
inline reference_wrapper<T const> cref(T const& t)
{
  return reference_wrapper<T const>(t);
}

template <typename T>
typename boost::enable_if
<boost::is_reference_wrapper<T>
 , T>::type
ref_once(T t)
{
  return t;
}

template <typename T>
typename boost::disable_if
<boost::is_reference_wrapper<T>
 , gntl::reference_wrapper<T> >::type
ref_once(T& t)
{
  return gntl::ref(t);
}

template <typename T>
struct ref_once_meta
  : boost::mpl::if_
    <
      boost::is_reference_wrapper<T>
      , T
      , gntl::reference_wrapper<T>
    >
{};

template <typename T>
typename boost::enable_if<boost::is_reference_wrapper<T>, T>::type
cref_once(T t)
{
  return t;
}

template <typename T>
typename boost::disable_if<boost::is_reference_wrapper<T>, gntl::reference_wrapper<T const> >::type
cref_once(T const& t)
{
  return gntl::cref(t);
}

template <typename T>
typename boost::enable_if<boost::is_reference_wrapper<T>, T>::type
ref_if_by_ref(T t)
{
  return t;
}

template <typename T>
typename boost::disable_if<boost::is_reference_wrapper<T>, gntl::reference_wrapper<T> >::type
ref_if_by_ref(T& t)
{
  return gntl::ref(t);
}

template <typename T>
typename boost::disable_if<boost::is_reference_wrapper<T>, T>::type
ref_if_by_ref(T t)
{
  return t;
}

}

namespace boost {

template <typename T>
class is_reference_wrapper<gntl::reference_wrapper<T> >
  : public boost::mpl::true_
{};

template <typename T>
class unwrap_reference<gntl::reference_wrapper<T> >
{
public:
  typedef T type;
};

template <typename T>
class is_reference_wrapper<gntl::reference_wrapper<T> const>
  : public boost::mpl::true_
{};

template <typename T>
class unwrap_reference<gntl::reference_wrapper<T> const>
{
public:
  typedef T type;
};

template <typename T>
class is_reference_wrapper<gntl::reference_wrapper<T> volatile>
  : public boost::mpl::true_
{};

template <typename T>
class unwrap_reference<gntl::reference_wrapper<T> volatile>
{
public:
  typedef T type;
};

template <typename T>
class is_reference_wrapper<gntl::reference_wrapper<T> const volatile>
  : public boost::mpl::true_
{};

template <typename T>
class unwrap_reference<gntl::reference_wrapper<T> const volatile>
{
public:
  typedef T type;
};

}

#include <gntl/detail/pop_options.hpp>

#endif
