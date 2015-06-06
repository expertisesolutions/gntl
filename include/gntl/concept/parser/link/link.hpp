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

#ifndef GNTL_CONCEPT_PARSER_LINK_LINK_HPP
#define GNTL_CONCEPT_PARSER_LINK_LINK_HPP

#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/concept/parser/link/link_param.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct link_traits
{
  typedef boost::mpl::false_ is_link;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Link
{
  typedef link_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_link::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::xconnector_type xconnector_type;
  typedef typename traits::bind_range bind_range;
  typedef typename traits::link_param_range link_param_range;

  typedef typename boost::range_value<bind_range>::type bind_type;
  typedef typename boost::range_value<link_param_range>::type link_param_type;

  BOOST_CONCEPT_ASSERT((Bind<bind_type>));
  BOOST_CONCEPT_ASSERT((LinkParam<link_param_type>));

  BOOST_CONCEPT_USAGE (Link)
  {
    convertible_to<identifier_type>(traits::identifier (i));
    convertible_to<bool>(traits::has_identifier (i));
    convertible_to<xconnector_type>(traits::xconnector (i));
    convertible_to<bind_range>(traits::bind (i));
    convertible_to<link_param_range>(traits::link_param (i));
  }

  template <typename To, typename From>
  void convertible_to (From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
