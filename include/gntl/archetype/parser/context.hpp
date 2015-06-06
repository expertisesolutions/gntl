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

#ifndef GNTL_ARCHETYPE_PARSER_CONTEXT_HPP
#define GNTL_ARCHETYPE_PARSER_CONTEXT_HPP

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/archetype/parser/switch.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Media, typename Property, typename Port, typename Link, typename SwitchPort, typename BindRule>
struct context
{
};

} }

namespace concept { namespace parser {

template <typename Media, typename Property, typename Port, typename Link, typename SwitchPort, typename BindRule>
struct context_traits<archetype::parser::context<Media, Property, Port, Link, SwitchPort, BindRule> >
{
  typedef archetype::parser::context<Media,Property,Port,Link,SwitchPort,BindRule>
    context_type;
  struct identifier_type {};
  typedef boost::input_iterator_archetype<context_type> context_iterator;
  typedef boost::iterator_range<context_iterator> context_range;
  typedef boost::input_iterator_archetype<Media> media_iterator;
  typedef boost::iterator_range<media_iterator> media_range;
  typedef boost::input_iterator_archetype<Property> property_iterator;
  typedef boost::iterator_range<property_iterator> property_range;
  typedef boost::input_iterator_archetype<Port> port_iterator;
  typedef boost::iterator_range<port_iterator> port_range;
  typedef boost::input_iterator_archetype<Link> link_iterator;
  typedef boost::iterator_range<link_iterator> link_range;
  typedef archetype::parser::switch_<Media,context_type,SwitchPort,BindRule> switch_type;
  typedef boost::forward_iterator_archetype<switch_type> switch_iterator;
  typedef boost::iterator_range<switch_iterator> switch_range;

  static identifier_type identifier(context_type);
  static identifier_type refer(context_type);
  static bool has_refer(context_type);
  static context_range context_all(context_type);
  static media_range media_all(context_type);
  static property_range property_all(context_type);
  static port_range port_all(context_type);
  static link_range link_all(context_type);
  static switch_range switch_all(context_type);
};

} } }

#endif
