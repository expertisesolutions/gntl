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

#ifndef GNTL_STRUCTURE_COMPOSED_DETAIL_ROLE_PREDICATE_HPP
#define GNTL_STRUCTURE_COMPOSED_DETAIL_ROLE_PREDICATE_HPP

#include <gntl/concept/parser/link/link.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed { namespace composed_detail {

template <typename Role>
struct role_predicate
{
  role_predicate(Role role)
    : role(role) {}
  typedef bool result_type;
  template <typename Bind>
  result_type operator()(Bind b) const
  {
    typedef concept::parser::bind_traits<Bind> bind_traits;
    return bind_traits::role(b) == role;
  }

  Role role;
};

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
