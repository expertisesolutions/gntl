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

#ifndef GNTL_ALGORITHM_STRUCTURE_LINK_EVALUATE_HPP
#define GNTL_ALGORITHM_STRUCTURE_LINK_EVALUATE_HPP

#include <gntl/concept/structure/link.hpp>
#include <gntl/algorithm/structure/condition/evaluate.hpp>
#include <gntl/algorithm/structure/condition/evaluate_bound_simple_condition.hpp>
#include <gntl/algorithm/structure/condition/evaluate_assessment_statement.hpp>

#include <boost/bind.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace link {

namespace link_detail {

struct evaluate_bound_simple_condition_functor
{
  typedef bool result_type;
  template <typename BoundSimpleCondition, typename Document, typename Context>
  result_type operator()(BoundSimpleCondition c, Document d, Context b
                         , typename boost::enable_if
                         <typename concept::structure::bounded_simple_condition_traits
                         <typename unwrap_parameter<BoundSimpleCondition>::type
                         >::is_bounded_simple_condition
                         , void*>::type = 0) const
  {
    return condition::evaluate_bound_simple_condition(c, d, b);
  }

  template <typename AssessmentStatement, typename Document, typename Context>
  result_type operator()(AssessmentStatement a, Document d, Context b
                         , typename boost::enable_if
                         <typename concept::structure::bound_assessment_statement_traits
                         <typename unwrap_parameter<AssessmentStatement>::type
                         >::is_bound_assessment_statement
                         , void*>::type = 0) const
  {
    return condition::evaluate_assessment_statement(a, d, b);
  }
};

}

template <typename Link, typename Document, typename Context>
bool evaluate (Link link, Document document, Context context)
{
  typedef typename unwrap_parameter<Link>::type link_type;
  typedef concept::structure::link_traits<link_type> link_traits;
  if(gntl::algorithm::structure::condition
     ::evaluate(link_traits::condition_expression(link)
                , boost::bind(link_detail::evaluate_bound_simple_condition_functor(), _1
                              , document, context)))
  {
    return true;
  }
  return false;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif

