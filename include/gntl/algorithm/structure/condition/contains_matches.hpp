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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_CONTAINS_CONDITION_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_CONTAINS_CONDITION_HPP

#include <gntl/concept/structure/condition/condition_expression.hpp>
#include <gntl/concept/structure/condition/condition.hpp>
#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/condition/compound_condition.hpp>
#include <gntl/algorithm/structure/condition/defaults.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Predicate>
bool contains_matching_condition_expression(ConditionExpression condition
                                       , Predicate predicate
                                       , typename boost::enable_if<boost::is_same<Iter, EndIter>
                                                                   , void>::type* = 0)
{
  return false;
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Predicate>
bool contains_matching_condition_expression(ConditionExpression condition
                                       , Predicate predicate
                                       , typename boost::disable_if<boost::is_same<Iter, EndIter>
                                                                    , void>::type* = 0);

template <typename Condition, typename Predicate>
bool contains_matching_condition(Condition c
                            , Predicate predicate
                            , typename boost::enable_if
                            <typename concept::structure::condition_expression_traits
                             <Condition>::is_condition_expression, void>::type* = 0)
{
  typedef concept::structure::condition_expression_traits
    <Condition> traits;
  typedef typename traits::condition_list_type condition_list_type;
  return contains_matching_condition_expression
    <typename boost::mpl::begin<condition_list_type>::type
     , typename boost::mpl::end<condition_list_type>::type>
    (c, predicate);
}

template <typename SimpleCondition, typename Predicate>
bool contains_matching_condition_aux(SimpleCondition c
                                , Predicate predicate
                                , concept::structure::simple_condition_tag)
{
  return predicate(c);
}

template <typename Predicate>
struct contains_matching_condition_predicate
{
  contains_matching_condition_predicate(Predicate predicate)
    : predicate(predicate)
  {}

  typedef bool result_type;
  template <typename Condition>
  result_type operator()(Condition c) const
  {
    return contains_matching_condition(c, predicate);
  }

  Predicate predicate;
};


template <typename CompoundCondition, typename Predicate>
bool contains_matching_condition_aux(CompoundCondition c
                                , Predicate predicate
                                , concept::structure::compound_condition_tag)
{
  typedef concept::structure::compound_condition_traits
    <CompoundCondition> compound_traits;
  typename compound_traits::condition_range
    condition_range = compound_traits::condition_all(c);
  typedef typename boost::range_iterator<typename compound_traits::condition_range>
    ::type iterator_type;
  contains_matching_condition_predicate<Predicate> p(predicate);
  iterator_type iterator = gntl::range::find_if(condition_range, p);
  if(iterator != boost::end(condition_range))
  {
    gntl::range::for_each(boost::iterator_range<iterator_type>
                          (boost::next(iterator), boost::end(condition_range))
                          , p);
    return true;
  }
  else
    return false;
}

template <typename AssessmentStatement, typename Predicate>
bool contains_matching_condition_aux(AssessmentStatement s
                                     , Predicate predicate
                                     , concept::structure::assessment_statement_tag)
{
  return false;
}

template <typename CompoundStatement, typename Predicate>
bool contains_matching_condition_aux(CompoundStatement s
                                     , Predicate predicate
                                     , concept::structure::compound_statement_tag)
{
  return false;
}

template <typename Condition, typename Predicate>
bool contains_matching_condition(Condition c
                            , Predicate predicate
                            , typename boost::enable_if
                            <typename concept::structure::condition_traits
                            <Condition>::is_condition, void>::type* = 0)
{
  GNTL_CONCEPT_ASSERT((concept::structure::Condition<Condition>));
  return contains_matching_condition_aux(c, predicate
                                         , typename concept::structure::condition_traits
                                         <Condition>::category_tag());
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Predicate>
bool contains_matching_condition_expression(ConditionExpression condition
                                            , Predicate predicate
                                            , typename boost::disable_if<boost::is_same<Iter, EndIter>
                                                                         , void>::type*)
{
  typedef typename boost::mpl::deref<Iter>::type condition_type;
  typedef concept::structure::condition_expression_traits
    <ConditionExpression> condition_expression_traits;
  if(condition_expression_traits
     ::template is_type<condition_type>(condition))
  {
    condition_type cond = condition_expression_traits
      ::template get<condition_type>(condition);
    if(contains_matching_condition(cond, predicate))
      return true;
  }
  return contains_matching_condition_expression<typename boost::mpl::next<Iter>::type
                                           , EndIter>(condition
                                                      , predicate);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
