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

#ifndef GNTL_CONCEPT_LOOKUPABLE_HPP
#define GNTL_CONCEPT_LOOKUPABLE_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept {

template <typename T, typename Enable = void>
struct lookupable_traits
{
  typedef boost::mpl::false_ is_lookupable;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Lookupable// : boost::CopyConstructible<X>, boost::Assignable<X>
{
  typedef lookupable_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_lookupable::value, ==, true);
  typedef typename traits::key_type key_type;
  typedef typename traits::result_type result_type;
  typedef typename traits::value_type value_type;

  BOOST_CONCEPT_USAGE(Lookupable)
  {
    convertible_to<result_type>(traits::lookup(i, key));
    convertible_to<result_type>(traits::not_found(i));
    convertible_to<value_type>(*p);
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  Lookupable();

  result_type p;
  key_type key;
  X i;
};
#endif
} }


#include <gntl/detail/pop_options.hpp>

#endif
