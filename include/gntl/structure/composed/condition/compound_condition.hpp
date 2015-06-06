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

#ifndef GNTL_STRUCTURE_COMPOSED_CONDITION_COMPOUND_CONDITION_HPP
#define GNTL_STRUCTURE_COMPOSED_CONDITION_COMPOUND_CONDITION_HPP

#include <gntl/concept/parser/link/link.hpp>
#include <gntl/concept/parser/connector/connector_compound_condition.hpp>
#include <gntl/concept/structure/condition/compound_condition.hpp>
#include <gntl/structure/composed/condition/compound_condition_expression.hpp>
#include <gntl/algorithm/parser/link.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/config.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename LinkParser, typename CompoundConditionParser>
struct compound_condition
{
  typedef typename boost::unwrap_reference<LinkParser>::type link_type;
  typedef concept::parser::link_traits<link_type> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_value_type;
  typedef typename boost::unwrap_reference<bind_value_type>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;
  compound_condition(LinkParser link
                     , CompoundConditionParser condition
                     , std::map<role_type, bool>* role_conditions)
    : link(link), condition(condition), role_conditions(role_conditions)
  {}

  LinkParser link;
  CompoundConditionParser condition;
  std::map<role_type, bool>* role_conditions;
};

namespace compound_detail {

template <typename Link>
struct bind_meta
{
  typedef concept::parser::link_traits<Link> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type type;
};

}

template <typename Link, typename NewCondition, typename Map>
struct condition_transform
{
  condition_transform(Link link, Map map)
    : link(link), map(map) {}

  typedef NewCondition result_type;

  template <typename Condition>
  result_type operator()(Condition c) const
  {
    return result_type(link, c, map);
  }

  Link link;
  Map map;
};

} }

namespace concept { namespace structure {

template <typename LinkParser, typename CompoundConditionParser>
struct compound_condition_traits
  <gntl::structure::composed
   ::compound_condition
   <LinkParser, CompoundConditionParser> >
{
  typedef boost::mpl::true_ is_compound_condition;
  typedef gntl::structure::composed
   ::compound_condition
   <LinkParser, CompoundConditionParser>
  compound_condition;
  
  typedef concept::parser::link_traits<LinkParser> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;
  typedef concept::parser::connector_compound_condition_traits
    <CompoundConditionParser> condition_traits;

  typedef typename condition_traits::operator_type operator_type;
  typedef typename condition_traits::delay_type delay_type;
  typedef 
      gntl::structure::composed
      ::condition_transform
      <
        LinkParser
        , gntl::structure::composed
          ::compound_condition_expression
          <LinkParser
           , typename boost::range_value
           <typename condition_traits::condition_expression_range>::type
          >
        , std::map<role_type, bool>*
      > transform_function;
  typedef boost::transform_iterator
    <
      transform_function
      , typename boost::range_iterator
      <typename condition_traits::condition_expression_range>::type
      , typename transform_function::result_type
    >
    condition_iterator;

  typedef boost::iterator_range
    <condition_iterator>
    condition_range;

  static operator_type operator_(compound_condition c)
  { return condition_traits::operator_(c.condition); }
  static delay_type delay(compound_condition c)
  { return condition_traits::delay(c.condition); }
  static bool has_delay(compound_condition c)
  { return condition_traits::has_delay(c.condition); }
  static condition_range condition_all(compound_condition c)
  {
    typedef typename condition_traits::condition_expression_range
      connector_condition_range;
    typename boost::range_iterator<connector_condition_range>
      ::type
      first = boost::begin
      (condition_traits::condition_expression_all(c.condition))
      , last = boost::end
      (condition_traits::condition_expression_all(c.condition));
    return condition_range
      (condition_iterator(first, transform_function(c.link, c.role_conditions))
       , condition_iterator(last, transform_function(c.link, c.role_conditions)));
  }
};

template <typename BindParser, typename CompoundConditionParser>
struct condition_traits
  <gntl::structure::composed
   ::compound_condition
   <BindParser, CompoundConditionParser> >
{
  typedef boost::mpl::true_ is_condition;
  typedef concept::structure::compound_condition_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
