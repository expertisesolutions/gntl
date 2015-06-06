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

#ifndef GNTL_CONCEPT_STRUCTURE_ACTION_BOUND_SIMPLE_ACTION_HPP
#define GNTL_CONCEPT_STRUCTURE_ACTION_BOUND_SIMPLE_ACTION_HPP

#include <gntl/concept/structure/action/action_bound_component.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct bound_simple_action_traits
{
  typedef boost::mpl::false_ is_bound_simple_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct BoundSimpleAction
{
  typedef bound_simple_action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_bound_simple_action::value, ==, true);
  // From Simple Action
  typedef typename traits::role_type role_type;
  typedef typename traits::event_type_type event_type_type;
  typedef typename traits::action_type_type action_type_type;
  typedef typename traits::component_range component_range;
  typedef typename traits::min_type min_type;
  typedef typename traits::max_type max_type;

  BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<component_range>));
  typedef typename boost::range_value<component_range>::type component_type;
  BOOST_CONCEPT_ASSERT((ActionBoundComponent<component_type>));

  BOOST_CONCEPT_USAGE(BoundSimpleAction)
  {
    // From Simple Action
    convertible_to<role_type>(traits::role(i));
    convertible_to<bool>(traits::has_event_type(i));
    convertible_to<event_type_type>(traits::event_type(i));
    convertible_to<bool>(traits::has_action_type(i));
    convertible_to<action_type_type>(traits::action_type(i));
    convertible_to<component_range>(traits::component_all(i));
    convertible_to<bool>(traits::has_min(i));
    convertible_to<min_type>((traits::min)(i));
    convertible_to<bool>(traits::has_max(i));
    convertible_to<max_type>((traits::max)(i));
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

