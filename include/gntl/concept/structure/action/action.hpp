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

#ifndef GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_HPP
#define GNTL_CONCEPT_STRUCTURE_ACTION_ACTION_HPP

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace gntl { namespace concept { namespace structure {

struct simple_action_tag {};
struct compound_action_tag {};

template <typename T>
struct action_traits
{
  typedef boost::mpl::false_ is_action;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Action
{
  typedef action_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_action::value, ==, true);
  typedef typename traits::category_tag category_tag;
};
#endif
} } }

#endif
