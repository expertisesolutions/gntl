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

#ifndef GNTL_STRUCTURE_COMPOSED_ACTION_ACTION_EXPRESSION_HPP
#define GNTL_STRUCTURE_COMPOSED_ACTION_ACTION_EXPRESSION_HPP

#include <gntl/concept/structure/action/action_expression.hpp>
#include <gntl/structure/composed/action/bound_simple_action.hpp>
#include <gntl/structure/composed/action/compound_action.hpp>
#include <gntl/structure/composed/detail/role_predicate.hpp>
#include <gntl/concept/parser/link/link.hpp>
#include <gntl/range.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/iterator/filter_iterator.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Link, typename CausalConnector>
struct action_expression
{
  action_expression(Link link, CausalConnector causal_connector)
    : link(link), causal_connector(causal_connector)
  {}

  Link link;
  CausalConnector causal_connector;
};

} }

namespace concept { namespace structure {

template <typename Link, typename CausalConnector>
struct action_expression_traits<gntl::structure::composed
                                ::action_expression<Link, CausalConnector> >
{
  typedef boost::mpl::true_ is_action_expression;
  typedef gntl::structure::composed::action_expression<Link, CausalConnector>
    action_expression;

  typedef concept::parser::link_traits
    <Link> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_iterator<bind_range>::type
    bind_iterator;
  typedef typename boost::range_value<bind_range>::type
    bind_type;
  typedef concept::parser::bind_traits
    <bind_type> bind_traits;

  typedef concept::parser::causal_connector_traits
    <CausalConnector> causal_connector_traits;
  typedef typename causal_connector_traits::action_type action_type;

  typedef concept::parser::connector_action_traits
    <action_type> action_traits;
  typedef typename action_traits::simple_action_type
    simple_action_type;
  typedef concept::parser::connector_simple_action_traits
    <simple_action_type> simple_action_traits;
  
  typedef typename simple_action_traits
    ::role_type role_type;
  typedef gntl::structure::composed::composed_detail::role_predicate
    <role_type> role_predicate;

  typedef boost::filter_iterator<role_predicate
                                 , bind_iterator>
    role_filtered_iterator;
  typedef boost::iterator_range<role_filtered_iterator>
    role_filtered_range;

  typedef gntl::structure::composed
  ::bound_simple_action<role_filtered_range
                        , simple_action_type>
    bound_simple_action;
  GNTL_CONCEPT_ASSERT((concept::structure::BoundSimpleAction<bound_simple_action>));

  typedef typename action_traits
    ::compound_action_type compound_action_parser;

  typedef gntl::structure::composed
    ::compound_action<Link, compound_action_parser>
    compound_action;
  GNTL_CONCEPT_ASSERT((concept::structure::CompoundAction<compound_action>));
  typedef boost::mpl::vector<bound_simple_action
                             , compound_action> action_list_type;

  template <typename T>
  static bool is_type (action_expression expr)
  {
    BOOST_MPL_ASSERT((boost::mpl::not_<boost::mpl::or_
                      <boost::is_const<T>, boost::is_volatile<T> > >));

    typedef typename boost::is_same
      <T, compound_action>::type is_compound;

    return action_traits::is_compound
      (causal_connector_traits::action
       (expr.causal_connector))
      == is_compound::value;
  }

  template <typename T>
  struct tag {};

  static bound_simple_action get_aux(action_expression c
                                     , tag<bound_simple_action>)
  {
    typename link_traits::bind_range
      bind_range = link_traits::bind(c.link);
    action_type action = causal_connector_traits::action(c.causal_connector);
    simple_action_type simple_action = action_traits::simple_action(action);
    role_predicate predicate(simple_action_traits::role(simple_action));
    role_filtered_iterator
      first (predicate
             , boost::begin(bind_range), boost::end(bind_range))
      , last (predicate
              , boost::end(bind_range), boost::end(bind_range))
      ;
    if(first == last)
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Can't find the respective role in the bound link for this simple action"))
                               (typename error::role<typename simple_action_traits::role_type>::type
                                (simple_action_traits::role(simple_action))));
    return bound_simple_action
      (role_filtered_range(first, last), simple_action);
  }

  static compound_action get_aux(action_expression c
                                 , tag<compound_action>)
  {
    action_type action = causal_connector_traits::action(c.causal_connector);
    compound_action_parser action_ = action_traits::compound_action(action);
    return compound_action(c.link, action_);
  }

  template <typename T>
  static T get(action_expression a)
  {
    return get_aux(a, tag<T>());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
