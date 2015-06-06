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

#ifndef GNTL_ALGORITHM_STRUCTURE_ACTION_FOLD_HPP
#define GNTL_ALGORITHM_STRUCTURE_ACTION_FOLD_HPP

#include <gntl/concept/structure/action/action_expression.hpp>
#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace action {

template <typename ActionExpression, typename Value, typename BinaryOperation>
Value fold (ActionExpression action_expression, Value v, BinaryOperation operation
            , typename boost::enable_if
            <typename concept::structure::action_expression_traits
             <ActionExpression>::is_action_expression, void>::type* = 0);


template <typename SimpleAction, typename Value, typename BinaryOperation>
Value fold (SimpleAction simple_action, Value v, BinaryOperation operation
            , typename boost::enable_if
            <boost::is_base_of
             <gntl::concept::structure::simple_action_tag
              , typename concept::structure::action_traits
              <SimpleAction>::category_tag>, void>::type* = 0)
{
  return operation(v, simple_action);
}

template <typename CompoundAction, typename Value, typename BinaryOperation>
Value fold (CompoundAction compound_action, Value v, BinaryOperation operation
            , typename boost::enable_if
            <boost::is_base_of
             <gntl::concept::structure::compound_action_tag
              , typename concept::structure::action_traits
              <CompoundAction>::category_tag>, void>::type* = 0)
{
  GNTL_DEBUG_LOG("compound action fold" << std::endl)
  typedef concept::structure::compound_action_traits<CompoundAction> traits;
  typedef typename traits::action_range action_range;
  action_range actions = traits::action_all(compound_action);
  typedef typename boost::range_iterator<action_range>::type action_iterator;
  for(action_iterator first = boost::begin(actions)
        , last = boost::end(actions); first != last; ++first)
  {
    v = fold(*first, v, operation);
  }
  return v;
}

template <typename Iter, typename EndIter, typename ActionExpression
          , typename Value, typename BinaryOperation>
Value fold_action_expression (ActionExpression, Value, BinaryOperation
                              , typename boost::enable_if
                              <boost::is_same<Iter, EndIter>
                               , void>::type* = 0)
{
  // This should *never* happen
  std::abort();
  throw -1;
}

template <typename Iter, typename EndIter, typename ActionExpression
          , typename Value, typename BinaryOperation>
Value fold_action_expression (ActionExpression a, Value v, BinaryOperation op
                              , typename boost::disable_if
                              <boost::is_same<Iter, EndIter>
                               , void>::type* = 0)
{
  typedef concept::structure::action_expression_traits
    <ActionExpression> action_expression_traits;
  typedef typename boost::mpl::deref<Iter>::type action_type;
  if(action_expression_traits::template is_type<action_type>(a))
  {
    return action::fold(action_expression_traits::template get<action_type>(a), v, op);
  }
  else
    return fold_action_expression<typename boost::mpl::next<Iter>::type, EndIter> (a, v, op);
}

template <typename ActionExpression, typename Value, typename BinaryOperation>
Value fold (ActionExpression action_expression, Value v, BinaryOperation operation
            , typename boost::enable_if
            <typename concept::structure::action_expression_traits
             <ActionExpression>::is_action_expression, void>::type*)
{
  typedef typename concept::structure::action_expression_traits
    <ActionExpression> action_expression_traits;
  typedef typename action_expression_traits::action_list_type
    action_list_type;
  return fold_action_expression
    <typename boost::mpl::begin<action_list_type>::type
     , typename boost::mpl::end<action_list_type>::type>
    (action_expression, v, operation);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
