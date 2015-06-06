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

#ifndef GNTL_CONCEPT_PARSER_CAUSALCONNECTOR_HPP
#define GNTL_CONCEPT_PARSER_CAUSALCONNECTOR_HPP

#include <gntl/concept/parser/connector/connector_condition_expression.hpp>
#include <gntl/concept/parser/connector/connector_action.hpp>
#include <gntl/concept/parser/connector/connector_parameter.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct causal_connector_traits
{
  typedef boost::mpl::false_ is_causal_connector;
};
/*
template <typename T>
struct causal_connector_traits
{
    typedef typename T::identifier_type identifier_type;
    typedef typename T::condition_type condition_type;
    typedef typename T::action_type action_type;
    typedef typename T::connector_parameter_type connector_parameter_type;
    typedef typename T::connector_parameter_iterator connector_parameter_iterator;
};
*/
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct CausalConnector
{
    typedef causal_connector_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_causal_connector::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::condition_type condition_type;
    typedef typename traits::action_type action_type;
    typedef typename traits::connector_parameter_type connector_parameter_type;
    typedef typename traits::connector_parameter_iterator connector_parameter_iterator;

  //BOOST_CONCEPT_ASSERT ((ConnectorCondition<condition_type>));
    BOOST_CONCEPT_ASSERT ((ConnectorAction<action_type>));
    BOOST_CONCEPT_ASSERT ((ConnectorParameter<connector_parameter_type>));

    BOOST_MPL_ASSERT ((boost::is_convertible<typename std::iterator_traits<connector_parameter_iterator>::value_type \
                          , connector_parameter_type>));

    BOOST_CONCEPT_USAGE (CausalConnector)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<condition_type>(traits::condition (i));
        convertible_to<action_type>(traits::action (i));
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
