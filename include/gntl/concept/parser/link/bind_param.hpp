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

#ifndef GNTL_CONCEPT_PARSER_LINK_BIND_PARAM_HPP
#define GNTL_CONCEPT_PARSER_LINK_BIND_PARAM_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct bind_param_traits
{
  typedef boost::mpl::false_ is_bind_param;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct BindParam
{
  typedef bind_param_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_bind_param::value, ==, true);
  typedef typename traits::name_type name_type;
  typedef typename traits::value_type value_type;

  BOOST_CONCEPT_USAGE(BindParam)
  {
    convertible_to<name_type>(traits::name(i));
    convertible_to<value_type>(traits::value(i));
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
