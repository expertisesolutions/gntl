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

#ifndef GNTL_CONCEPT_STRUCTURE_SWITCH_HPP
#define GNTL_CONCEPT_STRUCTURE_SWITCH_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context_fwd.hpp>
#include <gntl/concept/structure/bind_rule.hpp>
#include <gntl/concept/lookupable.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/parameter.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct switch_traits
{
  typedef boost::mpl::false_ is_switch;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X, typename TestContext = boost::mpl::true_>
struct Switch
{
  typedef switch_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_switch::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::refer_type refer_type;
  typedef typename traits::switch_port_range switch_port_range;
  typedef typename traits::bind_rule_range bind_rule_range;
  typedef typename traits::media_range media_range;
  typedef typename traits::context_range context_range;
  typedef typename traits::switch_range switch_range;
  typedef typename traits::media_lookupable media_lookupable;
  typedef typename traits::context_lookupable context_lookupable;
  typedef typename traits::switch_lookupable switch_lookupable;

  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<media_range>));
  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<context_range>));
  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<switch_range>));
  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<switch_port_range>));
  BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<bind_rule_range>));

  BOOST_CONCEPT_ASSERT((Lookupable<context_lookupable>));
  BOOST_CONCEPT_ASSERT((Lookupable<media_lookupable>));

  typedef typename boost::range_value<typename unwrap_parameter<switch_range>::type>::type switch_value_type;
  typedef typename boost::range_value<typename unwrap_parameter<media_range>::type>::type media_value_type;
  typedef typename boost::range_value<typename unwrap_parameter<context_range>::type>::type context_value_type;
  typedef typename boost::range_value<typename unwrap_parameter<switch_port_range>::type>::type 
    switch_port_value_type;
  typedef typename boost::range_value<typename unwrap_parameter<bind_rule_range>::type>::type
    bind_rule_value_type;

  BOOST_MPL_ASSERT((boost::is_same<X, typename unwrap_parameter<switch_value_type>::type>));
  BOOST_CONCEPT_ASSERT((Media<typename unwrap_parameter<media_value_type>::type>));
  BOOST_CONCEPT_ASSERT((BindRule<typename unwrap_parameter<bind_rule_value_type>::type>));

  template <typename T = int> 
  struct TestContext_meta
  {
    BOOST_CONCEPT_ASSERT((Context<typename unwrap_parameter<context_value_type>::type>));
  };

  typename boost::mpl::eval_if<TestContext, boost::mpl::identity<TestContext_meta<> >
                               , boost::mpl::identity<int> >::type test_context;

  BOOST_CONCEPT_USAGE(Switch)
  {
    convertible_to<identifier_type>(traits::identifier(const_i));
    convertible_to<bool>(traits::has_refer(const_i));
    convertible_to<refer_type>(traits::refer(const_i));
    convertible_to<bool>(traits::has_default_component(const_i));
    convertible_to<identifier_type>(traits::default_component(const_i));
    convertible_to<switch_port_range>(traits::switch_port_all(i));
    convertible_to<switch_range>(traits::switch_all(i));
    convertible_to<media_range>(traits::media_all(i));
    convertible_to<context_range>(traits::context_all(i));
    convertible_to<bind_rule_range>(traits::bind_rule_all(i));
    convertible_to<media_lookupable>(traits::media_lookup(i));
    convertible_to<context_lookupable>(traits::context_lookup(i));
    convertible_to<switch_lookupable>(traits::switch_lookup(i));
    convertible_to<bool>(traits::is_presentation_occurring(i));
    convertible_to<bool>(traits::is_presentation_paused(i));
    convertible_to<bool>(traits::is_presentation_sleeping(i));
    convertible_to<identifier_type>(traits::active_component(const_i));
    traits::activate_component(i, identifier);
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
  X const_i;
  identifier_type identifier;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
