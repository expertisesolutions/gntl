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

#ifndef GNTL_CONCEPT_PARSER_RULEBASE_HPP
#define GNTL_CONCEPT_PARSER_RULEBASE_HPP

#include <gntl/concept/parser/rule/rule.hpp>
#include <gntl/parameter.hpp>
#include <gntl/concept_check.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/static_assert.hpp>

#include <iterator>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct rule_base_traits
{
  typedef boost::mpl::false_ is_rule_base;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct RuleBase : boost::CopyConstructible<X>
{
    typedef rule_base_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_rule_base::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::rule_range rule_range;

    BOOST_CONCEPT_ASSERT((boost::ForwardRangeConcept<rule_range>));

    typedef typename boost::range_value<typename unwrap_parameter<rule_range>::type>::type
      rule_value_type;
    BOOST_CONCEPT_ASSERT((Rule<typename unwrap_parameter<rule_value_type>::type>));

    BOOST_CONCEPT_USAGE (RuleBase)
    {
      convertible_to<identifier_type> (traits::identifier (const_i));
      convertible_to<bool> (traits::has_identifier (const_i));
      convertible_to<rule_range> (traits::rule_all (const_i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_STATIC_ASSERT ((boost::is_convertible<T1, T0>::type::value));
    }

    RuleBase();

    X const const_i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
