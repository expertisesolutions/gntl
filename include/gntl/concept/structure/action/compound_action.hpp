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

#ifndef GNTL_CONCEPT_STRUCTURE_ACTION_COMPOUND_ACTION_HPP
#define GNTL_CONCEPT_STRUCTURE_ACTION_COMPOUND_ACTION_HPP

#include <gntl/concept/structure/action/action_expression.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct compound_action_traits
{
  typedef boost::mpl::false_ is_compound_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct CompoundAction
{
  typedef compound_action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_compound_action::value, ==, true);
  typedef typename traits::action_range action_range;

  typedef typename boost::range_value<action_range>::type action_type;
  BOOST_CONCEPT_ASSERT((ActionExpression<action_type>));

  BOOST_CONCEPT_USAGE(CompoundAction)
  {
    convertible_to<action_range>(traits::action_all(i));
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
