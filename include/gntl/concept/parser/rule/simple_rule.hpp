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

#ifndef GNTL_CONCEPT_PARSER_SIMPLE_RULE_HPP
#define GNTL_CONCEPT_PARSER_SIMPLE_RULE_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct simple_rule_traits
{
  typedef boost::mpl::false_ is_simple_rule;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct SimpleRule
{
  typedef simple_rule_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_simple_rule::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::value_type value_type;
  typedef typename traits::variable_type variable_type;
  typedef typename traits::comparator_type comparator_type;

  BOOST_CONCEPT_USAGE(SimpleRule)
  {
    convertible_to<identifier_type>(traits::identifier(i));
    convertible_to<value_type>(traits::value(i));
    convertible_to<variable_type>(traits::variable(i));
    convertible_to<comparator_type>(traits::comparator(i));
  }

  template <typename T0, typename T1>
  void convertible_to (T1 const&)
  {
    BOOST_STATIC_ASSERT ((boost::is_convertible<T1, T0>::type::value));
  }

  X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif

