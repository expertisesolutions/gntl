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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_BASE_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_BASE_HPP

#include <gntl/concept/parser/connector/causal_connector.hpp>
#include <gntl/concept/parser/import/import_base.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_base_traits
{
  typedef boost::mpl::false_ is_connector_base;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorBase
{
    typedef connector_base_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_connector_base::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::causal_connector_range causal_connector_range;
    typedef typename traits::import_base_range import_base_range;

    BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<causal_connector_range>));

    typedef typename boost::range_value<causal_connector_range>::type causal_connector_type;

    BOOST_CONCEPT_ASSERT((CausalConnector<causal_connector_type>));

    BOOST_CONCEPT_USAGE (ConnectorBase)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<bool>(traits::has_identifier (i));
        convertible_to<causal_connector_range>(traits::causal_connector_all(i));
        convertible_to<import_base_range>(traits::import_base_all(i));
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
