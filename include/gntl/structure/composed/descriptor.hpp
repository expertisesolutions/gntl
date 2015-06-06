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

#ifndef GNTL_STRUCTURE_COMPOSED_DESCRIPTOR_HPP
#define GNTL_STRUCTURE_COMPOSED_DESCRIPTOR_HPP

#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept/parser/descriptor/descriptor.hpp>

#include <boost/optional.hpp>
#include <boost/swap.hpp>

#include <iosfwd>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserDescriptor, typename DocumentURI>
struct descriptor
{
  descriptor()
  {
  }
  descriptor(ParserDescriptor d
             , DocumentURI document_uri = DocumentURI())
    : document_uri(document_uri)
    , region_document_uri(document_uri)
  {
    typedef typename boost::unwrap_reference<ParserDescriptor>::type parser_descriptor_type;
    typedef concept::parser::descriptor_traits<parser_descriptor_type> traits;
    identifier = traits::identifier(d);
    if(traits::has_player(d))
      player = traits::player(d);
    if(traits::has_explicit_duration(d))
      explicit_duration = traits::explicit_duration(d);
    if(traits::has_region(d))
      region = traits::region(d);
    if(traits::has_freeze(d))
      freeze = traits::freeze(d);
    if(traits::has_focus_index(d))
      focus_index = traits::focus_index(d);
    if(traits::has_move_left(d))
      move_left = traits::move_left(d);
    if(traits::has_move_right(d))
      move_right = traits::move_right(d);
    if(traits::has_move_up(d))
      move_up = traits::move_up(d);
    if(traits::has_move_down(d))
      move_down = traits::move_down(d);
    if(traits::has_focus_border_color(d))
      focus_border_color = traits::focus_border_color(d);
    if(traits::has_focus_border_width(d))
      focus_border_width = traits::focus_border_width(d);
    if(traits::has_focus_border_transparency(d))
      focus_border_transparency = traits::focus_border_transparency(d);
    if(traits::has_focus_source(d))
      focus_source = traits::focus_source(d);
    if(traits::has_focus_selection_source(d))
      focus_selection_source = traits::focus_selection_source(d);
    if(traits::has_selection_border_color(d))
      selection_border_color = traits::selection_border_color(d);
    if(traits::has_transition_in(d))
      transition_in = traits::transition_in(d);
    if(traits::has_transition_out(d))
      transition_out = traits::transition_out(d);
  }

  descriptor(descriptor high, descriptor const& low)
  {
    swap(high);
    if(identifier.empty())
      identifier = low.identifier;
    if(!player)
      player = low.player;
    if(!explicit_duration)
      explicit_duration = low.explicit_duration;
    if(!region)
    {
      region_document_uri = low.region_document_uri;
      region = low.region;
    }
    if(!freeze)
      freeze = low.freeze;
    if(!focus_index)
      focus_index = low.focus_index;
    if(!move_left)
      move_left = low.move_left;
    if(!move_right)
      move_right = low.move_right;
    if(!move_up)
      move_up = low.move_up;
    if(!move_down)
      move_down = low.move_down;
    if(!focus_border_color)
      focus_border_color = low.focus_border_color;
    if(!focus_border_width)
      focus_border_width = low.focus_border_width;
    if(!focus_border_transparency)
      focus_border_transparency = low.focus_border_transparency;
    if(!focus_source)
      focus_source = low.focus_source;
    if(!focus_selection_source)
      focus_selection_source = low.focus_selection_source;
    if(!selection_border_color)
      selection_border_color = low.selection_border_color;
    if(!transition_in)
      transition_in = low.transition_in;
    if(!transition_out)
      transition_out = low.transition_out;
  }
  
  typedef typename boost::unwrap_reference<ParserDescriptor>::type
    parser_descriptor_type;
  typedef concept::parser::descriptor_traits<parser_descriptor_type>
    parser_descriptor_traits;

  std::string identifier;
  DocumentURI document_uri;
  DocumentURI region_document_uri;
  boost::optional<typename parser_descriptor_traits::player_type> player;
  boost::optional<typename parser_descriptor_traits::explicit_duration_type> explicit_duration;
  boost::optional<typename parser_descriptor_traits::region_type> region;
  boost::optional<typename parser_descriptor_traits::freeze_type> freeze;
  boost::optional<typename parser_descriptor_traits::focus_index_type> focus_index;
  boost::optional<typename parser_descriptor_traits::focus_index_type> move_left;
  boost::optional<typename parser_descriptor_traits::focus_index_type> move_right;
  boost::optional<typename parser_descriptor_traits::focus_index_type> move_up;
  boost::optional<typename parser_descriptor_traits::focus_index_type> move_down;
  boost::optional<typename parser_descriptor_traits::color_type> focus_border_color;
  boost::optional<typename parser_descriptor_traits::width_type> focus_border_width;
  boost::optional<typename parser_descriptor_traits::transparency_type> focus_border_transparency;
  boost::optional<typename parser_descriptor_traits::source_type> focus_source;
  boost::optional<typename parser_descriptor_traits::source_type> focus_selection_source;
  boost::optional<typename parser_descriptor_traits::color_type> selection_border_color;
  boost::optional<typename parser_descriptor_traits::transition_type> transition_in;
  boost::optional<typename parser_descriptor_traits::transition_type> transition_out;

  void swap(descriptor& other)
  {
    boost::swap(identifier, other.identifier);
    boost::swap(document_uri, other.document_uri);
    boost::swap(region_document_uri, other.region_document_uri);
    boost::swap(player, other.player);
    boost::swap(explicit_duration, other.explicit_duration);
    boost::swap(region, other.region);
    boost::swap(freeze, other.freeze);
    boost::swap(focus_index, other.focus_index);
    boost::swap(move_left, other.move_left);
    boost::swap(move_right, other.move_right);
    boost::swap(move_up, other.move_up);
    boost::swap(move_down, other.move_down);
    boost::swap(focus_border_color, other.focus_border_color);
    boost::swap(focus_border_width, other.focus_border_width);
    boost::swap(focus_border_transparency, other.focus_border_transparency);
    boost::swap(focus_source, other.focus_source);
    boost::swap(focus_selection_source, other.focus_selection_source);
    boost::swap(selection_border_color, other.selection_border_color);
    boost::swap(transition_in, other.transition_in);
    boost::swap(transition_out, other.transition_out);
  }
};

template <typename ParserDescriptor, typename DocumentURI>
inline bool operator==(descriptor<ParserDescriptor, DocumentURI> const& lhs
                       , descriptor<ParserDescriptor, DocumentURI> const& rhs)
{
  return lhs.identifier == rhs.identifier
    && lhs.document_uri == rhs.document_uri
    && lhs.region_document_uri == rhs.region_document_uri
    && lhs.player == rhs.player
    && lhs.explicit_duration == rhs.explicit_duration
    && lhs.region == rhs.region
    && lhs.freeze == rhs.freeze
    && lhs.focus_index == rhs.focus_index
    && lhs.move_left == rhs.move_left
    && lhs.move_right == rhs.move_right
    && lhs.move_up == rhs.move_up
    && lhs.move_down == rhs.move_down
    && lhs.focus_border_color == rhs.focus_border_color
    && lhs.focus_border_width == rhs.focus_border_width
    //&& lhs.focus_border_transparency == rhs.focus_border_transparency
    && lhs.focus_source == rhs.focus_source
    && lhs.focus_selection_source == rhs.focus_selection_source
    && lhs.selection_border_color == rhs.selection_border_color
    // && lhs.transition_in == rhs.transition_in
    // && lhs.transition_out == rhs.transition_out
    ;
}

template <typename ParserDescriptor, typename DocumentURI>
inline bool operator!=(descriptor<ParserDescriptor, DocumentURI> const& lhs
                       , descriptor<ParserDescriptor, DocumentURI> const& rhs)
{
  return !(lhs == rhs);
}

template <typename ParserDescriptor, typename DocumentURI>
std::ostream& operator<<(std::ostream& os, descriptor<ParserDescriptor, DocumentURI> const& descriptor)
{
  os << "[identifier: " << descriptor.identifier
     << " document_uri: " << descriptor.document_uri
     << " region_document_uri: " << descriptor.region_document_uri
     << " player: " << descriptor.player
     << " explicit_duration: " << descriptor.explicit_duration
     << " region: " << descriptor.region
     << " freeze: " << descriptor.freeze
     << " focus_index: " << descriptor.focus_index
     << " move_left: " << descriptor.move_left
     << " move_right: " << descriptor.move_right
     << " move_up: " << descriptor.move_up
     << " move_down: " << descriptor.move_down
     << " focus_border_color: " << descriptor.focus_border_color
     << " focus_border_width: " << descriptor.focus_border_width
     << " focus_source: " << descriptor.focus_source
     << " focus_selection_source: " << descriptor.focus_selection_source
     << " selection_border_color: " << descriptor.selection_border_color
     << "]";
  return os;
}

} }

namespace concept { namespace structure {

template <typename ParserDescriptor, typename DocumentURI>
struct descriptor_traits<gntl::structure::composed::descriptor<ParserDescriptor, DocumentURI> >
{
  typedef boost::mpl::true_ is_descriptor;
  typedef gntl::structure::composed::descriptor<ParserDescriptor, DocumentURI> descriptor_type;
  typedef typename boost::unwrap_reference<ParserDescriptor>::type parser_descriptor_type;
  typedef concept::parser::descriptor_traits<parser_descriptor_type> parser_descriptor_traits;
  typedef std::string identifier_type;
  typedef DocumentURI document_uri_type;
  typedef typename parser_descriptor_traits::player_type player_type;
  typedef typename parser_descriptor_traits::explicit_duration_type explicit_duration_type;
  typedef typename parser_descriptor_traits::region_type region_type;
  typedef typename parser_descriptor_traits::freeze_type freeze_type;
  typedef typename parser_descriptor_traits::focus_index_type focus_index_type;
  typedef typename parser_descriptor_traits::color_type color_type;
  typedef typename parser_descriptor_traits::width_type width_type;
  typedef typename parser_descriptor_traits::transparency_type transparency_type;
  typedef typename parser_descriptor_traits::source_type source_type;
  typedef typename parser_descriptor_traits::transition_type transition_type;

  static identifier_type identifier(descriptor_type const& d)
  {
    return d.identifier;
  }
  static void set_region_document_uri(descriptor_type& d, document_uri_type document_uri)
  {
    d.region_document_uri = document_uri;
  }
  static document_uri_type region_document_uri(descriptor_type const& d)
  {
    return d.region_document_uri;
  }
  static bool has_player(descriptor_type const& d)
  {
    return !!d.player;
  }
  static void set_player(descriptor_type& d, player_type player)
  {
    d.player = player;
  }
  static player_type player(descriptor_type const& d)
  {
    return *d.player;
  }
  static bool has_explicit_duration(descriptor_type const& d)
  {
    return !!d.explicit_duration;
  }
  static void set_explicit_duration(descriptor_type& d, explicit_duration_type explicit_duration)
  {
    d.explicit_duration = explicit_duration;
  }
  static explicit_duration_type explicit_duration(descriptor_type const& d)
  {
    return *d.explicit_duration;
  }
  static bool has_region(descriptor_type const& d)
  {
    return !!d.region;
  }
  static void set_region(descriptor_type& d, region_type region)
  {
    d.region = region;
  }
  static region_type region(descriptor_type const& d)
  {
    return *d.region;
  }
  static bool has_freeze(descriptor_type const& d)
  {
    return !!d.freeze;
  } 
  static void set_freeze(descriptor_type& d, freeze_type freeze)
  {
    d.freeze = freeze;
  }
  static freeze_type freeze(descriptor_type const& d)
  {
    return *d.freeze;
  }
  static bool has_focus_index(descriptor_type const& d)
  {
    return !!d.focus_index;
  }
  static void set_focus_index(descriptor_type& d, focus_index_type focus_index)
  {
    d.focus_index = focus_index;
  }
  static focus_index_type focus_index(descriptor_type const& d)
  {
    return *d.focus_index;
  }
  static bool has_focus_border_color(descriptor_type const& d)
  {
    return !!d.focus_border_color;
  }
  static void set_focus_border_color(descriptor_type& d, color_type focus_border_color)
  {
    d.focus_border_color = focus_border_color;
  }
  static color_type focus_border_color(descriptor_type const& d)
  {
    return *d.focus_border_color;
  }
  static bool has_focus_border_width(descriptor_type const& d)
  {
    return !!d.focus_border_width;
  }
  static void set_focus_border_width(descriptor_type& d, width_type focus_border_width)
  {
    d.focus_border_width = focus_border_width;
  }
  static width_type focus_border_width(descriptor_type const& d)
  {
    return *d.focus_border_width;
  }
  static bool has_focus_border_transparency(descriptor_type const& d)
  {
    return !!d.focus_border_transparency;
  }
  static void set_focus_border_transparency(descriptor_type& d
                                            , transparency_type focus_border_transparency)
  {
    d.focus_border_transparency = focus_border_transparency;
  }
  static transparency_type focus_border_transparency(descriptor_type const& d)
  {
    return *d.focus_border_transparency;
  }
  static bool has_focus_source(descriptor_type const& d)
  {
    return !!d.focus_source;
  }
  static void set_focus_source(descriptor_type& d, source_type focus_source)
  {
    d.focus_source = focus_source;
  }
  static source_type focus_source(descriptor_type const& d)
  {
    return *d.focus_source;
  }
  static bool has_focus_selection_source(descriptor_type const& d)
  {
    return !!d.focus_selection_source;
  }
  static void set_focus_selection_source(descriptor_type& d, source_type focus_selection_source)
  {
    d.focus_selection_source = focus_selection_source;
  }
  static source_type focus_selection_source(descriptor_type const& d)
  {
    return *d.focus_selection_source;
  }
  static bool has_selection_border_color(descriptor_type const& d)
  {
    return !!d.selection_border_color;
  }
  static void set_selection_border_color(descriptor_type& d, color_type selection_border_color)
  {
    d.selection_border_color = selection_border_color;
  }
  static color_type selection_border_color(descriptor_type const& d)
  {
    return *d.selection_border_color;
  }
  static void set_transition_in(descriptor_type& d, transition_type transition_in)
  {
    d.transition_in = transition_in;
  }
  static bool has_transition_in(descriptor_type const& d)
  {
    return !!d.transition_in;
  }
  static transition_type transition_in(descriptor_type const& d)
  {
    return *d.transition_in;
  }
  static bool has_transition_out(descriptor_type const& d)
  {
    return !!d.transition_out;
  }
  static void set_transition_out(descriptor_type& d, transition_type transition_out)
  {
    d.transition_out = transition_out;
  }
  static transition_type transition_out(descriptor_type const& d)
  {
    return *d.transition_out;
  }
  static bool has_move_left(descriptor_type const& d)
  {
    return !!d.move_left; 
  }
  static void set_move_left(descriptor_type& d, focus_index_type focus_index)
  {
    d.move_left = focus_index;
  }
  static focus_index_type move_left(descriptor_type const& d)
  {
    return *d.move_left;
  }
  static bool has_move_right(descriptor_type const& d)
  {
    return !!d.move_right;
  }
  static void set_move_right(descriptor_type& d, focus_index_type focus_index)
  {
    d.move_right = focus_index;
  }
  static focus_index_type move_right(descriptor_type const& d)
  {
    return *d.move_right;
  }
  static bool has_move_up(descriptor_type const& d)
  {
    return !!d.move_up;
  }
  static void set_move_up(descriptor_type& d, focus_index_type focus_index)
  {
    d.move_up = focus_index;
  }
  static focus_index_type move_up(descriptor_type const& d)
  {
    return *d.move_up;
  }
  static bool has_move_down(descriptor_type const& d)
  {
    return !!d.move_down;
  }
  static focus_index_type move_down(descriptor_type const& d)
  {
    return *d.move_down;
  }
  static void set_move_down(descriptor_type& d, focus_index_type focus_index)
  {
    d.move_down = focus_index;
  }
  static descriptor_type compose(descriptor_type const& high, descriptor_type const& low)
  {
    return descriptor_type(high, low);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
