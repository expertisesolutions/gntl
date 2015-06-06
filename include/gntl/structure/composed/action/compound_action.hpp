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

#ifndef GNTL_STRUCTURE_COMPOSED_ACTION_COMPOUND_ACTION_HPP
#define GNTL_STRUCTURE_COMPOSED_ACTION_COMPOUND_ACTION_HPP

#include <gntl/concept/structure/action/compound_action.hpp>
#include <gntl/structure/composed/action/compound_action_expression.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Link, typename CompoundActionParser>
struct compound_action
{
  compound_action(Link link
                  , CompoundActionParser compound_action_parser)
    : link(link), compound_action_parser(compound_action_parser)
  {}

  Link link;
  CompoundActionParser compound_action_parser;
};

namespace compound_detail {

template <typename Link, typename Result>
struct action_transform
{
  action_transform(Link link)
    : link(link) {}

  typedef Result result_type;

  template <typename Action>
  result_type operator()(Action c) const
  {
    return result_type(link, c);
  }

  Link link;
};

}

} }

namespace concept { namespace structure {

template <typename Link, typename CompoundActionParser>
struct action_traits<gntl::structure::composed
                     ::compound_action<Link, CompoundActionParser> >
{
  typedef boost::mpl::true_ is_action;
  typedef compound_action_tag category_tag;
};

template <typename Link, typename CompoundActionParser>
struct compound_action_traits<gntl::structure::composed
                              ::compound_action<Link, CompoundActionParser> >
{
  typedef boost::mpl::true_ is_compound_action;
  typedef gntl::structure::composed
    ::compound_action<Link, CompoundActionParser>
    compound_action;

  typedef concept::parser::connector_compound_action_traits
    <CompoundActionParser> action_traits;

  typedef 
      gntl::structure::composed
     ::compound_detail::action_transform
      <
        Link
        , gntl::structure::composed
          ::compound_action_expression
          <Link
           , typename boost::range_value
           <typename action_traits::connector_action_range>::type
          >
      > transform_function;
  typedef boost::transform_iterator
    <
      transform_function
      , typename boost::range_iterator
      <typename action_traits::connector_action_range>::type
      , typename transform_function::result_type
    >
    action_iterator;

  typedef boost::iterator_range
    <action_iterator>
    action_range;

  static action_range action_all(compound_action a)
  {
    typedef typename action_traits::connector_action_range
      connector_action_range;
    typename boost::range_iterator<connector_action_range>
      ::type
      first = boost::begin
      (action_traits::connector_action_all(a.compound_action_parser))
      , last = boost::end
      (action_traits::connector_action_all(a.compound_action_parser));
    return action_range
      (action_iterator(first, transform_function(a.link))
       , action_iterator(last, transform_function(a.link)));
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
