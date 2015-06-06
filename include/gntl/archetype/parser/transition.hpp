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

#ifndef GNTL_ARCHETYPE_PARSER_TRANSITION_HPP
#define GNTL_ARCHETYPE_PARSER_TRANSITION_HPP

#include <gntl/concept/parser/transition/transition.hpp>

namespace gntl { namespace archetype { namespace parser {

struct transition
{
};

} }

namespace concept { namespace parser {

template <>
struct transition_traits<archetype::parser::transition>
{
  typedef boost::mpl::true_ is_transition;
  typedef archetype::parser::transition transition;

  struct identifier_type {};
  struct type_type {};
  struct duration_type {};
  struct start_progress_type {};
  struct end_progress_type {};
  struct direction_type {};
  struct fade_color_type {};
  struct horizontal_repeat_type {};
  struct vertical_repeat_type {};
  struct border_width_type {};
  struct border_color_type {};
  
  static identifier_type identifier (transition);
  static type_type type (transition);
  static duration_type duration (transition);
  static bool has_duration (transition);
  static start_progress_type start_progress (transition);
  static bool has_start_progress (transition);
  static end_progress_type end_progress (transition);
  static bool has_end_progress (transition);
  static direction_type direction (transition);
  static bool has_direction (transition);
  static fade_color_type fade_color (transition);
  static bool has_fade_color (transition);
  static horizontal_repeat_type horizontal_repeat (transition);
  static bool has_horizontal_repeat (transition);
  static vertical_repeat_type vertical_repeat (transition);
  static bool has_vertical_repeat (transition);
  static border_width_type border_width (transition);
  static bool has_border_width (transition);
  static border_color_type border_color (transition);
  static bool has_border_color (transition);
};

} } }

#endif
