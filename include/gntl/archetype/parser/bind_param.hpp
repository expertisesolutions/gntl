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

#ifndef GNTL_ARCHETYPE_PARSER_BIND_PARAM_HPP
#define GNTL_ARCHETYPE_PARSER_BIND_PARAM_HPP

namespace gntl {
namespace archetype { namespace parser {

struct bind_param
{
};

} }

namespace concept { namespace parser {

template <>
struct bind_param_traits<archetype::parser::bind_param>
{
  typedef archetype::parser::bind_param bind_param;
  typedef boost::mpl::true_ is_bind_param;
  struct name_type {};
  struct value_type {};

  static name_type name(bind_param b);
  static value_type value(bind_param b);
};

} } } 

#endif
