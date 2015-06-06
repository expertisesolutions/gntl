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

#ifndef GNTL_CONCEPT_PARSER_HAS_DESCRIPTOR_PARAM_HPP
#define GNTL_CONCEPT_PARSER_HAS_DESCRIPTOR_PARAM_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/parser/descriptor/descriptor_param.hpp>
#include <gntl/range.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct has_descriptor_param_traits
{
  typedef boost::mpl::false_ has_descriptor_param;
};

/*
template <>
struct has_descriptor_param_traits<has_descriptor_param_type>
{
  typedef boost::mpl::true_ has_descriptor_param;
  typedef some_range_type descriptor_param_range;
  static descriptor_param_range descriptor_param(has_descriptor_param_type);
};
*/


#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct HasDescriptorParam
{
    typedef has_descriptor_param_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::has_descriptor_param::value, ==, true);
    typedef typename traits::descriptor_param_range descriptor_param_range;

    BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<descriptor_param_range>));
    typedef typename boost::range_value<descriptor_param_range>::type
      descriptor_param_type;
    BOOST_CONCEPT_ASSERT((DescriptorParam<descriptor_param_type>));

    BOOST_CONCEPT_USAGE (HasDescriptorParam)
    {
        convertible_to<descriptor_param_range>(traits::descriptor_param (i));
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
