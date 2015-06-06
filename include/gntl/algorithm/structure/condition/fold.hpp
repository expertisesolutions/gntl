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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_FOLD_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_FOLD_HPP

#include <gntl/concept/structure/condition/condition_expression.hpp>
#include <gntl/concept/structure/condition/condition.hpp>
#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/condition/bound_assessment_statement.hpp>
#include <gntl/concept/structure/condition/compound_condition.hpp>
#include <gntl/concept/structure/condition/compound_statement.hpp>
#include <gntl/concept/parser/connector/connector_assessment_statement.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/size.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

template <typename ConditionExpression, typename Value, typename BinaryOperation>
Value fold(ConditionExpression c
           , Value v
           , BinaryOperation o
           , typename boost::enable_if
           <typename concept::structure::condition_expression_traits
            <ConditionExpression>::is_condition_expression, void>::type* = 0);

template <typename CompoundCondition, typename Value, typename BinaryOperation>
Value fold(CompoundCondition c
           , Value v
           , BinaryOperation o
           , typename boost::enable_if
           <typename concept::structure::compound_condition_traits
            <CompoundCondition>::is_compound_condition, void>::type* = 0)
{
  typedef typename concept::structure::compound_condition_traits
    <CompoundCondition> compound_condition_traits;
  typedef typename compound_condition_traits::condition_range condition_range;
  condition_range conditions = compound_condition_traits::condition_all(c);
  for(typename boost::range_iterator<condition_range>::type
        Iter = boost::begin(conditions)
        , EndIter = boost::end(conditions)
        ;Iter != EndIter
        ;++Iter)
  {
    v = condition::fold(*Iter, v, o);
  }
  GNTL_DEBUG_LOG("compound condition evaluation result " << v << std::endl)
  return v;
}

template <typename SimpleCondition, typename Value, typename BinaryOperation>
Value fold(SimpleCondition c
           , Value v
           , BinaryOperation o
           , typename boost::enable_if
           <typename concept::structure::bounded_simple_condition_traits
            <SimpleCondition>::is_bounded_simple_condition, void>::type* = 0)
{
  typedef typename concept::structure::bounded_simple_condition_traits
    <SimpleCondition> traits;
  return o(v, c);
}

template <typename AssessmentStatement, typename Value, typename BinaryOperation>
Value fold(AssessmentStatement c
           , Value v
           , BinaryOperation o
           , typename boost::enable_if
           <typename concept::structure::bound_assessment_statement_traits
            <AssessmentStatement>::is_bound_assessment_statement, void>::type* = 0)
{
  return o(v, c);
}

template <typename CompoundStatement, typename Value, typename BinaryOperation>
Value fold(CompoundStatement c
           , Value v
           , BinaryOperation p
           , typename boost::enable_if
           <typename concept::structure::compound_statement_traits
            <CompoundStatement>::is_compound_statement, void>::type* = 0)
{
  return v;
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Value
          , typename BinaryOperation>
Value fold_condition_expression (ConditionExpression
                                 , Value v
                                 , BinaryOperation
                                 , typename boost::enable_if
                                 <boost::is_same<Iter, EndIter>
                                  , void>::type* = 0)
{
  return v;
}

template <typename Iter, typename EndIter
          , typename ConditionExpression
          , typename Value
          , typename BinaryOperation>
Value fold_condition_expression (ConditionExpression c
                                 , Value v
                                 , BinaryOperation o
                                 , typename boost::disable_if
                                 <boost::is_same<Iter, EndIter>
                                  , void>::type* = 0)
{
  typedef concept::structure::condition_expression_traits
    <ConditionExpression> condition_expression_traits;
  typedef typename boost::mpl::deref<Iter>::type condition_type;
  if(condition_expression_traits::template is_type
     <condition_type>(c))
    return condition::fold(condition_expression_traits
                           ::template get<condition_type>(c), v, o);

  return condition::fold_condition_expression
    <typename boost::mpl::next<Iter>::type
     , EndIter>
    (c, v, o);
}

template <typename ConditionExpression, typename Value, typename BinaryOperation>
Value fold(ConditionExpression c
           , Value v
           , BinaryOperation f
           , typename boost::enable_if
           <typename concept::structure::condition_expression_traits
            <ConditionExpression>::is_condition_expression, void>::type*)
{
  typedef typename concept::structure::condition_expression_traits
    <ConditionExpression> condition_expression_traits;
  typedef typename condition_expression_traits::condition_list_type
    condition_list_type;
  return condition::fold_condition_expression
    <typename boost::mpl::begin<condition_list_type>::type
     , typename boost::mpl::end<condition_list_type>::type>
    (c, v, f);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
