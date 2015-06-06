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

#ifndef GNTL_CONCEPT_STRUCTURE_COMPOUND_CONDITION_HPP
#define GNTL_CONCEPT_STRUCTURE_COMPOUND_CONDITION_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/structure/condition/condition_expression.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct compound_condition_traits
{
  typedef boost::mpl::false_ is_compound_condition;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct CompoundCondition
{
  typedef compound_condition_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_compound_condition::value, ==, true);

  // From Compound Condition
  typedef typename traits::operator_type operator_type;
  typedef typename traits::delay_type delay_type;
  typedef typename traits::condition_range condition_range;
  
  BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<condition_range>));
  typedef typename boost::range_value<condition_range>::type condition_type;
  BOOST_CONCEPT_ASSERT((ConditionExpression<condition_type>));

  BOOST_CONCEPT_USAGE(CompoundCondition)
  {
    // From Compound Condition
    convertible_to<operator_type>(traits::operator_ (i));
    convertible_to<delay_type>(traits::delay (i));
    convertible_to<bool>(traits::has_delay(i));
    convertible_to<condition_range>(traits::condition_all(i));
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
