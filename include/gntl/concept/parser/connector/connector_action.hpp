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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_ACTION_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_CONNECTOR_ACTION_HPP

#include <boost/mpl/bool.hpp>
#include <gntl/concept/parser/connector/connector_simple_action.hpp>
#include <gntl/concept/parser/connector/connector_compound_action.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_action_traits
{
  typedef boost::mpl::false_ is_connector_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorAction
{
  typedef connector_action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_connector_action::value, ==, true);
  typedef typename traits::simple_action_type simple_action_type;
  typedef typename traits::compound_action_type compound_action_type;

  BOOST_CONCEPT_ASSERT ((ConnectorSimpleAction<simple_action_type>));
  BOOST_CONCEPT_ASSERT ((ConnectorCompoundAction<compound_action_type>));

  BOOST_CONCEPT_USAGE(ConnectorAction)
  {
    convertible_to<bool>(traits::is_compound(i));
    convertible_to<simple_action_type>(traits::simple_action(i));
    convertible_to<compound_action_type>(traits::compound_action(i));
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
