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

#ifndef GNTL_CONCEPT_PARSER_TRANSITION_BASE_TRAITS_HPP
#define GNTL_CONCEPT_PARSER_TRANSITION_BASE_TRAITS_HPP

#include <gntl/concept_check.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct transition_base_traits
{
  typedef boost::mpl::false_ is_transition_base;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct TransitionBase
{
  typedef transition_base_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_transition_base::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::transition_range transition_range;

  BOOST_CONCEPT_ASSERT ((boost::ForwardRangeConcept<typename unwrap_parameter<transition_range>::type>));

  BOOST_CONCEPT_USAGE (TransitionBase)
  {
    convertible_to<bool>(traits::has_identifier (i));
    convertible_to<identifier_type>(traits::identifier (i));
    convertible_to<transition_range>(traits::transition_all (i));
  }

  template <typename T0, typename T1>
  void convertible_to (T1 const&)
  {
    BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
  }

  X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
