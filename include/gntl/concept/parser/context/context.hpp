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

#ifndef GNTL_CONCEPT_PARSER_CONTEXT_HPP
#define GNTL_CONCEPT_PARSER_CONTEXT_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/parser/switch/switch.hpp>
#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept/parser/port/port.hpp>
#include <gntl/parameter.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct context_traits
{
  typedef boost::mpl::false_ is_context;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Context : boost::CopyConstructible<X>
{
    typedef context_traits<X> traits;
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::context_range context_range;
    typedef typename traits::media_range media_range;
    typedef typename traits::port_range port_range;
    typedef typename traits::link_range link_range;
    typedef typename traits::switch_range switch_range;

    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<switch_range>));
    typedef typename boost::range_value<switch_range>::type switch_value_type;
    typedef typename boost::range_value<port_range>::type port_value_type;
    typedef typename boost::range_value<media_range>::type media_value_type;
    typedef typename boost::range_value<context_range>::type context_value_type;
    typedef typename unwrap_parameter<switch_value_type>::type switch_type;
    BOOST_CONCEPT_ASSERT((Switch<switch_type, boost::mpl::false_>));
    BOOST_CONCEPT_ASSERT((Media<typename unwrap_parameter<media_value_type>::type>));
    BOOST_CONCEPT_ASSERT((Port<typename unwrap_parameter<port_value_type>::type>));

    BOOST_CONCEPT_USAGE (Context)
    {
      convertible_to<identifier_type>(traits::identifier (i));
      convertible_to<bool>(traits::has_refer (i));
      convertible_to<identifier_type>(traits::refer (i));
      convertible_to<context_range>(traits::context_all(i));
      convertible_to<media_range>(traits::media_all(i));
      convertible_to<port_range>(traits::port_all(i));
      convertible_to<link_range>(traits::link_all(i));
      convertible_to<switch_range>(traits::switch_all(i));
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
