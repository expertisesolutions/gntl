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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_BOUND_SIMPLE_CONDITION_PREDICATE_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_BOUND_SIMPLE_CONDITION_PREDICATE_HPP

#include <gntl/event_enum.hpp>
#include <gntl/transition_enum.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/algorithm/structure/condition/defaults.hpp>
#include <gntl/detail/void.hpp>

#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

template <typename BoundSimpleCondition, typename Document
          , typename Body>
bool evaluate_bound_simple_condition (BoundSimpleCondition const& condition
                                      , Document const& document
                                      , Body const& body)
{
  GNTL_DEBUG_LOG("evaluate_bound_simple_condition" << std::endl)
  typedef typename boost::unwrap_reference<BoundSimpleCondition>::type condition_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef gntl::concept::structure::document_traits
    <document_type> structure_document_traits;
  GNTL_CONCEPT_ASSERT((gntl::concept::structure::BoundedSimpleCondition<condition_type>));
  GNTL_DEBUG_LOG("condition " << typeid(condition_type).name() << std::endl)
  typedef gntl::concept::structure::bounded_simple_condition_traits
    <condition_type> condition_traits;

  typedef typename condition_traits::component_range
    component_range;
  component_range components = condition_traits::components(condition);
  typedef typename boost::range_value<component_range>::type
    bound_component_type;
  typedef gntl::concept::structure::condition_bound_component_traits
    <bound_component_type> traits;

  // gntl::event_type ev;
  // gntl::transition_type tc;
  if(condition_traits::has_event_type (condition) && condition_traits::has_transition (condition))
  {
    // ev = condition_traits::event_type(condition);
    // tc = condition_traits::transition(condition);
  }
  else if(boost::optional<std::pair<gntl::event_type, gntl::transition_type> > p
          = gntl::algorithm::structure::condition::default_from_role
          <gntl::event_type, gntl::transition_type>(condition_traits::role(condition)))
  {
    // ev = p->first;
    // tc = p->second;
  }
  else
  {
    GNTL_DEBUG_LOG("Couldn't find what transition and event type this condition is to" << std::endl)
    return false;
  }

  bool qualifier_and
    = condition_traits::has_qualifier(condition)
    && condition_traits::qualifier(condition) == "and";
  std::size_t size = boost::distance(components);
  GNTL_DEBUG_LOG("Number of components bound " << size << std::endl)
  std::size_t min = 1, max = 1;
  if(condition_traits::has_min(condition))
    min = condition_traits::min(condition)?*condition_traits::min(condition)
      :(std::numeric_limits<std::size_t>::max)();
  if(size < min)
    return false; // should we throw?

  if(condition_traits::has_max(condition))
    max = condition_traits::max(condition)?*condition_traits::max(condition)
      :(std::numeric_limits<std::size_t>::max)();
  if(size > max)
    return false; // should we throw?

  if(min > max)
    return false;

  if(size == 0)
  {
    GNTL_DEBUG_LOG("size is 0, failing condition (no components)" << std::endl)
    return false; // we should throw?
  }

  for(typename boost::range_iterator<component_range>::type
        first = boost::begin(components)
        , last = boost::next(boost::begin(components), size)
        ;first != last; ++first)
  {
    GNTL_DEBUG_LOG("component: " << traits::component(*first) << std::endl)
    bool r = traits::state(*first);
    if(r)
    {
      if(!qualifier_and)
        return true;
    }
    else if(qualifier_and)
      return false;      
  }

  return qualifier_and;
}


struct evaluate_bound_simple_condition_functor
{
  typedef bool result_type;
  template <typename BoundSimpleCondition, typename Document, typename Body>
  result_type operator()(BoundSimpleCondition const& c, Document const& d, Body const& b) const
  {
    return evaluate_bound_simple_condition(c, d, b);
  }
};

template <typename BoundSimpleCondition, typename Document>
bool evaluate (BoundSimpleCondition const& condition
               , Document const& document
               , typename boost::enable_if
                 <
                   boost::mpl::and_
                   <
                     typename gntl::concept::structure::bounded_simple_condition_traits
                     <typename boost::unwrap_reference<BoundSimpleCondition>::type>
                     ::is_bounded_simple_condition
                     , typename gntl::concept::structure::document_traits
                     <typename boost::unwrap_reference<Document>::type>
                     ::is_document
                   >
                 , gntl::detail::void_
                 >::type = gntl::detail::void_())
{
  return evaluate_bound_simple_condition(condition, document);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
