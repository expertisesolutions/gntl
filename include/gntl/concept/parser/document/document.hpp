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

#ifndef GNTL_CONCEPTS_DOCUMENTNODE_HPP
#define GNTL_CONCEPTS_DOCUMENTNODE_HPP

#include <gntl/concept/parser/head/head.hpp>
#include <gntl/concept/parser/body/body.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct document_traits
{
  typedef boost::mpl::false_ is_document;
};

/*
template <typename T>
struct document_traits
{
    typedef typename T::head_type head_type;
    typedef typename T::body_type body_type;
    typedef typename T::identifier_type identifier_type;
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Document : boost::CopyConstructible<X>
{
    typedef document_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_document::value, ==, true);
    typedef typename traits::head_type head_type;
    typedef typename traits::body_type body_type;
    typedef typename traits::identifier_type identifier_type;

    BOOST_CONCEPT_ASSERT ((Head<head_type>));
    BOOST_CONCEPT_ASSERT ((Body<body_type>));
    
    BOOST_CONCEPT_USAGE (Document)
    {
        convertible_to<head_type> (traits::head (i));
        convertible_to<body_type> (traits::body (i));
        convertible_to<identifier_type> (traits::identifier (i));
    }

    X i;

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
