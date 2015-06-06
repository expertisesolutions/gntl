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

#ifndef GNTL_ARCHETYPE_PARSER_IMPORT_DOCUMENT_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_IMPORT_DOCUMENT_BASE_HPP

#include <gntl/concept/parser/import/has_import_ncl.hpp>
#include <gntl/archetype/parser/has_import_ncl.hpp>

#include <boost/concept_check.hpp>
#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename ImportNCL>
struct import_document_base : has_import_ncl<ImportNCL>
{
};

} }

namespace concept { namespace parser {

template <typename ImportNCL>
struct has_import_ncl_traits<archetype::parser::import_document_base
                             <ImportNCL> >
  : has_import_ncl_traits<archetype::parser::has_import_ncl<ImportNCL> >
{
};

} } }

#endif
