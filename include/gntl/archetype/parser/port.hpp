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

#ifndef GNTL_ARCHETYPE_PARSER_PORT_HPP
#define GNTL_ARCHETYPE_PARSER_PORT_HPP

#include <gntl/concept/parser/port/port.hpp>

namespace gntl { namespace archetype { namespace parser {

struct port
{
};

} }

namespace concept { namespace parser {

template <>
struct port_traits<archetype::parser::port>
{
    typedef boost::mpl::true_ is_port;
    struct identifier_type {};
    struct component_type {};
    struct interface_type {};

    typedef archetype::parser::port port;
    static identifier_type identifier (port);
    static component_type component (port);
    static interface_type interface_ (port);
    static bool has_interface (port);
};

} } }

#endif
