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

#include <gntl/archetype/parser/descriptor.hpp>
#include <gntl/archetype/parser/descriptor_base.hpp>
#include <gntl/archetype/rgb_color.hpp>
#include <gntl/concept_check.hpp>

void compile_time_specific ()
{
  typedef gntl::archetype::parser::descriptor_base
    <gntl::archetype::parser::descriptor
     <gntl::archetype::parser::descriptor_param
      , gntl::archetype::rgb_color>, int > descriptor_base_type;
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::DescriptorBase<descriptor_base_type>));
}

int main() {}
