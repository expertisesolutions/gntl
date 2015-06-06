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

#ifndef GNTL_ARCHETYPE_PARSER_SWITCH_HPP
#define GNTL_ARCHETYPE_PARSER_SWITCH_HPP

#include <gntl/concept/parser/switch/switch.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Media, typename Context, typename SwitchPort, typename BindRule>
struct switch_ {};

} }

namespace concept { namespace parser {

template <typename Media, typename Context, typename SwitchPort, typename BindRule>
struct switch_traits<archetype::parser::switch_<Media, Context, SwitchPort, BindRule> >
{
  typedef archetype::parser::switch_<Media, Context, SwitchPort, BindRule> switch_type;

  typedef boost::mpl::true_ is_switch;
  struct identifier_type {};
  typedef boost::forward_iterator_archetype<Media> media_iterator;
  typedef boost::iterator_range<media_iterator> media_range;
  typedef boost::forward_iterator_archetype<SwitchPort> switch_port_iterator;
  typedef boost::iterator_range<switch_port_iterator> switch_port_range;
  typedef boost::forward_iterator_archetype<BindRule> bind_rule_iterator;
  typedef boost::iterator_range<bind_rule_iterator> bind_rule_range;
  typedef boost::forward_iterator_archetype<Context> context_iterator;
  typedef boost::iterator_range<context_iterator> context_range;
  typedef boost::forward_iterator_archetype<switch_type> switch_iterator;
  typedef boost::iterator_range<switch_iterator> switch_range;

  static identifier_type identifier(switch_type);
  static bool has_refer(switch_type);
  static identifier_type refer(switch_type);
  static bool has_default_component(switch_type);
  static identifier_type default_component(switch_type);
  static switch_port_range switch_port_all(switch_type);
  static bind_rule_range bind_rule_all(switch_type);
  static media_range media_all(switch_type);
  static context_range context_all(switch_type);
  static switch_range switch_all(switch_type);
};

} } }

#endif
