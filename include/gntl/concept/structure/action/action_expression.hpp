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

#ifndef GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_EXPRESSION_HPP
#define GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_EXPRESSION_HPP

#include <gntl/concept/structure/action/action.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_convertible.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct action_expression_traits
{
  typedef boost::mpl::false_ is_action_expression;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ActionExpression
{
  typedef action_expression_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_action_expression::value, ==, true);
  typedef typename traits::action_list_type action_list_type;

  BOOST_CONCEPT_USAGE(ActionExpression)
  {
    check_get(boost::mpl::identity
              <typename boost::mpl::begin<action_list_type>::type>()
              , boost::mpl::identity
              <typename boost::mpl::end<action_list_type>::type>());
  }

  template <typename Iter, typename End>
  void check_get(Iter iter, End end
                 , typename boost::disable_if
                 <boost::is_same<typename Iter::type
                                 , typename End::type>, void>::type* = 0
                 )
  {
    typedef typename boost::mpl::deref<typename Iter::type>::type
      value_type;
    convertible_to<bool>(traits::template is_type<value_type>(i));
    convertible_to<value_type>(traits::template get<value_type>(i));
    check_get(boost::mpl::identity
              <typename boost::mpl::next<typename Iter::type>::type>()
              , end);
    BOOST_CONCEPT_ASSERT((Action<value_type>));
  }

  template <typename Iter, typename End>
  void check_get(Iter iter, End end
                 , typename boost::enable_if
                 <boost::is_same<typename Iter::type
                                 , typename End::type>, void>::type* = 0
                 )
  {
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
};
#endif
} } }

#endif
