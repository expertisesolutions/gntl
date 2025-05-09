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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SELECT_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SELECT_IPP

#include <gntl/algorithm/structure/media/select.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/algorithm/structure/document.hpp>
#include <gntl/algorithm/structure/media/calculate_focused_border.hpp>
#include <gntl/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Media, typename Presentation, typename Document
          , typename Key, typename Descriptor, typename...Args>
void focus_select_with_descriptor(Media m, Presentation p, Document d
                                  , Key key, Descriptor descriptor, Args&&... args)
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef typename boost::unwrap_reference<Descriptor>::type descriptor_type;
  typedef typename boost::unwrap_reference<Presentation>::type presentation_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  typedef concept::structure::presentation_traits<presentation_type> presentation_traits;

  GNTL_DEBUG_LOG("key " << key << std::endl);
  typedef typename descriptor_traits::focus_index_type focus_index_type;
  focus_index_type focus_index;
  if(key == "CURSOR_UP" && descriptor_traits::has_move_up(descriptor))
    focus_index = descriptor_traits::move_up(descriptor);
  else if(key == "CURSOR_DOWN" && descriptor_traits::has_move_down(descriptor))
    focus_index = descriptor_traits::move_down(descriptor);
  else if(key == "CURSOR_LEFT" && descriptor_traits::has_move_left(descriptor))
    focus_index = descriptor_traits::move_left(descriptor);
  else if(key == "CURSOR_RIGHT" && descriptor_traits::has_move_right(descriptor))
    focus_index = descriptor_traits::move_right(descriptor);
  else if(key == "ENTER")
  {
    document_traits::register_event (d
                                     , concept::identifier (m)
                                     , boost::none
                                     , gntl::transition_enum::starts
                                     , gntl::event_enum::selection);
    GNTL_DEBUG_LOG("ENTER was pressed on " << concept::identifier (m) << std::endl)

    if(presentation_traits::wants_keys(p))
    {
    if(document_traits::has_global_properties_media(d))
    {
      document_traits::start_set_property(d, "service.currentKeyMaster", concept::identifier(m));
      typename document_traits::component_identifier interface_("service.currentKeyMaster");
      GNTL_DEBUG_LOG("Registering attribution event to media: "
                     << document_traits::global_properties_media(d)
                     << " with interface: " << interface_ << std::endl)
      document_traits::register_event (d
                                       , document_traits::global_properties_media(d)
                                       , interface_
                                       , gntl::transition_enum::starts
                                       , gntl::event_enum::attribution);
    }
    else
    {
      document_traits::start_set_property(d, "service.currentKeyMaster", concept::identifier(m));
      document_traits::commit_set_property(d, "service.currentKeyMaster");
    }
    }
    return;
  }
  else if(key == "BACK")
  {
    document_traits::register_event (d, concept::identifier (m)
                                     , boost::none
                                     , gntl::transition_enum::stops
                                     , gntl::event_enum::selection);
    GNTL_DEBUG_LOG("BACK was pressed" << std::endl)
    return;
  }
  else
  {
    GNTL_DEBUG_LOG("Not a navigational key" << std::endl)
    return;
  }

  GNTL_DEBUG_LOG("should move focus to focusIndex " << focus_index << std::endl)

  typedef typename document_traits::focus_index_presentation_lookupable presentation_lookupable;
  presentation_lookupable lookupable = document_traits::focus_index_presentation_lookup(d);
  typedef concept::lookupable_traits<presentation_lookupable> lookupable_traits;
  typedef typename lookupable_traits::result_type lookup_result;
  lookup_result r = lookupable_traits::lookup(lookupable, focus_index);

  if(r != lookupable_traits::not_found(lookupable))
  {
    typedef typename lookupable_traits::value_type lookup_value_type;
    lookup_value_type v = *r;
    typedef typename lookup_value_type::const_iterator iterator;
    for(iterator first = v.begin (), last = v.end (); first != last; ++first)
    {
      typedef typename lookup_value_type::value_type value_type;
      typedef typename value_type::second_type ref_presentation_type;
      typedef typename gntl::unwrap_parameter<ref_presentation_type>::type
        presentation_type;
      typedef gntl::concept::structure::presentation_traits
        <presentation_type> presentation_traits;
      if(presentation_traits::is_occurring(first->second))
      {
        if(!presentation_traits::is_focused(first->second))
        {
          typedef typename unwrap_parameter<value_type>::type pair_type;
          typedef typename pair_type::second_type presentation_pair_type;
          typedef typename unwrap_parameter<presentation_pair_type>::type presentation_type;
          typedef concept::structure::presentation_traits<presentation_type>
            presentation_traits;
          typedef typename presentation_traits::descriptor_type descriptor_type;
          typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
          typedef typename descriptor_traits::width_type width_type;
          typedef typename descriptor_traits::color_type color_type;
          descriptor_type descriptor = presentation_traits::current_descriptor
            (first->second);
          std::pair<width_type, color_type>
            c = media::calculate_focused_border (first->second, descriptor
                                                 , presentation_traits::is_selected(p));

          presentation_traits::add_border (first->second, c.first, c.second, args...);
          presentation_traits::focused(first->second);
          structure::document::set_focus(d, first->first, descriptor);

          presentation_traits::reset_focus(p);
          presentation_traits::remove_border(p, args...);
        }
        break;
      }
    }
  }
  
}

template <typename Media, typename Document, typename Key, typename...Args>
void focus_select(Media m, Document d, Key key, Args&&... args)
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef typename media_traits::descriptor_type descriptor_type;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  GNTL_DEBUG_LOG("selecting " << concept::identifier(m) << std::endl)

  typedef typename media_traits::presentation_range presentation_range;

  presentation_range presentations = concept::presentation_all(m);
  typedef typename boost::range_value<presentation_range>::type presentation_type;
  typename boost::range_iterator<presentation_range>::type
    first = boost::begin(presentations)
    , last = boost::end(presentations);
  while(first != last)
  {
    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
    if(presentation_traits::is_focused(*first))
    {
      descriptor_type descriptor = presentation_traits::current_descriptor(*first);
      focus_select_with_descriptor(m, *first, d, key, descriptor, args...);
      break;
    }
    ++first;
  }
}

template <typename Media, typename Document, typename Key>
focus_select_functor::result_type focus_select_functor::operator()
  (Media m, Document d, Key key) const
{
  focus_select(m, d, key);
}

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
