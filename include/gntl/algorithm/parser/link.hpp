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

#ifndef GNTL_ALGORITHM_PARSER_LINK_HPP
#define GNTL_ALGORITHM_PARSER_LINK_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/parser/link/bind.hpp>
#include <gntl/concept/parser/link/link.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace parser { namespace link {

template <typename Role>
struct bind_role_predicate
{
  bind_role_predicate(Role role)
    : role(role)
  {}

  typedef bool result_type;
  
  template <typename Bind>
  result_type operator()(Bind b) const
  {
    GNTL_CONCEPT_ASSERT((concept::parser::Bind<Bind>));
    typedef concept::parser::bind_traits<Bind> bind_traits;
    return bind_traits::role(b) == role;
  }

  Role role;
};

template <typename Link>
struct get_xconnector
{
  typedef typename boost::unwrap_reference<Link>::type
    link_type;
  typedef concept::parser::link_traits<link_type>
    link_traits;

  typedef typename link_traits::xconnector_type result_type;
  result_type operator()(Link link) const
  {
    return link_traits::xconnector(link);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
