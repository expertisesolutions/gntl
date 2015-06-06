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

#ifndef GNTL_STRUCTURE_COMPOSED_ACTION_BOUND_SIMPLE_ACTION_HPP
#define GNTL_STRUCTURE_COMPOSED_ACTION_BOUND_SIMPLE_ACTION_HPP

#include <gntl/concept/structure/action/action.hpp>
#include <gntl/concept/structure/action/bound_simple_action.hpp>
#include <gntl/structure/composed/action/action_bound_component.hpp>

#include <boost/iterator/transform_iterator.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename BindRange, typename SimpleAction>
struct bound_simple_action
{
  bound_simple_action(BindRange bind_range, SimpleAction simple_action)
    : bind_range(bind_range), simple_action(simple_action) {}

  BindRange bind_range;
  SimpleAction simple_action;
};

} }

namespace concept { namespace structure {

template <typename BindRange, typename SimpleAction>
struct action_traits<gntl::structure::composed
                     ::bound_simple_action<BindRange, SimpleAction> >
{
  typedef boost::mpl::true_ is_action;
  typedef gntl::concept::structure::simple_action_tag category_tag;
};

template <typename BindRange, typename SimpleAction>
struct bound_simple_action_traits<gntl::structure::composed
                                  ::bound_simple_action<BindRange, SimpleAction> >
{
  typedef boost::mpl::true_ is_bound_simple_action;
  typedef gntl::structure::composed
    ::bound_simple_action<BindRange, SimpleAction>
    bound_simple_action;
  typedef concept::parser::connector_simple_action_traits
    <SimpleAction> simple_action_traits;
  typedef typename boost::range_value<BindRange>::type bind_type;
  typedef typename boost::range_iterator<BindRange>::type bind_iterator;
  typedef concept::parser::bind_traits
    <bind_type> bind_traits;
  typedef typename simple_action_traits::role_type role_type;
  typedef typename simple_action_traits::event_type_type event_type_type;
  typedef typename simple_action_traits::action_type_type action_type_type;
  typedef typename simple_action_traits::min_type min_type;
  typedef typename simple_action_traits::max_type max_type;
  
  typedef gntl::structure::composed::action_bound_component
    <bind_type, SimpleAction> bound_component;

  struct component_transform
  {
    component_transform(SimpleAction simple_action)
      : simple_action(simple_action)
    {}

    typedef bound_component result_type;
    result_type operator()(bind_type bind) const
    {
      return bound_component(bind, simple_action);
    }

    SimpleAction simple_action;
  };

  typedef boost::transform_iterator<component_transform
                                    , bind_iterator> bound_component_iterator;
  typedef boost::iterator_range<bound_component_iterator> component_range;

  static role_type role (bound_simple_action a)
  {
    return simple_action_traits::role (a.simple_action);
  }
  static event_type_type event_type (bound_simple_action a)
  {
    return simple_action_traits::event_type (a.simple_action);
  }
  static bool has_event_type (bound_simple_action a)
  {
    return simple_action_traits::has_event_type (a.simple_action);
  }
  static action_type_type action_type (bound_simple_action a)
  {
    return simple_action_traits::action_type (a.simple_action);
  }
  static bool has_action_type (bound_simple_action a)
  {
    return simple_action_traits::has_action_type (a.simple_action);
  }
  static min_type (min) (bound_simple_action a)
  {
    return (simple_action_traits::min) (a.simple_action);
  }
  static bool has_min (bound_simple_action a)
  {
    return simple_action_traits::has_min (a.simple_action);
  }
  static max_type (max) (bound_simple_action a)
  {
    return (simple_action_traits::max) (a.simple_action);
  }
  static bool has_max (bound_simple_action a)
  {
    return simple_action_traits::has_max (a.simple_action);
  }

  static component_range component_all(bound_simple_action a)
  {
    component_transform transform(a.simple_action);
    return component_range(bound_component_iterator(boost::begin(a.bind_range), transform)
                           , bound_component_iterator(boost::end(a.bind_range), transform));
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
