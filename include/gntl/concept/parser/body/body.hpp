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

#ifndef GNTL_CONCEPT_PARSER_BODY_HPP
#define GNTL_CONCEPT_PARSER_BODY_HPP

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct body_traits
{
  typedef boost::mpl::false_ is_body;
};

/*
template <>
struct body_traits<body>
{
  typedef body body_type;
  typedef context context_type;
  static context_type context(body_type);
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Body
{
    typedef body_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_body::value, ==, true);
    typedef typename traits::context_type context_type;

    BOOST_CONCEPT_ASSERT ((Context<context_type>));

    BOOST_CONCEPT_USAGE (Body)
    {
        convertible_to<context_type>(traits::context (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_STATIC_ASSERT ((boost::is_convertible<T1,T0>::type::value));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
