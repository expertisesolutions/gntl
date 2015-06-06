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

#ifndef GNTL_ARCHETYPE_PARSER_REGION_HPP
#define GNTL_ARCHETYPE_PARSER_REGION_HPP

#include <gntl/concept/parser/region/region.hpp>

#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Coordinate>
struct region
{
};

} }

namespace concept { namespace parser {

template <typename Coordinate>
struct region_traits<archetype::parser::region<Coordinate> >
{
    typedef archetype::parser::region<Coordinate> region;
    typedef boost::mpl::true_ is_region;
    struct identifier_type {};
    typedef Coordinate coordinate_type;
    struct title_type {};
    struct zindex_type {};

    static bool has_identifier (region);
    static identifier_type identifier (region);
    static bool has_title (region);
    static bool has_left (region);
    static bool has_right (region);
    static bool has_top (region);
    static bool has_bottom (region);
    static bool has_height (region);
    static bool has_width (region);
    static bool has_zindex (region);
    static coordinate_type left (region);
    static coordinate_type right (region);
    static coordinate_type top (region);
    static coordinate_type bottom (region);
    static coordinate_type height (region);
    static coordinate_type width (region);
    static title_type title (region);
    static zindex_type zindex (region);
};

} } }

#endif
