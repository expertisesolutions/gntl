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

#ifndef GNTL_STRUCTURE_COMPOSED_CONDITION_BOUNDED_SIMPLE_CONDITION_HPP
#define GNTL_STRUCTURE_COMPOSED_CONDITION_BOUNDED_SIMPLE_CONDITION_HPP

#include <gntl/concept/parser/connector/connector_simple_condition.hpp>
#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/concept/parser/link/bind_param.hpp>
#include <gntl/concept/structure/condition/bounded_simple_condition.hpp>
#include <gntl/concept/structure/condition/condition.hpp>
#include <gntl/structure/composed/condition/condition_bound_component.hpp>

#include <boost/iterator/transform_iterator.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename BindContainer, typename SimpleConditionParser, typename Role>
struct bounded_simple_condition
{
  typedef typename boost::unwrap_reference<Role>::type role_type;
  bounded_simple_condition(BindContainer bind_container
                           , SimpleConditionParser condition
                           , std::map<role_type, bool>* role_conditions)
    : bind_container(bind_container), condition(condition)
    , role_conditions(role_conditions) {}

  typedef BindContainer bind_container_type;
  typedef SimpleConditionParser simple_condition_type;

  BindContainer bind_container;
  SimpleConditionParser condition;
  std::map<role_type, bool>* role_conditions;
};

} }

namespace concept { namespace structure {

template <typename BindContainer, typename SimpleCondition, typename Role>
struct bounded_simple_condition_traits<gntl::structure::composed
                                       ::bounded_simple_condition<BindContainer, SimpleCondition, Role> >
{
  typedef boost::mpl::true_ is_bounded_simple_condition;
  typedef gntl::structure::composed
    ::bounded_simple_condition<BindContainer, SimpleCondition, Role>
    bounded_simple_condition;
  typedef typename boost::range_value<BindContainer>::type bind_type;
  typedef typename boost::range_const_iterator<BindContainer>::type bind_iterator;
  typedef concept::parser::connector_simple_condition_traits
    <SimpleCondition> simple_condition_traits;

  typedef gntl::structure::composed::condition_bound_component
    <bind_type, SimpleCondition> bound_component;

  typedef typename simple_condition_traits::role_type role_type;
  typedef typename simple_condition_traits::event_type_type event_type_type;
  typedef typename simple_condition_traits::transition_type transition_type;
  typedef typename simple_condition_traits::min_type min_type;
  typedef typename simple_condition_traits::max_type max_type;
  typedef typename simple_condition_traits::qualifier_type qualifier_type;

  struct component_transform
  {
    component_transform(SimpleCondition simple_condition
                        , std::map<role_type, bool>& role_conditions)
      : simple_condition(simple_condition), role_conditions(&role_conditions)
    {}

    typedef bound_component result_type;
    template <typename Bind>
    result_type operator()(Bind bind) const
    {
      return bound_component(bind, simple_condition, *role_conditions);
    }

    SimpleCondition simple_condition;
    std::map<role_type, bool>* role_conditions;
  };
  typedef boost::transform_iterator<component_transform, bind_iterator>
    bound_component_iterator;
  typedef boost::iterator_range<bound_component_iterator> component_range;

  static role_type role(bounded_simple_condition const& c)
  { return simple_condition_traits::role(c.condition); }
  static bool has_event_type(bounded_simple_condition const& c)
  { return simple_condition_traits::has_event_type(c.condition); }
  static event_type_type event_type(bounded_simple_condition const& c)
  { return simple_condition_traits::event_type(c.condition); }
  static bool has_transition(bounded_simple_condition const& c)
  { return simple_condition_traits::has_transition(c.condition); }
  static transition_type transition(bounded_simple_condition const& c)
  { return simple_condition_traits::transition(c.condition); }
  static bool has_min(bounded_simple_condition const& c)
  { return simple_condition_traits::has_min(c.condition); }
  static min_type (min)(bounded_simple_condition const& c)
  { return (simple_condition_traits::min)(c.condition); }
  static bool has_max(bounded_simple_condition const& c)
  { return simple_condition_traits::has_max(c.condition); }
  static max_type (max)(bounded_simple_condition const& c)
  { return (simple_condition_traits::max)(c.condition); }
  static bool has_qualifier(bounded_simple_condition const& c)
  { return simple_condition_traits::has_qualifier(c.condition); }
  static qualifier_type qualifier(bounded_simple_condition const& c)
  { return simple_condition_traits::qualifier(c.condition); }
  static component_range components(bounded_simple_condition const& c)
  { 
    component_transform transform(c.condition, *c.role_conditions);
    return component_range(bound_component_iterator(c.bind_container.begin(), transform)
                           , bound_component_iterator(c.bind_container.end(), transform));
  }
};

template <typename BindContainer, typename SimpleCondition, typename Role>
struct condition_traits<gntl::structure::composed
                        ::bounded_simple_condition<BindContainer, SimpleCondition, Role> >
{
  typedef boost::mpl::true_ is_condition;
  typedef concept::structure::simple_condition_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
