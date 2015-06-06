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

#ifndef GNTL_CONCEPT_PARSER_RULE_HPP
#define GNTL_CONCEPT_PARSER_RULE_HPP

#include <gntl/rule_comparator.hpp>
#include <gntl/concept/parser/rule/simple_rule.hpp>
#include <gntl/concept/parser/rule/composite_rule.hpp>

#include <gntl/concept_check.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/static_assert.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct rule_traits
{
  typedef boost::mpl::false_ is_rule;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Rule
{
  typedef rule_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_rule::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::simple_rule_type simple_rule_type;
  typedef typename traits::composite_rule_type composite_rule_type;

  BOOST_CONCEPT_ASSERT ((SimpleRule<simple_rule_type>));
  BOOST_CONCEPT_ASSERT ((CompositeRule<composite_rule_type>));

  BOOST_CONCEPT_USAGE (Rule)
  {
    is_convertible<bool>(traits::is_composite(const_i));
    is_convertible<identifier_type>(traits::identifier (const_i));
    is_convertible<simple_rule_type>(traits::simple_rule (const_i));
    is_convertible<composite_rule_type>(traits::composite_rule (const_i));
  }

  template <typename T0, typename T1>
  void is_convertible (T1 const&)
  {
      BOOST_STATIC_ASSERT ((boost::is_convertible<T1,T0>::type::value));
  }

  Rule();

  X const const_i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
