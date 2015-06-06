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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_COMPOUND_ACTION_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_COMPOUND_ACTION_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_compound_action_traits
{
  typedef boost::mpl::false_ is_connector_compound_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorCompoundAction
{
  typedef connector_compound_action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_connector_compound_action::value, ==, true);
  typedef typename traits::connector_action_range
    connector_action_range;

  BOOST_CONCEPT_ASSERT ((boost::SinglePassRangeConcept<connector_action_range>));
  typedef typename boost::range_value<connector_action_range>::type
    connector_action_type;

  BOOST_CONCEPT_USAGE (ConnectorCompoundAction)
  {
    convertible_to<connector_action_range>(traits::connector_action_all(i));
  }

  template <typename T0, typename T1>
  void convertible_to (T1 const&)
  {
    BOOST_MPL_ASSERT ((boost::is_convertible<T1, T0>));
  }

  X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
