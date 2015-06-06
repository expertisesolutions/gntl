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

#ifndef GNTL_CONCEPT_PARSER_CONNECTOR_ASSESSMENT_HPP
#define GNTL_CONCEPT_PARSER_CONNECTOR_ASSESSMENT_HPP

#include <gntl/concept/parser/connector/connector_attribute_assessment.hpp>
#include <gntl/concept/parser/connector/connector_value_assessment.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct connector_assessment_traits
{
  typedef boost::mpl::false_ is_connector_assessment;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ConnectorAssessment
{
    typedef connector_assessment_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_connector_assessment::value, ==, true);
    typedef typename traits::attribute_assessment_type attribute_assessment_type;
    typedef typename traits::value_assessment_type value_assessment_type;

    BOOST_CONCEPT_ASSERT ((ConnectorAttributeAssessment<attribute_assessment_type>));
    BOOST_CONCEPT_ASSERT ((ConnectorValueAssessment<value_assessment_type>));

    BOOST_CONCEPT_USAGE (ConnectorAssessment)
    {
        convertible_to<bool>(traits::is_value_assessment (i));
        convertible_to<attribute_assessment_type>(traits::attribute_assessment (i));
        convertible_to<value_assessment_type>(traits::value_assessment (i));
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
