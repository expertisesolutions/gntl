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

#ifndef GNTL_ALGORITHM_STRUCTURE_ACTION_HPP
#define GNTL_ALGORITHM_STRUCTURE_ACTION_HPP

#include <gntl/concept/structure/action/action_expression.hpp>
#include <gntl/concept/structure/action/compound_action.hpp>

#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace action {

template <typename SimpleAction, typename Operation>
void execute (SimpleAction simple_action
              , Operation operation
              , typename boost::enable_if
              <boost::is_base_of
               <gntl::concept::structure::simple_action_tag
                , typename concept::structure::action_traits
                <SimpleAction>::category_tag>, void>::type* = 0)
{
  operation(simple_action);
}

template <typename Operation>
struct execute_function;

template <typename CompoundAction, typename Operation>
void execute (CompoundAction compound_action
              , Operation operation
              , typename boost::enable_if
              <boost::is_base_of
               <gntl::concept::structure::compound_action_tag
                , typename concept::structure::action_traits
                <CompoundAction>::category_tag>, void>::type* = 0)
{
  GNTL_DEBUG_LOG("compound action execution" << std::endl)
  typedef concept::structure::compound_action_traits
    <CompoundAction> traits;
  gntl::range::for_each(traits::action_all(compound_action)
                        , execute_function<Operation>(operation));
}

template <typename Iter, typename EndIter
          , typename ActionExpression
          , typename Predicate>
void evaluate_action_expression (ActionExpression
                                    , Predicate
                                    , typename boost::enable_if
                                    <boost::is_same<Iter, EndIter>
                                     , void>::type* = 0)
{
  std::abort();
}

template <typename Iter, typename EndIter
          , typename ActionExpression
          , typename Predicate>
void evaluate_action_expression (ActionExpression a
                                    , Predicate op
                                    , typename boost::disable_if
                                    <boost::is_same<Iter, EndIter>
                                     , void>::type* = 0)
{
  typedef concept::structure::action_expression_traits
    <ActionExpression> action_expression_traits;
  typedef typename boost::mpl::deref<Iter>::type action_type;
  if(action_expression_traits::template is_type<action_type>(a))
  {
    execute(action_expression_traits::template get<action_type>(a), op);
  }
  else
    evaluate_action_expression
      <typename boost::mpl::next<Iter>::type
       , EndIter>
      (a, op);
}

template <typename ActionExpression, typename Operation>
void execute (ActionExpression action_expression
              , Operation operation
              , typename boost::enable_if
              <typename concept::structure::action_expression_traits
               <ActionExpression>::is_action_expression, void>::type* = 0)
{
  typedef typename concept::structure::action_expression_traits
    <ActionExpression> action_expression_traits;
  typedef typename action_expression_traits::action_list_type
    action_list_type;
  evaluate_action_expression
    <typename boost::mpl::begin<action_list_type>::type
     , typename boost::mpl::end<action_list_type>::type>
    (action_expression, operation);
}

template <typename Operation>
struct execute_function
{
  execute_function(Operation op) : op(op) {}

  typedef void result_type;
  template <typename Action>
  result_type operator()(Action a)
  {
    execute(a, op);
  }

  Operation op;
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
