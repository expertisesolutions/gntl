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

#ifndef GNTL_CONCEPT_STRUCTURE_COMPONENT_LOCATION_HPP
#define GNTL_CONCEPT_STRUCTURE_COMPONENT_LOCATION_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct component_location_traits
{
  typedef boost::mpl::false_ is_component_location;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ComponentLocation
{
  typedef component_location_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_component_location::value, ==, true);
  typedef typename traits::identifier_type identifier_type;
  typedef typename traits::document_uri_type document_uri_type;
  
  BOOST_CONCEPT_USAGE (ComponentLocation)
  {
    convertible_to<identifier_type>(traits::identifier(const_i));
    // convertible_to<bool>(traits::has_parent_context(const_i));
    // convertible_to<identifier_type>(traits::parent_context(const_i));
    convertible_to<identifier_type>(traits::document_uri(const_i));
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }
  
  X const_i;
};
#endif
} } }

#include <gntl/detail/pop_options.hpp>

#endif
