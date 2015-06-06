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

#ifndef GNTL_ARCHETYPE_PARSER_REGION_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_REGION_BASE_HPP

#include <gntl/concept/parser/region/region_base.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Region, typename ImportBase>
struct region_base
{
};

} }

namespace concept { namespace parser {

template <typename Region, typename ImportBase>
struct region_base_traits<archetype::parser::region_base<Region, ImportBase> >
{
  typedef archetype::parser::region_base<Region, ImportBase> region_base;
  typedef boost::mpl::true_ is_region_base;
  struct identifier_type {};
  typedef boost::input_iterator_archetype<ImportBase> import_base_iterator;
  typedef boost::iterator_range<import_base_iterator> import_base_range;
  typedef boost::input_iterator_archetype<Region> region_iterator;
  typedef boost::iterator_range<region_iterator> region_range;

  static identifier_type identifier (region_base);
  static bool has_identifier (region_base);
  static import_base_range import_base_all (region_base);
  static region_range region_all (region_base);
};

} } }

#endif
