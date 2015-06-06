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

#ifndef GNTL_ARCHETYPE_PARSER_MEDIA_HPP
#define GNTL_ARCHETYPE_PARSER_MEDIA_HPP

#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept_check.hpp>

#include <boost/range/iterator_range.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename Area, typename Property>
struct media
{
};

} }

namespace concept { namespace parser {

template <typename Area, typename Property>
struct media_traits<archetype::parser::media<Area, Property> >
{
    typedef boost::mpl::true_ is_media;
    typedef archetype::parser::media<Area, Property> media;
    struct identifier_type
    {
      bool operator==(identifier_type) const;
    };
    struct source_type {};
    struct instance_type {};
    struct type_type {};
    struct descriptor_type {};
    struct player_type {};
    struct explicit_duration_type {};
    struct region_type {};
    struct freeze_type {};
    struct focus_index_type {};
    struct color_type {};
    struct width_type {};
    struct transparency_type {};
    struct transition_type {};
    typedef boost::input_iterator_archetype<Area> area_iterator;
    typedef boost::iterator_range<area_iterator> area_range;
    typedef boost::input_iterator_archetype<Property> property_iterator;
    typedef boost::iterator_range<property_iterator> property_range;

    static identifier_type identifier (media);
    static bool has_source (media);
    static source_type source (media);
    static bool has_refer (media);
    static identifier_type refer (media);
    static bool has_instance (media);
    static instance_type instance (media);
    static bool has_type (media);
    static type_type type (media);
    static bool has_descriptor (media);
    static descriptor_type descriptor (media);
    static area_range area_all(media);
    static property_range property_all(media);
    static player_type player(media);
    static bool has_explicit_duration(media);
    static explicit_duration_type explicit_duration(media);
    static bool has_region(media);
    static region_type region(media);
    static bool has_freeze(media);
    static freeze_type freeze(media);
    static bool has_move_left(media);
    static focus_index_type move_left(media);
    static bool has_move_right(media);
    static focus_index_type move_right(media);
    static bool has_move_up(media);
    static focus_index_type move_up(media);
    static bool has_move_down(media);
    static focus_index_type move_down(media);
    static bool has_focus_index(media);
    static focus_index_type focus_index(media);
    static bool has_focus_border_color(media);
    static color_type focus_border_color(media);
    static bool has_focus_border_width(media);
    static width_type focus_border_width(media);
    static bool has_focus_border_transparency(media);
    static transparency_type focus_border_transparency(media);
    static bool has_focus_source(media);
    static source_type focus_source(media);
    static bool has_focus_selection_source(media);
    static source_type focus_selection_source(media);
    static bool has_selection_border_color(media);
    static color_type selection_border_color(media);
    static bool has_transition_in(media);
    static transition_type transition_in(media);
    static bool has_transition_out(media);
    static transition_type transition_out(media);
};

} } }

#endif
