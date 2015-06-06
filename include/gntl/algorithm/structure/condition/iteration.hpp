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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_ITERATION_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_ITERATION_HPP

#include <gntl/concept/structure/condition/condition_expression.hpp>
#include <gntl/concept/structure/condition/condition.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

template <typename Predicate>
struct matches_leaf_condition_predicate;

template <typename CompoundCondition
          , typename Predicate>
bool matches_leaf_condition_tag(CompoundCondition condition
                                , Predicate p
                                , concept::structure::compound_condition_tag)
{
  typedef concept::structure::compound_condition_traits
    <CompoundCondition> compound_traits;
  typename compound_traits::condition_range
    condition_range = compound_traits::condition_all(condition);
  return gntl::range::find_if(condition_range
                              , matches_leaf_condition_predicate<Predicate>(p))
    != boost::end(condition_range);
}

template <typename SimpleCondition
          , typename Predicate>
bool matches_leaf_condition_tag(SimpleCondition condition
                                , Predicate p
                                , concept::structure::simple_condition_tag)
{
  return p(condition);
}

template <typename Condition
          , typename Predicate>
bool matches_leaf_condition(Condition condition
                            , Predicate p
                            , typename boost::enable_if
                              <
                                typename concept::structure::condition_traits
                                <typename boost::unwrap_reference<Condition>::type>::is_condition
                              , void
                              >::type* = 0
                            )
{
  typedef typename boost::unwrap_reference<Condition>::type condition_type;
  typedef concept::structure::condition_traits<condition_type> traits;
  return condition::matches_leaf_condition_tag(condition, p, typename traits::category_tag());
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Predicate>
inline
bool matches_leaf_condition_iterate_expression(ConditionExpression
                                               , Predicate
                                               , typename boost::enable_if<boost::is_same<Iter, EndIter>
                                                                          , void>::type* = 0)
{
  return false;
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Predicate>
bool matches_leaf_condition_iterate_expression(ConditionExpression condition
                                               , Predicate p
                                               , typename boost::disable_if<boost::is_same<Iter, EndIter>
                                                                            , void>::type* = 0)
{
  typedef typename boost::mpl::deref<Iter>::type condition_type;
  typedef concept::structure::condition_expression_traits
    <ConditionExpression> condition_expression_traits;
  if(condition_expression_traits
     ::template is_type<condition_type>(condition))
  {
    condition_type cond = condition_expression_traits
      ::template get<condition_type>(condition);
    if(condition::matches_leaf_condition(cond, p))
      return true;
  }
  return condition::matches_leaf_condition_iterate_expression
    <typename boost::mpl::next<Iter>::type, EndIter>(condition, p);
}

template <typename Condition, typename Predicate>
bool matches_leaf_condition(Condition c, Predicate p
                            , typename boost::enable_if
                              <typename concept::structure::condition_expression_traits
                              <Condition>::is_condition_expression, void>::type* = 0)
{
  typedef concept::structure::condition_expression_traits
    <Condition> traits;
  typedef typename traits::condition_list_type condition_list_type;
  return condition::matches_leaf_condition_iterate_expression
    <typename boost::mpl::begin<condition_list_type>::type
     , typename boost::mpl::end<condition_list_type>::type>
    (c, p);
}

template <typename Predicate>
struct matches_leaf_condition_predicate
{
  matches_leaf_condition_predicate(Predicate p)
    : p(p)
  {}

  typedef bool result_type;
  template <typename Condition>
  result_type operator()(Condition c) const
  {
    return condition::matches_leaf_condition(c, p);
  }

  Predicate p;
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
