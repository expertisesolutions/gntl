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

#ifndef GNTL_ARCHETYPE_STRUCTURE_PRESENTATION_HPP
#define GNTL_ARCHETYPE_STRUCTURE_PRESENTATION_HPP

#include <gntl/concept/structure/presentation.hpp>

#include <boost/mpl/vector.hpp>

namespace gntl { namespace archetype { namespace structure {

struct presentation {};

} }

namespace concept { namespace structure {

template <>
struct presentation_traits<archetype::structure::presentation>
{
  typedef boost::mpl::true_ is_presentation;
  typedef archetype::structure::presentation presentation;
  typedef boost::mpl::vector1<void(presentation)> start_function_overloads;
  struct component_identifier {};
  struct time_duration {};
  struct color_type {};
  struct descriptor_type {};

  static bool is_occurring(presentation const&);
  static bool is_paused(presentation const&);
  static bool is_sleeping(presentation const&);
  static bool is_focused(presentation const&);
  static bool is_selected(presentation const&);
  static descriptor_type current_descriptor(presentation const&);
  static void start(presentation const&);
  static void stop(presentation const&);
  static void pause(presentation const&);
  static void abort(presentation const&);
  static void resume(presentation const&);
  static void focused(presentation const&);
  static void selected(presentation const&);
  static void reset_focus(presentation const&);
  static void reset_selection(presentation const&);
  static void add_border(presentation const&, int, color_type);
  static void remove_border(presentation const&);
  static void listen_time(presentation const&, component_identifier, component_identifier, time_duration, gntl::transition_type);
  static void listen_npt(presentation const&, component_identifier, component_identifier, int, gntl::transition_type);
  static void listen_frame(presentation const&, component_identifier, component_identifier, std::size_t, gntl::transition_type);
};

} } }

#endif
