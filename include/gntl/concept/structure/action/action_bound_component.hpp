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

#ifndef GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_BOUND_COMPONENT_HPP
#define GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_BOUND_COMPONENT_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct action_bound_component_traits
{
  typedef boost::mpl::false_ is_action_bound_component;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ActionBoundComponent
{
  typedef action_bound_component_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_action_bound_component::value, ==, true);
  typedef typename traits::delay_type delay_type;
  typedef typename traits::string_type string_type;
  typedef typename traits::qualifier_type qualifier_type;
  typedef typename traits::repeat_type repeat_type;
  typedef typename traits::repeat_delay_type repeat_delay_type;
  typedef typename traits::duration_type duration_type;
  typedef typename traits::by_type by_type;
  typedef typename traits::component_type component_type;
  typedef typename traits::interface_type interface_type;
  typedef typename traits::descriptor_type descriptor_type;

  BOOST_CONCEPT_USAGE(ActionBoundComponent)
  {
    convertible_to<bool>(traits::has_delay(i));
    convertible_to<delay_type>(traits::delay(i));
    convertible_to<bool>(traits::has_value(i));
    convertible_to<string_type>(traits::value(i));
    convertible_to<bool>(traits::has_qualifier(i));
    convertible_to<qualifier_type>(traits::qualifier(i));
    convertible_to<bool>(traits::has_repeat(i));
    convertible_to<repeat_type>(traits::repeat(i));
    convertible_to<bool>(traits::has_repeat_delay(i));
    convertible_to<repeat_delay_type>(traits::repeat_delay(i));
    convertible_to<bool>(traits::has_duration(i));
    convertible_to<duration_type>(traits::duration(i));
    convertible_to<bool>(traits::has_by(i));
    convertible_to<by_type>(traits::by(i));
    convertible_to<component_type>(traits::component (i));
    convertible_to<interface_type>(traits::interface_ (i));
    convertible_to<descriptor_type>(traits::descriptor (i));
    convertible_to<bool>(traits::has_descriptor (i));
    convertible_to<bool>(traits::has_interface (i));
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
