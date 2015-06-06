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

#ifndef GNTL_ARCHETYPE_PARSER_IMPORT_NCL_HPP
#define GNTL_ARCHETYPE_PARSER_IMPORT_NCL_HPP

#include <gntl/concept/parser/import/import_ncl.hpp>

namespace gntl { namespace archetype { namespace parser {

struct import_ncl
{
};

} }

namespace concept { namespace parser {

template <>
struct import_ncl_traits<archetype::parser::import_ncl>
{
  typedef archetype::parser::import_ncl import_ncl;
  struct document_uri_type {};
  struct alias_type {};
  typedef boost::mpl::true_ is_import_ncl;

  static document_uri_type document_uri(import_ncl);
  static alias_type alias(import_ncl);
};

} } }

#endif
