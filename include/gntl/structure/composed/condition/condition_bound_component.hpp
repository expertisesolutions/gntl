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

#ifndef GNTL_STRUCTURE_COMPOSED_CONDITION_BOUND_COMPONENT_HPP
#define GNTL_STRUCTURE_COMPOSED_CONDITION_BOUND_COMPONENT_HPP

#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/concept/parser/connector/connector_simple_condition.hpp>
#include <gntl/concept/structure/condition/condition_bound_component.hpp>
#include <gntl/log/log.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Bind, typename SimpleCondition>
struct condition_bound_component
{
  typedef typename boost::unwrap_reference<Bind>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;
  condition_bound_component(Bind bind, SimpleCondition simple_condition
                            , std::map<role_type, bool>& role_conditions)
    : set(false), bind(bind), simple_condition(simple_condition)
    , role_conditions(&role_conditions)
  {}

  bool set;
  Bind bind;
  SimpleCondition simple_condition;
  std::map<role_type, bool>* role_conditions;
};

} }

namespace concept { namespace structure {

template <typename Bind, typename SimpleCondition>
struct condition_bound_component_traits<gntl::structure::composed::condition_bound_component
                                        <Bind, SimpleCondition> >
{
  typedef boost::mpl::true_ is_condition_bound_component;
  typedef gntl::structure::composed::condition_bound_component
    <Bind, SimpleCondition> condition_bound_component;

  typedef typename boost::unwrap_reference<Bind>::type bind_type;
  typedef typename boost::unwrap_reference<SimpleCondition>::type simple_condition_type;

  typedef concept::parser::bind_traits
    <bind_type> bind_traits;
  typedef concept::parser::connector_simple_condition_traits
    <simple_condition_type> simple_condition_traits;

  typedef typename bind_traits::component_type component_type;
  typedef typename bind_traits::interface_type interface_type;
  typedef typename bind_traits::descriptor_type descriptor_type;
  typedef typename simple_condition_traits::delay_type delay_type;
  typedef typename simple_condition_traits::key_type key_type;

  static void set(condition_bound_component& c)
  {
    typename bind_traits::role_type role = bind_traits::role(c.bind);
    GNTL_DEBUG_LOG("===== component is being set " << role << std::endl)
    (*c.role_conditions)[role] = true;
  }
  static void reset(condition_bound_component& c)
  {
    typedef typename bind_traits::role_type role_type;
    role_type role = bind_traits::role(c.bind);
    typename std::map<role_type, bool>::iterator
      iterator = c.role_conditions->find(role);
    if(iterator != c.role_conditions->end())
      c.role_conditions->erase(iterator);
  }
  static bool state(condition_bound_component const& c)
  {
    typedef typename bind_traits::role_type role_type;
    role_type role = bind_traits::role(c.bind);
    typename std::map<role_type, bool>::const_iterator
      iterator = c.role_conditions->find(role);
    bool r = (iterator != c.role_conditions->end() && iterator->second);
    GNTL_DEBUG_LOG("condition " << role << " is set? " << r << " " 
                   << c.role_conditions->size() << std::endl)
    return r;
  }
  static component_type component(condition_bound_component const& c)
  { return bind_traits::component(c.bind); }
  static bool has_interface(condition_bound_component const& c)
  { return bind_traits::has_interface(c.bind); }
  static interface_type interface_(condition_bound_component const& c)
  { return bind_traits::interface_(c.bind); }
  static bool has_descriptor(condition_bound_component const& c)
  { return bind_traits::has_descriptor(c.bind); }
  static descriptor_type descriptor(condition_bound_component const& c)
  { return bind_traits::descriptor(c.bind); }

  static bool has_delay(condition_bound_component const& c)
  { return simple_condition_traits::has_delay(c.simple_condition); }
  static delay_type delay(condition_bound_component const& c)
  { return simple_condition_traits::delay(c.simple_condition); }
  static bool has_key(condition_bound_component const& c)
  { return simple_condition_traits::has_key(c.simple_condition); }
  static key_type key(condition_bound_component const& c)
  { 
    typedef typename bind_traits::bind_param_range bind_param_range;
    bind_param_range bind_params = bind_traits::bind_param(c.bind);
    typedef typename simple_condition_traits::key_type key_type;
    key_type key = simple_condition_traits::key(c.simple_condition); 
    if(boost::distance(bind_params) != 0)
    {
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
        typedef typename key_type::const_iterator key_iterator;
        key_iterator key_first = boost::begin(key)
          , key_last = boost::end(key);
        if(key_first != key_last && *(key_first++) == '$'
           &&
#if BOOST_VERSION > 104200
           boost::range::equal(name
                                  , boost::iterator_range<key_iterator>
                                  (key_first, key_last))
#else
           (std::distance(boost::begin(name), boost::end(name))
            == std::distance(key_first, key_last)
            && std::equal(key_first, key_last, boost::begin(name)))
#endif
           )
          return bind_param_traits::value (*first);
      }
    }
    return key;
  }
  
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif

