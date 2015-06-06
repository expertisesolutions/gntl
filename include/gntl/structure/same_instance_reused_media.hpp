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

#ifndef GNTL_STRUCTURE_SAME_INSTANCE_REUSED_MEDIA_HPP
#define GNTL_STRUCTURE_SAME_INSTANCE_REUSED_MEDIA_HPP

#include <gntl/concept/structure/media.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure {

template <typename Media, typename ReusedMedia>
struct same_instance_reused_media
{
  Media media;
  ReusedMedia reused_media;

  same_instance_reused_media(Media media, ReusedMedia reused_media)
    : media(media), reused_media(reused_media)
  {}
};

}

namespace concept { namespace structure {

template <typename Media, typename ReusedMedia>
struct media_traits<gntl::structure::same_instance_reused_media<Media, ReusedMedia> >
{
  typedef boost::mpl::true_ is_media;
  typedef structure::media_traits<typename unwrap_parameter<Media>::type> structure_media_traits;
  typedef structure::media_traits<typename unwrap_parameter<ReusedMedia>::type> reused_media_traits;

  typedef gntl::structure::same_instance_reused_media<Media, ReusedMedia> media_type;
  typedef typename structure_media_traits::identifier_type identifier_type;
  typedef typename reused_media_traits::source_type source_type;
  typedef typename structure_media_traits::instance_type instance_type;
  typedef typename reused_media_traits::type_type type_type;
  typedef typename reused_media_traits::interface_type interface_type;
  typedef typename reused_media_traits::string_type string_type;
  typedef typename reused_media_traits::integer_type integer_type;
  typedef typename reused_media_traits::descriptor_type descriptor_type;
  typedef typename reused_media_traits::descriptor_identifier_type descriptor_identifier_type;
  typedef typename reused_media_traits::presentation_type presentation_type;
  typedef typename reused_media_traits::presentation_range presentation_range;
  typedef typename structure_media_traits::area_range area_range;
  typedef typename structure_media_traits::property_type property_type;
  typedef typename structure_media_traits::property_range property_range;
  typedef typename reused_media_traits::player_type player_type;
  typedef typename reused_media_traits::explicit_duration_type explicit_duration_type;
  typedef typename reused_media_traits::region_type region_type;
  typedef typename reused_media_traits::freeze_type freeze_type;
  typedef typename reused_media_traits::focus_index_type focus_index_type;
  typedef typename reused_media_traits::color_type color_type;
  typedef typename reused_media_traits::width_type width_type;
  typedef typename reused_media_traits::transparency_type transparency_type;
  typedef typename reused_media_traits::transition_type transition_type;

  static bool is_same_instance_refer(media_type const&)
  {
    return true;
  }
  static identifier_type same_instance_referred(media_type const& m)
  {
    return structure_media_traits::identifier (m.reused_media);
  }
  static bool has_property(media_type const& m, interface_type name)
  {
    return reused_media_traits::has_property(m.reused_media, name);
  }
  static void start_set_property(media_type& m, interface_type name, string_type value)
  {
    reused_media_traits::start_set_property(m.reused_media, name, value);
  }
  static void start_set_property(media_type& m, interface_type name, integer_type value)
  {
    reused_media_traits::start_set_property(m.reused_media, name, value);
  }
  static void commit_set_property(media_type& m, interface_type name)
  {
    reused_media_traits::commit_set_property(m.reused_media, name);
  }
  static property_range property_all(media_type const& m)
  {
    return reused_media_traits::property_all(m.reused_media);
  }
  static property_type get_property(media_type const& m, interface_type const& name)
  {
    return reused_media_traits::get_property(m.reused_media, name);
  }
  static bool has_presentation(media_type const& m, descriptor_type descriptor)
  {
    return reused_media_traits::has_presentation(m.reused_media, descriptor);
  }
  static presentation_type prepare_presentation(media_type const& m, descriptor_type descriptor)
  {
    return reused_media_traits::prepare_presentation(m.reused_media, descriptor);
  }
  static presentation_type get_presentation(media_type const& m, descriptor_type descriptor)
  {
    return reused_media_traits::get_presentation(m.reused_media, descriptor);
  }
  static presentation_range presentation_all(media_type& m)
  {
    return reused_media_traits::presentation_all(m.reused_media);
  }
  static identifier_type identifier(media_type const& m)
  {
    return structure_media_traits::identifier(m.media);
  }
  static bool has_source(media_type const& m)
  {
    return reused_media_traits::has_source(m.reused_media);
  }
  static bool has_refer(media_type const& m)
  {
    if(reused_media_traits::has_refer(m.reused_media))
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("A media with a refer attribute cannot refer to a media with a refer"
                                 " attribute also"))
                               (typename error::component_identifier
                                <typename structure_media_traits::identifier_type>::type
                                (structure_media_traits::identifier(m.media)))
                               (typename error::refer<typename reused_media_traits::identifier_type>::type
                                (reused_media_traits::identifier(m.reused_media))));
    return false;
  }
  static bool has_instance(media_type const& m)
  {
    if(reused_media_traits::has_instance(m.reused_media))
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("A media with a refer attribute cannot refer to a media with a instance"
                                 " attribute"))
                               (typename error::component_identifier
                                <typename structure_media_traits::identifier_type>::type
                                (structure_media_traits::identifier(m.media)))
                               (typename error::refer<typename reused_media_traits::identifier_type>::type
                                (reused_media_traits::identifier(m.reused_media))));
    return false;
  }
  static bool has_type(media_type const& m)
  {
    return reused_media_traits::has_type(m.reused_media);
  }
  static source_type source(media_type const& m)
  {
    return reused_media_traits::source(m.reused_media);
  }
  static identifier_type refer(media_type const& m)
  {
    std::abort();
    throw -1;
  }
  static instance_type instance(media_type const& m)
  {
    std::abort();
    throw -1;
  }
  static type_type type(media_type const& m)
  {
    return reused_media_traits::type(m.reused_media);
  }
  static bool has_descriptor_identifier(media_type const& m)
  {
    return reused_media_traits::has_descriptor_identifier(m.reused_media);
  }
  static descriptor_identifier_type descriptor_identifier(media_type const& m)
  {
    return reused_media_traits::descriptor_identifier(m.reused_media);
  }
  static area_range area_all(media_type& m)
  {
    return reused_media_traits::area_all(m.reused_media);
  }
  static bool has_player (media_type const& m)
  {
    return reused_media_traits::has_player (m.reused_media);
  }
  static player_type player (media_type const& m)
  {
    return reused_media_traits::player (m.reused_media);
  }
  static bool has_explicit_duration (media_type const& m)
  {
    return reused_media_traits::has_explicit_duration (m.reused_media);
  }
  static boost::posix_time::time_duration explicit_duration (media_type const& m)
  {
    return reused_media_traits::explicit_duration (m.reused_media);
  }
  static bool has_region (media_type const& m)
  {
    return reused_media_traits::has_region (m.reused_media);
  }
  static region_type region (media_type const& m)
  {
    return reused_media_traits::region (m.reused_media);
  }
  static bool has_freeze (media_type const& m)
  {
    return reused_media_traits::has_freeze (m.reused_media);
  }
  static bool freeze (media_type const& m)
  {
    return reused_media_traits::freeze (m.reused_media);
  }
  static bool has_move_left (media_type const& m)
  {
    return reused_media_traits::has_move_left (m.reused_media);
  }
  static int move_left (media_type const& m)
  {
    return reused_media_traits::move_left (m.reused_media);
  }
  static bool has_move_right (media_type const& m)
  {
    return reused_media_traits::has_move_right (m.reused_media);
  }
  static int move_right (media_type const& m)
  {
    return reused_media_traits::move_right (m.reused_media);
  }
  static bool has_move_up (media_type const& m)
  {
    return reused_media_traits::has_move_up (m.reused_media);
  }
  static int move_up (media_type const& m)
  {
    return reused_media_traits::move_up (m.reused_media);
  }
  static bool has_move_down (media_type const& m)
  {
    return reused_media_traits::has_move_down (m.reused_media);
  }
  static int move_down (media_type const& m)
  {
    return reused_media_traits::move_down (m.reused_media);
  }
  static bool has_focus_index (media_type const& m)
  {
    return reused_media_traits::has_focus_index (m.reused_media);
  }
  static int focus_index (media_type const& m)
  {
    return reused_media_traits::focus_index (m.reused_media);
  }
  static bool has_focus_border_color (media_type const& m)
  {
    return reused_media_traits::has_focus_border_color (m.reused_media);
  }
  static color_type focus_border_color (media_type const& m)
  {
    return reused_media_traits::focus_border_color (m.reused_media);
  }
  static bool has_focus_border_width (media_type const& m)
  {
    return reused_media_traits::has_focus_border_width (m.reused_media);
  }
  static int focus_border_width (media_type const& m)
  {
    return reused_media_traits::focus_border_width (m.reused_media);
  }
  static bool has_focus_border_transparency (media_type const& m)
  {
    return reused_media_traits::has_focus_border_transparency (m.reused_media);
  }
  static transparency_type focus_border_transparency (media_type const& m)
  {
    return reused_media_traits::focus_border_transparency (m.reused_media);
  }
  static bool has_focus_source (media_type const& m)
  {
    return reused_media_traits::has_focus_source (m.reused_media);
  }
  static source_type focus_source (media_type const& m)
  {
    return reused_media_traits::focus_source (m.reused_media);
  }
  static bool has_focus_selection_source (media_type const& m)
  {
    return reused_media_traits::has_focus_selection_source (m.reused_media);
  }
  static source_type focus_selection_source (media_type const& m)
  {
    return reused_media_traits::focus_selection_source (m.reused_media);
  }
  static bool has_selection_border_color (media_type const& m)
  {
    return reused_media_traits::has_selection_border_color (m.reused_media);
  }
  static color_type selection_border_color (media_type const& m)
  {
    return reused_media_traits::selection_border_color (m.reused_media);
  }
  static bool has_transition_in (media_type const& m)
  {
    return reused_media_traits::has_transition_in (m.reused_media);
  }
  static transition_type transition_in (media_type const& m)
  {
    return reused_media_traits::transition_in (m.reused_media);
  }
  static bool has_transition_out (media_type const& m)
  {
    return reused_media_traits::has_transition_out (m.reused_media);
  }
  static transition_type transition_out (media_type const& m)
  {
    return reused_media_traits::transition_out (m.reused_media);
  }
};

} } }



#include <gntl/detail/pop_options.hpp>

#endif
