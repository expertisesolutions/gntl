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

#ifndef GNTL_CONCEPT_PARSER_LINK_BIND_HPP
#define GNTL_CONCEPT_PARSER_LINK_BIND_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/parser/link/bind_param.hpp>
#include <gntl/range.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct bind_traits
{
  typedef boost::mpl::false_ is_bind;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Bind
{
  typedef bind_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_bind::value, ==, true);
  typedef typename traits::role_type role_type;
  typedef typename traits::component_type component_type;
  typedef typename traits::interface_type interface_type;
  typedef typename traits::descriptor_type descriptor_type;
  typedef typename traits::bind_param_range bind_param_range;

  BOOST_CONCEPT_ASSERT((boost::SinglePassRangeConcept<bind_param_range>));
  typedef typename boost::range_value<bind_param_range>::type bind_param_type;

  BOOST_CONCEPT_ASSERT((BindParam<bind_param_type>));

  BOOST_CONCEPT_USAGE(Bind)
  {
    convertible_to<role_type>(traits::role (i));
    convertible_to<component_type>(traits::component (i));
    convertible_to<interface_type>(traits::interface_ (i));
    convertible_to<descriptor_type>(traits::descriptor (i));
    convertible_to<bool>(traits::has_descriptor (i));
    convertible_to<bool>(traits::has_interface (i));
    convertible_to<bind_param_range>(traits::bind_param (i));
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
