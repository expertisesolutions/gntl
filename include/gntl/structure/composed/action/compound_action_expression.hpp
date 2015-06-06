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

#ifndef GNTL_STRUCTURE_COMPOSED_ACTION_COMPOUND_ACTION_EXPRESSION_HPP
#define GNTL_STRUCTURE_COMPOSED_ACTION_COMPOUND_ACTION_EXPRESSION_HPP

#include <gntl/concept/parser/connector/connector_action.hpp>
#include <gntl/structure/composed/action/compound_action_fwd.hpp>
#include <gntl/structure/composed/detail/role_predicate.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/iterator/filter_iterator.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed { 

template <typename Link, typename ActionParser>
struct compound_action_expression
{
  compound_action_expression(Link link, ActionParser action)
    : link(link), action(action)
  {}

  Link link;
  ActionParser action;
};

} }

namespace concept { namespace structure {

template <typename Link, typename ActionParser>
struct action_expression_traits<gntl::structure::composed
                                ::compound_action_expression<Link, ActionParser> >
{
  typedef boost::mpl::true_ is_action_expression;
  typedef gntl::structure::composed
    ::compound_action_expression<Link, ActionParser>
    compound_action_expression;

  typedef concept::parser::connector_action_traits
    <ActionParser> action_traits;
  typedef typename action_traits::simple_action_type
    simple_action_type;
  typedef typename action_traits::compound_action_type
    compound_action_type;

  typedef concept::parser::link_traits
    <Link> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_iterator<bind_range>::type
    bind_iterator;
  typedef typename boost::range_value<bind_range>::type
    bind_type;
  typedef concept::parser::bind_traits
    <bind_type> bind_traits;

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

  typedef gntl::structure::composed::bound_simple_action
    <role_filtered_range, simple_action_type>
    bound_simple_action;

  typedef gntl::structure::composed::compound_action
    <Link, compound_action_type>
    compound_action;
  typedef boost::mpl::vector<bound_simple_action
                             , compound_action> action_list_type;

  template <typename T>
  static bool is_type (compound_action_expression expr)
  {
    BOOST_MPL_ASSERT((boost::mpl::not_<boost::mpl::or_
                      <boost::is_const<T>, boost::is_volatile<T> > >));

    typedef typename boost::is_same
      <T, compound_action>::type is_compound;

    return action_traits::is_compound(expr.action)
      == is_compound::value;
  }

  template <typename T>
  struct tag {};

  static bound_simple_action get_aux(compound_action_expression a
                                     , tag<bound_simple_action>)
  {
    typename link_traits::bind_range
      bind_range = link_traits::bind(a.link);
    simple_action_type simple_action = action_traits::simple_action(a.action);
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
                                ("Can't find the respective role in the bound link for this simple action"
                                 "(inside a compoundAction)"))
                               (typename error::role<typename simple_action_traits::role_type>::type
                                (simple_action_traits::role(simple_action))));
    return bound_simple_action
      (role_filtered_range(first, last), simple_action);
  }

  static compound_action get_aux(compound_action_expression a
                                 , tag<compound_action>)
  {
    return compound_action(a.link, action_traits::compound_action(a.action));
  }

  template <typename T>
  static T get(compound_action_expression a)
  {
    return get_aux(a, tag<T>());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
