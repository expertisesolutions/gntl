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

#ifndef GNTL_CONCEPT_STRUCTURE_BOUND_ASSESSMENT_STATEMENT_HPP
#define GNTL_CONCEPT_STRUCTURE_BOUND_ASSESSMENT_STATEMENT_HPP

#include <gntl/concept/structure/condition/bound_attribute_assessment.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_convertible.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct bound_assessment_statement_traits
{
  typedef boost::mpl::false_ is_bound_assessment_statement;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct BoundAssessmentStatement
{
  typedef bound_assessment_statement_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_bound_assessment_statement::value, ==, true);
  typedef typename traits::value_assessment_type value_assessment_type;
  typedef typename traits::attribute_assessment_type attribute_assessment_type;

  BOOST_CONCEPT_ASSERT((BoundAttributeAssessment<attribute_assessment_type>));

  BOOST_CONCEPT_USAGE(BoundAssessmentStatement)
  {
    convertible_to<attribute_assessment_type>(traits::first(i));
    convertible_to<attribute_assessment_type>
      (traits::template second
       <attribute_assessment_type>(i));
    convertible_to<value_assessment_type>
      (traits::template second
       <value_assessment_type>(i));
    convertible_to<bool>
      (traits::template is_second<attribute_assessment_type>(i));
    convertible_to<bool>
      (traits::template is_second<value_assessment_type>(i));
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
