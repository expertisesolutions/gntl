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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_SIMPLE_CONDITION_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_SIMPLE_CONDITION_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_simple_condition_traits
{
  typedef boost::mpl::false_ is_connector_simple_condition;
};
/*
template <typename T>
struct connector_simple_condition_traits
{
    typedef typename T::role_type role_type;
    typedef typename T::delay_type delay_type;
    typedef typename T::event_type_type event_type_type;
    typedef typename T::key_type key_type;
    typedef typename T::transition_type transition_type;
    typedef typename T::min_type min_type;
    typedef typename T::max_type max_type;
    typedef typename T::qualifier_type qualifier_type;
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorSimpleCondition
{
    typedef connector_simple_condition_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_connector_simple_condition::value, ==, true);
    typedef typename traits::role_type role_type;
    typedef typename traits::delay_type delay_type;
    typedef typename traits::event_type_type event_type_type;
    typedef typename traits::key_type key_type;
    typedef typename traits::transition_type transition_type;
    typedef typename traits::min_type min_type;
    typedef typename traits::max_type max_type;
    typedef typename traits::qualifier_type qualifier_type;

    BOOST_CONCEPT_USAGE (ConnectorSimpleCondition)
    {
        convertible_to<role_type>(traits::role (i));
        convertible_to<bool>(traits::has_delay (i));
        convertible_to<delay_type>(traits::delay (i));
        convertible_to<bool>(traits::has_event_type (i));
        convertible_to<event_type_type>(traits::event_type (i));
        convertible_to<bool>(traits::has_key (i));
        convertible_to<key_type>(traits::key (i));
        convertible_to<bool>(traits::has_transition (i));
        convertible_to<transition_type>(traits::transition (i));
        convertible_to<bool>(traits::has_min (i));
        convertible_to<min_type>((traits::min) (i));
        convertible_to<bool>(traits::has_max (i));
        convertible_to<max_type>((traits::max) (i));
        convertible_to<bool>(traits::has_qualifier (i));
        convertible_to<qualifier_type>(traits::qualifier (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
