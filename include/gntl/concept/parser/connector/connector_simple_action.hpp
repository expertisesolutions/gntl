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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_SIMPLE_ACTION_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_SIMPLE_ACTION_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_simple_action_traits
{
  typedef boost::mpl::false_ is_connector_simple_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorSimpleAction
{
  typedef connector_simple_action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_connector_simple_action::value, ==, true);
  typedef typename traits::role_type role_type;
  typedef typename traits::delay_type delay_type;
  typedef typename traits::event_type_type event_type_type;
  typedef typename traits::action_type_type action_type_type;
  typedef typename traits::string_type string_type;
  typedef typename traits::min_type min_type;
  typedef typename traits::max_type max_type;
  typedef typename traits::qualifier_type qualifier_type;
  typedef typename traits::repeat_type repeat_type;
  typedef typename traits::repeat_delay_type repeat_delay_type;
  typedef typename traits::duration_type duration_type;
  typedef typename traits::by_type by_type;

  BOOST_CONCEPT_USAGE(ConnectorSimpleAction)
  {
    convertible_to<role_type>(traits::role(i));
    convertible_to<bool>(traits::has_delay(i));
    convertible_to<delay_type>(traits::delay(i));
    convertible_to<bool>(traits::has_event_type(i));
    convertible_to<event_type_type>(traits::event_type(i));
    convertible_to<bool>(traits::has_action_type(i));
    convertible_to<action_type_type>(traits::action_type(i));
    convertible_to<bool>(traits::has_value(i));
    convertible_to<string_type>(traits::value(i));
    convertible_to<bool>(traits::has_min(i));
    convertible_to<min_type>((traits::min)(i));
    convertible_to<bool>(traits::has_max(i));
    convertible_to<max_type>((traits::max)(i));
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


#include <gntl/detail/pop_options.hpp>

#endif
