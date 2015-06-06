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

#ifndef GNTL_ARCHETYPE_PARSER_BIND_HPP
#define GNTL_ARCHETYPE_PARSER_BIND_HPP

#include <boost/mpl/bool.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename BindParam>
struct bind
{
};

} } 

namespace concept { namespace parser {

template <typename BindParam>
struct bind_traits<archetype::parser::bind<BindParam> >
{
  typedef archetype::parser::bind<BindParam> bind;
  typedef boost::mpl::true_ is_bind;
  struct role_type {};
  struct component_type {};
  struct interface_type {};
  struct descriptor_type {};
  typedef boost::iterator_range
    <boost::input_iterator_archetype<BindParam> > bind_param_range;

  static role_type role(bind);
  static component_type component(bind);
  static interface_type interface_(bind);
  static descriptor_type descriptor(bind);
  static bool has_interface(bind);
  static bool has_descriptor(bind);
  static bind_param_range bind_param (bind);
};

} } }

#endif
