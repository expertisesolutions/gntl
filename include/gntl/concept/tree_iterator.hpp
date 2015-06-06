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

#ifndef GNTL_TREE_ITERATOR_HPP
#define GNTL_TREE_ITERATOR_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#ifndef GNTL_DISABLE_CONCEPTS
#include <gntl/concept_check.hpp>
#endif

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept {

template <typename Iterator>
struct tree_iterator_traits
{
  typedef boost::mpl::false_ is_tree_iterator;
};

/*
template <>
struct tree_iterator_traits<ns::iterator>
{
  typedef some_iterator_type node_iterator;
  typedef ns::iterator iterator;
  
  static node_iterator begin(node_iterator);
  static node_iterator end(node_iterator);
  static node_iterator node(ns::iterator);
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct TreeIterator
{
  typedef tree_iterator_traits<X> traits_type;
  BOOST_MPL_ASSERT_RELATION(traits_type::is_tree_iterator::value, ==, true);
  typedef typename traits_type::iterator iterator;
  typedef typename traits_type::node_iterator node_iterator;

  BOOST_MPL_ASSERT((boost::is_same<X, iterator>));
  
  BOOST_CONCEPT_USAGE(TreeIterator)
  {
    convertible_to<node_iterator>(traits_type::node(i));
    convertible_to<node_iterator>(traits_type::begin(node_it));
    convertible_to<node_iterator>(traits_type::end(node_it));
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  node_iterator node_it;
  X i;
};
#endif

} }


#include <gntl/detail/pop_options.hpp>

#endif
