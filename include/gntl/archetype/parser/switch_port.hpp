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

#ifndef GNTL_ARCHETYPE_PARSER_SWITCH_PORT_HPP
#define GNTL_ARCHETYPE_PARSER_SWITCH_PORT_HPP

#include <gntl/concept/parser/switch/switch_port.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

struct switch_port {};

} }

namespace concept { namespace parser {

template <>
struct switch_port_traits<archetype::parser::switch_port>
{
  typedef archetype::parser::switch_port switch_port;
  typedef boost::mpl::true_ is_switch_port;
  struct identifier_type {};

  static identifier_type identifier(switch_port);
};

} } }


#endif
