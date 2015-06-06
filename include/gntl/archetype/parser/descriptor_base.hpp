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

#ifndef GNTL_ARCHETYPE_PARSER_DESCRIPTOR_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_DESCRIPTOR_BASE_HPP

#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Descriptor, typename ImportBase>
struct descriptor_base
{
};

} }

namespace concept { namespace parser {

template <typename Descriptor, typename ImportBase>
struct descriptor_base_traits<archetype::parser::descriptor_base<Descriptor, ImportBase> >
{
  typedef archetype::parser::descriptor_base<Descriptor, ImportBase> descriptor_base;
  struct identifier_type {};
  typedef boost::mpl::true_ is_descriptor_base;
  typedef boost::input_iterator_archetype<ImportBase> import_base_iterator;
  typedef boost::iterator_range<import_base_iterator> import_base_range;
  typedef boost::input_iterator_archetype<Descriptor> descriptor_iterator;
  typedef boost::iterator_range<descriptor_iterator> descriptor_range;

  static bool has_identifier (descriptor_base);
  static identifier_type identifier (descriptor_base);
  static import_base_range import_base_all (descriptor_base);
  static descriptor_range descriptor_all (descriptor_base);
};

} } }

#endif
