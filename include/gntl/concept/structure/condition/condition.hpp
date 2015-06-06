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

#ifndef GNTL_CONCEPT_STRUCTURE_CONDITION_CONDITION_HPP
#define GNTL_CONCEPT_STRUCTURE_CONDITION_CONDITION_HPP

#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/condition/bound_assessment_statement.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

namespace gntl { namespace concept { namespace structure {

struct simple_condition_tag {};
struct compound_condition_tag {};
struct assessment_statement_tag {};
struct compound_statement_tag {};

template <typename T>
struct condition_traits
{
  typedef boost::mpl::false_ is_condition;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Condition
{
  typedef condition_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_condition::value, ==, true);
  typedef typename traits::category_tag category_tag;

  void check_specific(simple_condition_tag)
  {
    BOOST_CONCEPT_ASSERT((BoundedSimpleCondition<X>));
  }

  void check_specific(assessment_statement_tag)
  {
    BOOST_CONCEPT_ASSERT((BoundAssessmentStatement<X>));
  }

  template <typename Tag>
  void check_specific(Tag)
  {
  }

  BOOST_CONCEPT_USAGE(Condition)
  {
    check_specific(category_tag());
  }
};
#endif
} } }

#endif
