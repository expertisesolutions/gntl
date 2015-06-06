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

#ifndef GNTL_STRUCTURE_COMPOSED_COMPOUND_STATEMENT_HPP
#define GNTL_STRUCTURE_COMPOSED_COMPOUND_STATEMENT_HPP

#include <gntl/concept/structure/condition/compound_statement.hpp>
#include <gntl/concept/structure/condition/condition.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

//template
struct compound_statement
{
};

} }

namespace concept { namespace structure {

template <>
struct compound_statement_traits
  <gntl::structure::composed::compound_statement>
{
  typedef boost::mpl::true_ is_compound_statement;
};

template <>
struct condition_traits
  <gntl::structure::composed::compound_statement>
{
  typedef boost::mpl::true_ is_condition;
  typedef compound_statement_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
