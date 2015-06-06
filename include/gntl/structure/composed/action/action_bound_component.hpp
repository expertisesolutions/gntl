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

#ifndef GNTL_STRUCTURE_COMPOSED_ACTION_ACTION_BOUND_COMPONENT_HPP
#define GNTL_STRUCTURE_COMPOSED_ACTION_ACTION_BOUND_COMPONENT_HPP

#include <gntl/concept/parser/connector/connector_simple_action.hpp>
#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/concept/structure/action/action_bound_component.hpp>

#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Bind, typename SimpleAction>
struct action_bound_component
{
  action_bound_component(Bind bind, SimpleAction simple_action)
    : bind(bind), simple_action(simple_action)
  {}

  Bind bind;
  SimpleAction simple_action;
};

} }

namespace concept { namespace structure {

template <typename Bind, typename SimpleAction>
struct action_bound_component_traits
  <gntl::structure::composed::action_bound_component<Bind, SimpleAction> >
{
  typedef boost::mpl::true_ is_action_bound_component;
  typedef gntl::structure::composed::action_bound_component<Bind, SimpleAction>
    bound_component;

  typedef concept::parser::connector_simple_action_traits
    <SimpleAction> simple_action_traits;
  typedef concept::parser::bind_traits
    <Bind> bind_traits;

  typedef typename simple_action_traits::delay_type delay_type;
  typedef typename simple_action_traits::string_type string_type;
  typedef typename simple_action_traits::qualifier_type qualifier_type;
  typedef typename simple_action_traits::repeat_type repeat_type;
  typedef typename simple_action_traits::repeat_delay_type repeat_delay_type;
  typedef typename simple_action_traits::duration_type duration_type;
  typedef typename simple_action_traits::by_type by_type;

  typedef typename bind_traits::component_type component_type;
  typedef typename bind_traits::interface_type interface_type;
  typedef typename bind_traits::descriptor_type descriptor_type;

  static string_type substitute_params (bound_component c, string_type string)
  {
    if(!string.empty() && *string.begin() == '$')
    {
      typedef typename bind_traits::bind_param_range bind_param_range;
      bind_param_range bind_params = bind_traits::bind_param(c.bind);

      typedef typename boost::range_iterator
        <bind_param_range>::type bind_param_iterator;
      typedef typename boost::range_value
        <bind_param_range>::type bind_param_type;
      typedef concept::parser::bind_param_traits
        <bind_param_type> bind_param_traits;
      for(bind_param_iterator first = boost::begin(bind_params)
          , last = boost::end(bind_params)
          ;first != last
          ;++first)
      {
        typename bind_param_traits::name_type name = bind_param_traits::name (*first);
        typedef typename string_type::const_iterator string_iterator;
        if(
#if BOOST_VERSION > 104200
           boost::range::equal(name
                              , boost::iterator_range<string_iterator>
                              (boost::next(string.begin()), string.end()))
#else
           (std::distance(boost::begin(name), boost::end(name))
            == std::distance(boost::next(string.begin()), string.end())
            && std::equal(boost::next(string.begin()), string.end(), boost::begin(name)))
#endif
          )  
          return bind_param_traits::value (*first);
      }      
    }
    return string;
  }

  static delay_type delay (bound_component c)
  {
    return simple_action_traits::delay (c.simple_action);
  }
  static bool has_delay (bound_component c)
  {
    return simple_action_traits::has_delay (c.simple_action);
  }
  static string_type value (bound_component c)
  {
    return substitute_params(c, simple_action_traits::value (c.simple_action));
  }
  static bool has_value (bound_component c)
  {
    return simple_action_traits::has_value (c.simple_action);
  }
  static qualifier_type qualifier (bound_component c)
  {
    return simple_action_traits::qualifier (c.simple_action);
  }
  static bool has_qualifier (bound_component c)
  {
    return simple_action_traits::has_qualifier (c.simple_action);
  }
  static repeat_type repeat (bound_component c)
  {
    return simple_action_traits::repeat (c.simple_action);
  }
  static bool has_repeat (bound_component c)
  {
    return simple_action_traits::has_repeat (c.simple_action);
  }
  static repeat_delay_type repeat_delay (bound_component c)
  {
    return simple_action_traits::repeat_delay (c.simple_action);
  }
  static bool has_repeat_delay (bound_component c)
  {
    return simple_action_traits::has_repeat_delay (c.simple_action);
  }
  static duration_type duration (bound_component c)
  {
    return simple_action_traits::duration (c.simple_action);
  }
  static bool has_duration (bound_component c)
  {
    return simple_action_traits::has_duration (c.simple_action);
  }
  static by_type by (bound_component c)
  {
    return simple_action_traits::by (c.simple_action);
  }
  static bool has_by (bound_component c)
  {
    return simple_action_traits::has_by (c.simple_action);
  }

  static component_type component(bound_component c)
  {
    return bind_traits::component(c.bind);
  }
  static bool has_interface(bound_component c)
  {
    return bind_traits::has_interface(c.bind);
  }
  static interface_type interface_(bound_component c)
  {
    return bind_traits::interface_(c.bind);
  }
  static bool has_descriptor(bound_component c)
  {
    return bind_traits::has_descriptor(c.bind);
  }
  static descriptor_type descriptor(bound_component c)
  {
    return bind_traits::descriptor(c.bind);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif

