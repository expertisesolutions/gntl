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

#ifndef GNTL_ARCHETYPE_PARSER_DESCRIPTOR_HPP
#define GNTL_ARCHETYPE_PARSER_DESCRIPTOR_HPP

#include <gntl/concept/parser/descriptor/descriptor.hpp>
#include <gntl/archetype/parser/descriptor_param.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename DescriptorParam, typename RGBColor>
struct descriptor
{
};

} }

namespace concept { namespace parser {

template <typename DescriptorParam, typename RGBColor>
struct descriptor_traits<archetype::parser::descriptor<DescriptorParam, RGBColor> >
{
    typedef archetype::parser::descriptor<DescriptorParam, RGBColor>
      descriptor_type;
    struct identifier_type {};
    typedef boost::mpl::true_ is_descriptor;
    struct player_type {};
    struct explicit_duration_type {};
    struct region_type {};
    struct freeze_type {};
    struct focus_index_type {};
    typedef RGBColor focus_border_color_type;
    struct focus_border_width_type {};
    struct focus_border_transparency_type {};
    struct focus_source_type {};
    struct focus_selection_source_type {};
    typedef RGBColor selection_border_color_type;
    struct transition_in_type {};
    struct transition_out_type {};
    typedef DescriptorParam descriptor_param_type;
    typedef boost::input_iterator_archetype<DescriptorParam> descriptor_param_iterator;  

  static identifier_type 
  identifier (descriptor_type);
  static bool has_player (descriptor_type);
  static player_type 
  player (descriptor_type);
  static bool has_explicit_duration (descriptor_type);
  static explicit_duration_type
  explicit_duration (descriptor_type);
  static bool has_region (descriptor_type);
  static region_type region (descriptor_type);
  static bool has_freeze (descriptor_type);
  static freeze_type 
  freeze (descriptor_type);
  static bool has_move_left (descriptor_type);
  static focus_index_type
  move_left (descriptor_type);
  static bool has_move_right (descriptor_type);
  static focus_index_type
  move_right (descriptor_type);
  static bool has_move_up (descriptor_type);
  static focus_index_type
  move_up (descriptor_type);
  static bool has_move_down (descriptor_type);
  static focus_index_type
  move_down (descriptor_type);
  static bool has_focus_index (descriptor_type);
  static focus_index_type 
  focus_index (descriptor_type);
  static bool has_focus_border_color (descriptor_type);
  static focus_border_color_type 
  focus_border_color (descriptor_type);
  static bool has_focus_border_width (descriptor_type);
  static focus_border_width_type
  focus_border_width (descriptor_type);
  static bool has_focus_border_transparency (descriptor_type);
  static focus_border_transparency_type 
  focus_border_transparency (descriptor_type);
  static bool has_focus_source (descriptor_type);
  static focus_source_type
  focus_source (descriptor_type);
  static bool has_focus_selection_source (descriptor_type);
  static focus_selection_source_type
  focus_selection_source (descriptor_type);
  static bool has_selection_border_color (descriptor_type);
  static selection_border_color_type
  selection_border_color (descriptor_type);
  static bool has_transition_in (descriptor_type);
  static transition_in_type
  transition_in (descriptor_type);
  static bool has_transition_out (descriptor_type);
  static transition_out_type
  transition_out (descriptor_type);
};

} } }

#endif
