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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_COMPOUND_STATEMENT_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_COMPOUND_STATEMENT_HPP

#include <gntl/concept/parser/connector/connector_condition.hpp>
#include <gntl/concept/parser/connector/connector_compound_statement.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_compound_statement_traits
{
  typedef boost::mpl::false_ is_connector_compound_statement;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorCompoundStatement
{
    typedef connector_compound_statement_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_connector_compound_statement::value, ==, true);
    typedef typename traits::operator_type operator_type;
    typedef typename traits::is_negated_type is_negated_type;
    typedef typename traits::condition_expression_range
      condition_expression_range;

    BOOST_CONCEPT_ASSERT ((boost::SinglePassRangeConcept<condition_expression_range>));
    typedef typename boost::range_value<condition_expression_range>::type
      condition_expression_type;

    BOOST_CONCEPT_USAGE (ConnectorCompoundStatement)
    {
        convertible_to<operator_type>(traits::operator_ (i));
        convertible_to<bool>(traits::has_is_negated (i));
        convertible_to<is_negated_type>(traits::is_negated (i));
        convertible_to<condition_expression_range>(traits::condition_expression_all(i));
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
