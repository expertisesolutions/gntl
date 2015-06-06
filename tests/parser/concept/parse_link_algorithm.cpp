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

#ifndef GNTL_DISABLE_CONCEPTS
#include <gntl/concept/parser/link/link.hpp>
#include <gntl/archetype/parser/link.hpp>
#include <gntl/archetype/parser/bind.hpp>
#include <gntl/archetype/parser/bind_param.hpp>
#include <gntl/archetype/parser/link_param.hpp>

#include <boost/concept/assert.hpp>

namespace archetype = gntl::archetype;
namespace concept = gntl::concept;

void compile_time_specific ()
{
  BOOST_CONCEPT_ASSERT ((concept::parser::Link
                         <archetype::parser::link
                          <archetype::parser::bind<archetype::parser::bind_param>
                           , archetype::parser::link_param> >));
}

#endif

int main() {}
