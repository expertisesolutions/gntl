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

#ifndef GNTL_CONCEPT_PARSER_COMPOSITERULE_HPP
#define GNTL_CONCEPT_PARSER_COMPOSITERULE_HPP

#include <gntl/rule_operator.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct composite_rule_traits
{
  typedef boost::mpl::false_ is_composite_rule;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct CompositeRule
{
    typedef composite_rule_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_composite_rule::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::operator_type operator_type;
    typedef typename traits::rule_range rule_range;

    BOOST_CONCEPT_USAGE (CompositeRule)
    {
      convertible_to <identifier_type>(traits::identifier (i));
      convertible_to <operator_type>(traits::operator_ (i));
      convertible_to <rule_range>(traits::rule_all (i));
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
