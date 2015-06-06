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

#ifndef GNTL_STRUCTURE_COMPOSED_RULE_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_RULE_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename RuleRange>
struct rule_lookupable
{
  rule_lookupable(RuleRange rules)
    : rules(rules) {}
  
  RuleRange rules;
};

} }

namespace concept {

template <typename RuleRange>
struct lookupable_traits<gntl::structure::composed::rule_lookupable<RuleRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::rule_lookupable<RuleRange> rule_lookupable;
  typedef typename unwrap_parameter<RuleRange>::type rule_range;
  typedef typename boost::range_value<rule_range>::type rule_value_type;
  typedef typename boost::range_iterator<rule_range>::type rule_iterator;
  typedef typename unwrap_parameter<rule_value_type>::type rule_type;

  typedef concept::parser::rule_traits<rule_type> rule_traits;
  typedef typename rule_traits::identifier_type identifier_type;
  typedef identifier_type key_type;
  typedef rule_value_type value_type;
  
  struct result_type
  {
    result_type(rule_iterator iterator)
      : iterator(iterator) {}
    bool operator==(result_type const& other) const
    {
      return iterator == other.iterator;
    }
    bool operator!=(result_type const& other) const
    {
      return !(*this == other);
    }
    rule_value_type operator*() const { return *iterator; }
    rule_iterator iterator;
  };

  static result_type lookup(rule_lookupable const& l, key_type const& k)
  {
    rule_iterator first = boost::begin(l.rules)
      , last = boost::end(l.rules);
    for(; first != last; ++first)
    {
      GNTL_DEBUG_LOG("testing " << rule_traits::identifier(*first) << std::endl)
      if(rule_traits::identifier(*first) == k)
        return result_type(first);
    }
    return result_type(first);
  }

  static result_type not_found(rule_lookupable const& l)
  {
    return boost::end(l.rules);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
