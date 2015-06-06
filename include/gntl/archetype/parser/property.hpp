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

#ifndef GNTL_ARCHETYPE_PARSER_PROPERTY_HPP
#define GNTL_ARCHETYPE_PARSER_PROPERTY_HPP

#include <gntl/concept/parser/property/property.hpp>

namespace gntl { namespace archetype { namespace parser {

struct property
{
    struct name_type {};
    struct value_type {};
};

} }

namespace concept { namespace parser {

template <>
struct property_traits<archetype::parser::property>
{
  typedef boost::mpl::true_ is_property;
  typedef archetype::parser::property property;
  typedef property::name_type name_type;
  typedef property::value_type value_type;

  static name_type name (property);
  static value_type value (property);
  static bool has_value (property);
};

} } } 

#endif
