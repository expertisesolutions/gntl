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

#ifndef GNTL_CONCEPT_STRUCTURE_CONTEXT_HPP
#define GNTL_CONCEPT_STRUCTURE_CONTEXT_HPP

#include <gntl/concept/parser/port/port.hpp>
#include <gntl/concept/parser/context/context.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/link.hpp>
#include <gntl/concept/structure/switch.hpp>
#include <gntl/concept/lookupable.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct context_traits
{
  typedef boost::mpl::false_ is_context;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Context
{
    typedef context_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_context::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::port_range port_range;
    typedef typename traits::media_const_range media_const_range;
    typedef typename traits::media_range media_range;
    typedef typename traits::context_range context_range;
    typedef typename traits::link_range link_range;
    typedef typename traits::switch_range switch_range;
    typedef typename traits::media_lookupable media_lookupable;
    typedef typename traits::context_lookupable context_lookupable;
    typedef typename traits::switch_lookupable switch_lookupable;
    typedef typename traits::port_lookupable port_lookupable;
    typedef typename traits::refer_type refer_type;

    BOOST_CONCEPT_ASSERT((Lookupable<media_lookupable>));
    BOOST_CONCEPT_ASSERT((Lookupable<context_lookupable>));
    BOOST_CONCEPT_ASSERT((Lookupable<switch_lookupable>));
    BOOST_CONCEPT_ASSERT((Lookupable<port_lookupable>));

    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<port_range>::type>));
    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<media_const_range>::type>));
    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<media_range>::type>));
    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<context_range>::type>));
    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<link_range>::type>));
    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<typename unwrap_parameter<switch_range>::type>));

    typedef typename boost::range_value<typename unwrap_parameter<port_range>::type>::type port_value_type;
    typedef typename boost::range_value<typename unwrap_parameter<media_const_range>::type>::type 
      media_const_value_type;
    typedef typename boost::range_value<typename unwrap_parameter<media_range>::type>::type media_value_type;
    typedef typename boost::range_value<typename unwrap_parameter<context_range>::type>::type context_value_type;
    typedef typename boost::range_value<typename unwrap_parameter<link_range>::type>::type link_value_type;
    typedef typename boost::range_value<typename unwrap_parameter<switch_range>::type>::type switch_value_type;

    BOOST_CONCEPT_ASSERT((parser::Port<typename unwrap_parameter<port_value_type>::type>));
    BOOST_CONCEPT_ASSERT((Media<typename unwrap_parameter<media_value_type>::type>));
    BOOST_CONCEPT_ASSERT((Link<typename unwrap_parameter<link_value_type>::type>));
    BOOST_CONCEPT_ASSERT((Switch<typename unwrap_parameter<switch_value_type>::type, boost::mpl::false_>));

    BOOST_CONCEPT_USAGE (Context)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<port_range>(traits::port_all (i));
        convertible_to<port_lookupable>(traits::port_lookup (i));
        convertible_to<media_lookupable>(traits::media_lookup (i));
        convertible_to<context_lookupable>(traits::context_lookup (i));
        convertible_to<switch_lookupable>(traits::switch_lookup (i));
        convertible_to<media_range>(traits::media_all (i));
        convertible_to<media_const_range>(traits::media_all (const_i));
        convertible_to<context_range>(traits::context_all (i));
        convertible_to<switch_range>(traits::switch_all (i));
        convertible_to<link_range>(traits::link_all (i));
        convertible_to<bool>(traits::is_presentation_occurring (const_i));
        convertible_to<bool>(traits::is_presentation_paused (const_i));
        convertible_to<bool>(traits::is_presentation_sleeping (const_i));
        convertible_to<bool>(traits::has_refer (const_i));
        convertible_to<refer_type>(traits::refer (const_i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }

    X i;
    X const_i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
