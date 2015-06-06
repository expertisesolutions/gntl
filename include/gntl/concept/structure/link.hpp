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

#ifndef GNTL_CONCEPT_STRUCTURE_LINK_HPP
#define GNTL_CONCEPT_STRUCTURE_LINK_HPP

#include <gntl/concept/structure/condition/condition_expression.hpp>
#include <gntl/concept/structure/action/action_expression.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct link_traits
{
  typedef boost::mpl::false_ is_link;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Link
{
  typedef link_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_link::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::condition_expression_type condition_expression_type;
  typedef typename traits::action_expression_type action_expression_type;

  BOOST_CONCEPT_ASSERT((ConditionExpression<condition_expression_type>));
  BOOST_CONCEPT_ASSERT((ActionExpression<action_expression_type>));
    
  BOOST_CONCEPT_USAGE (Link)
  {
    convertible_to<identifier_type>(traits::identifier (const_i));
    convertible_to<bool>(traits::has_identifier (const_i));
    convertible_to<condition_expression_type>(traits::condition_expression(i));
    convertible_to<action_expression_type>(traits::action_expression(const_i));
  }

  template <typename To, typename From>
  void convertible_to (From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
  X const const_i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
