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

#ifndef GNTL_ARCHETYPE_PARSER_AREA_HPP
#define GNTL_ARCHETYPE_PARSER_AREA_HPP

#include <gntl/concept/parser/media/area.hpp>

namespace gntl { namespace archetype { namespace parser {

struct area
{
};

} }

namespace concept { namespace parser {

template <>
struct area_traits<archetype::parser::area>
{
    typedef boost::mpl::true_ is_area;
    struct identifier_type {};
    struct coordinate_type {};
    struct begin_type {};
    struct end_type {};
    struct text_type {};
    struct first_type {};
    struct last_type {};
    struct label_type {};
};

} } }

#endif
