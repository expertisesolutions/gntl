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

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_START_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_START_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/document/register_event.hpp>
#include <gntl/algorithm/structure/media/start_action_traits.hpp>
#include <gntl/algorithm/structure/media/calculate_focused_border.hpp>
#include <gntl/concept/parser/media/area.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/invalid_ncl_error.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, GNTL_MAX_ARGS               \
  , "gntl/algorithm/structure/media/start_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Media, typename Location, typename OptionalInterface
          , typename Descriptor, typename Dimensions, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_action_traits::start(Media m, Location l, OptionalInterface interface_
                                , Descriptor descriptor
                                , Dimensions dim
                                , Document document
                                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef typename unwrap_parameter<Descriptor>::type descriptor_type;

  GNTL_CONCEPT_ASSERT((concept::structure::Descriptor<descriptor_type>));
  GNTL_CONCEPT_ASSERT((concept::structure::Media<media_type>));
  GNTL_CONCEPT_ASSERT((concept::structure::Document<document_type>));

  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;

  typedef typename media_traits::presentation_type presentation_type;
  typedef concept::structure::presentation_traits<presentation_type> presentation_traits;

  presentation_type presentation = concept::prepare_presentation(m, descriptor);

  {
    typedef typename media_traits::area_range area_range;
    area_range areas = concept::area_all(m);
    for(typename boost::range_iterator<area_range>::type
          first = boost::begin(areas)
          , last = boost::end(areas)
          ;first != last;++first)
    {
      typedef typename boost::range_value<area_range>::type area_type;
      typedef concept::parser::area_traits<area_type> area_traits;
      GNTL_DEBUG_LOG("iterating over area " << area_traits::identifier(*first) << std::endl)
      if(area_traits::has_begin(*first))
      {
        presentation_traits::area_time_begin(presentation
                                             , area_traits::identifier(*first)
                                             , area_traits::begin(*first));
      }
      else if(area_traits::has_first(*first))
      {
        presentation_traits::area_frame_begin(presentation
                                              , area_traits::identifier(*first)
                                              , area_traits::first(*first));
      }
      if(area_traits::has_end(*first))
      {
        presentation_traits::area_time_end(presentation
                                           , area_traits::identifier(*first)
                                           , area_traits::end(*first));
      }
      else if(area_traits::has_last(*first))
      {
        presentation_traits::area_frame_end(presentation
                                            , area_traits::identifier(*first)
                                            , area_traits::last(*first));
      }
    }
  }

  {
    typedef typename media_traits::property_range property_range;
    property_range properties = concept::property_all(m);
    for(typename boost::range_iterator<property_range>::type
          first = boost::begin(properties)
          , last = boost::end(properties); first != last; ++first)
    {
      typedef typename boost::range_value<property_range>::type property_type;
      typedef concept::structure::property_traits<property_type> property_traits;
      if(presentation_traits::start_set_property(presentation, property_traits::name(*first)
                                                 , property_traits::value_as_string(*first)))
        presentation_traits::commit_set_property(presentation, property_traits::name(*first));
    }
  }

  if(descriptor_traits::has_focus_index(descriptor))
  {
    GNTL_DEBUG_LOG("Has focus index" << std::endl)
    if(!document_traits::has_focus(document))
    {
      GNTL_DEBUG_LOG("No media focused. Should focus this presentation" << std::endl)
      structure::document::set_focus(document, m, descriptor);
      presentation_traits::focused(presentation);
    }
    else if(descriptor_traits::focus_index(descriptor)
            == document_traits::focus_index(document)
            && !document_traits::is_focus_bound(document)
            )
    {
      GNTL_DEBUG_LOG("No media focused. Should focus this presentation" << std::endl)
      structure::document::set_focus(document, m, descriptor);
      presentation_traits::focused(presentation);
    }
  }

  if(presentation_traits::is_focused(presentation))
  {
    typedef typename descriptor_traits::width_type width_type;
    typedef typename descriptor_traits::color_type color_type;
    std::pair<width_type, color_type>
      r = media::calculate_focused_border (presentation, descriptor, false);
    if(r.first)
      presentation_traits::add_border(presentation, r.first, r.second);
  }

  // Media can't be selected since we're starting it now. But
  // it can be focused if it has a focus_index and no media
  // is focused right now
  boost::optional<typename media_traits::source_type> source;
  if(presentation_traits::is_focused(presentation)
     && descriptor_traits::has_focus_source (descriptor))
  {
    source = descriptor_traits::focus_source (descriptor);      
  }
  if(!source && concept::has_source(m))
    source = concept::source(m);
  else if(!source)
    GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                           , (typename error::reason<const char*>::type("No src attribute in media"))
                             (typename error::component_identifier<typename media_traits::identifier_type>::type
                              (concept::identifier(m))));

  if(descriptor_traits::has_explicit_duration(descriptor))
  {
    presentation_traits::explicit_duration
      (presentation, descriptor_traits::explicit_duration(descriptor));
  }

  presentation_traits::start
    (presentation, *source, interface_, dim
     , l
     BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));

  // if(d && descriptor_traits::has_focus_index(*d))
  // {
  //   GNTL_DEBUG_LOG("descriptor has focus index: "
  //                  << descriptor_traits::focus_index(*d) << std::endl)
  //   if(!document_traits::has_property(document, "service.currentFocus"))
  //   {
  //     structure::document::set_focus(document, m, *d);
  //     const int border_width = 1;
  //     if(border_width > 0)
  //     {
  //       if(dim.x >= border_width)
  //         dim.x -= border_width;
  //       if(dim.y >= border_width)
  //         dim.y -= border_width;
  //       dim.width += 2*border_width;
  //       dim.height += 2*border_width;
  //     }
  //     typename descriptor_traits::focus_border_color_type
  //       border_color (0u, 0u, 0xFFu);
  //     if(descriptor_traits::has_focus_border_color(*d))
  //       border_color = descriptor_traits::focus_border_color (*d);
  //     std::size_t border_width_temp
  //       = border_width >= 0
  //       ?border_width:-border_width;
  //     executor_traits::start
  //       (media_traits::executor (m)
  //        , s
  //        , d
  //        , dim
  //        , border_width_temp
  //        , border_color
  //        BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a)
  //       );
  //   }
  //   else
  //   {
  //     typename descriptor_traits::focus_border_color_type
  //       border_color;
  //     executor_traits::start
  //       (media_traits::executor (m)
  //        , s
  //        , d
  //        , dim
  //        , 0u
  //        , border_color
  //        BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a)
  //     );
  //   }
  // }
  // else
  // {
  //   typename descriptor_traits::focus_border_color_type
  //     border_color;
  //   executor_traits::start
  //     (media_traits::executor (m)
  //      , s
  //      , d
  //      , dim
  //      , 0u
  //      , border_color
  //      BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a)
  //     );
  // }
  algorithm::structure::document::register_event (document, m, interface_
                                                  , gntl::transition_enum::starts
                                                  , gntl::event_enum::presentation);
}
#endif
