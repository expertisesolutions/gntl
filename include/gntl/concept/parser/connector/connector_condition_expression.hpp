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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_CONDITION_EXPRESSION_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_CONDITION_EXPRESSION_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/parser/connector/connector_condition.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_condition_expression_traits
{
    typedef boost::mpl::false_ is_connector_condition_expression;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorConditionExpression
{
    typedef connector_condition_expression_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_connector_condition_expression::value, ==, true);
    typedef typename traits::condition_list_type condition_list_type;

    BOOST_CONCEPT_USAGE (ConnectorConditionExpression)
    {
        check_get(boost::mpl::identity
                  <typename boost::mpl::begin<condition_list_type>::type>()
                  , boost::mpl::identity
                  <typename boost::mpl::end<condition_list_type>::type>());
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1, T0>));
    }

    template <typename Iter, typename End>
    void check_get(Iter iter, End end
                   , typename boost::disable_if
                   <boost::is_same<typename Iter::type
                                   , typename End::type>, void>::type* = 0
                   )
    {
      typedef typename boost::mpl::deref<typename Iter::type>::type
        value_type;
      convertible_to<bool>(traits::template is_type<value_type>(i));
      convertible_to<value_type>(traits::template get<value_type>(i));
      check_get(boost::mpl::identity
                <typename boost::mpl::next<typename Iter::type>::type>()
                , end);
      BOOST_CONCEPT_ASSERT((ConnectorCondition<value_type>));
    }

    template <typename Iter, typename End>
    void check_get(Iter iter, End end
                   , typename boost::enable_if
                   <boost::is_same<typename Iter::type
                                   , typename End::type>, void>::type* = 0
                   )
    {
    }

    X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
