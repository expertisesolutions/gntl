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

#ifndef GNTL_ALGORITHM_STRUCTURE_SWITCH_EVALUATE_HPP
#define GNTL_ALGORITHM_STRUCTURE_SWITCH_EVALUATE_HPP

#include <gntl/parameter.hpp>
#include <gntl/algorithm/structure/component/lookup.hpp>
#include <gntl/algorithm/structure/rule/evaluate.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace switch_ {

namespace switch_detail {

template <typename Switch, typename Identifier>
struct select_switch
{
  select_switch(Switch switch_, Identifier identifier)
    : switch_(switch_), identifier(identifier)
  {}

  typedef void result_type;
  template <typename Component>
  result_type operator()(Component c) const
  {
    GNTL_DEBUG_LOG("should select component: " << identifier << std::endl)
    typedef typename unwrap_parameter<Switch>::type switch_type;
    typedef concept::structure::switch_traits<switch_type> switch_traits;
    switch_traits::activate_component(switch_, identifier);
  }

  Switch switch_;
  Identifier identifier;
};

}

template <typename Switch, typename Document>
void evaluate(Switch switch_, Document document)
{
  GNTL_DEBUG_LOG("evaluate" << std::endl)
  typedef typename unwrap_parameter<Switch>::type switch_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::switch_traits<switch_type> switch_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  typedef typename switch_traits::bind_rule_range bind_rule_value_range;
  bind_rule_value_range bind_rules = switch_traits::bind_rule_all(switch_);
  typedef typename unwrap_parameter<bind_rule_value_range>::type bind_rule_range;
  /* rules */
  typedef typename boost::range_iterator<bind_rule_range>::type bind_rule_iterator;
  for(bind_rule_iterator first = boost::begin(bind_rules), last = boost::end(bind_rules)
        ;first != last; ++first)
  {
    typedef typename boost::range_value<bind_rule_range>::type bind_rule_value_type;
    typedef typename unwrap_parameter<bind_rule_value_type>::type bind_rule_type;
    typedef concept::structure::bind_rule_traits<bind_rule_type> bind_rule_traits;
    typedef typename bind_rule_traits::rule_type rule_type;
    rule_type rule_id = bind_rule_traits::rule(*first);
    GNTL_DEBUG_LOG("Should evaluate rule " << rule_id << std::endl)
    typedef typename document_traits::rule_lookupable lookupable_value_type;
    lookupable_value_type lookupable = document_traits::rule_lookup(document);
    typedef concept::lookupable_traits<typename unwrap_parameter<lookupable_value_type>::type>
      lookupable_traits;
    typedef typename lookupable_traits::result_type lookup_result;
    lookup_result r = lookupable_traits::lookup(lookupable, rule_id);
    if(r != lookupable_traits::not_found(lookupable))
    {
      GNTL_DEBUG_LOG("Found rule, evaluating" << std::endl)
      if(algorithm::structure::rule::evaluate(*r, document))
      {
        GNTL_DEBUG_LOG("Found rule evaluated to true" << std::endl)
        algorithm::structure::component::lookup(bind_rule_traits::constituent(*first)
                                                , switch_detail::select_switch
                                                <Switch
                                                 , typename switch_traits::identifier_type>
                                                (switch_
                                                 , bind_rule_traits::constituent(*first))
                                                , switch_traits::media_lookup(switch_)
                                                , switch_traits::context_lookup(switch_));
        return;
      }
    }
  }
  
  if(switch_traits::has_default_component(switch_))
  {
    GNTL_DEBUG_LOG("select default component" << std::endl)
    algorithm::structure::component::lookup(switch_traits::default_component(switch_)
                                            , switch_detail::select_switch
                                              <Switch
                                               , typename switch_traits::identifier_type>
                                               (switch_
                                                , switch_traits::default_component(switch_))
                                            , switch_traits::media_lookup(switch_)
                                            , switch_traits::context_lookup(switch_));
  }
}

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
