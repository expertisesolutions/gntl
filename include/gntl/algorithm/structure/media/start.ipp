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

#if !defined(BOOST_PP_IS_ITERATING)

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_START_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_START_IPP

#include <gntl/structure/new_instance_reused_media.hpp>
#include <gntl/algorithm/structure/media/descriptor_compose.hpp>
#include <gntl/algorithm/structure/media/calculate_dimensions.hpp>
#include <gntl/algorithm/structure/descriptor.hpp>
#include <gntl/concept/parser/media/area.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/start.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename StartMediaTraits, typename Media, typename Location
          , typename OptionalInterface, typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_no_refer
(Media m, Location l, OptionalInterface interface_, Descriptor descriptor
 , Document document, media::dimensions full
 BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
 )
{
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef typename boost::unwrap_reference<Document>::type document_type;
    typedef typename boost::unwrap_reference<Location>::type location_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typedef concept::structure::document_traits<document_type> document_traits;
    typedef concept::structure::component_location_traits<location_type> location_traits;

    GNTL_DEBUG_LOG("Start of media " << location_traits::identifier(l) << std::endl);

    typedef typename media_traits::descriptor_type descriptor_value_type;
    typedef typename boost::unwrap_reference<descriptor_value_type>::type descriptor_type;
    typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));
    GNTL_CONCEPT_ASSERT ((concept::structure::Descriptor<descriptor_type>));

    typedef typename media_traits::presentation_type presentation_type;

    descriptor_type result_descriptor = media::descriptor_compose(m, descriptor, document);
    result_descriptor = structure::descriptor::compose_with_properties(result_descriptor, m);

    typedef typename document_traits::component_identifier interface_id_type;
    boost::optional<interface_id_type> interface_id;
    if(interface_)
      interface_id = *interface_;

    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
    if(!concept::has_presentation (m, result_descriptor)
       || presentation_traits::is_sleeping(concept::get_presentation(m, result_descriptor)))
    {
      GNTL_DEBUG_LOG("Starting media with descriptor: " << result_descriptor << std::endl)

      media::dimensions dimensions
        = calculate_dimensions_from_media_descriptor(m, document, result_descriptor, full);
      StartMediaTraits::start(m, l, interface_id, result_descriptor, dimensions
                              BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }
    else if(interface_)
    {
      GNTL_DEBUG_LOG("Presentation is running. But we might be starting an anchor" << std::endl)
      assert(!!interface_id);
      typedef typename media_traits::area_range area_value_range;
      typedef typename media_traits::presentation_type presentation_type;
      typedef typename unwrap_parameter<area_value_range>::type area_range;
      typedef typename boost::range_iterator<area_range>::type area_iterator;
      area_value_range areas = concept::area_all(m);
      for(area_iterator first = boost::begin(areas), last = boost::end(areas)
            ;first != last; ++first)
      {
        typedef typename boost::range_value<area_range>::type area_value_type;
        typedef typename unwrap_parameter<area_value_type>::type area_type;
        typedef concept::parser::area_traits<area_type> area_traits;
        if(area_traits::identifier(*first) == *interface_id)
        {
          GNTL_DEBUG_LOG("Found area corresponding to interface" << std::endl)
          presentation_type presentation = concept::get_presentation(m, result_descriptor);
          if(area_traits::has_begin(*first))
          {
            GNTL_DEBUG_LOG("Area has begin" << std::endl)
          }
          else if(area_traits::has_first(*first))
          {
            GNTL_DEBUG_LOG("Area has first" << std::endl)
          }
          else
          {
            GNTL_DEBUG_LOG("Area has no attribute" << std::endl)
            presentation_traits::start_area(presentation, area_traits::identifier(*first));
          }
          break;
        }
      }
    }    
}

template <typename StartMediaTraits, typename Media, typename Location
          , typename OptionalInterface, typename Descriptor
          , typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start
(Media m, Location l, OptionalInterface interface_, Descriptor descriptor
 , Document document, media::dimensions full
 BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
 )
{
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef typename boost::unwrap_reference<Document>::type document_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typedef concept::structure::document_traits<document_type> document_traits;

    typedef typename media_traits::descriptor_type descriptor_value_type;
    typedef typename boost::unwrap_reference<descriptor_value_type>::type descriptor_type;
    typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));
    GNTL_CONCEPT_ASSERT ((concept::structure::Descriptor<descriptor_type>));

    if(concept::has_refer(m))
    {
      GNTL_DEBUG_LOG("Has refer, should do something different" << std::endl)
      typedef typename media_traits::identifier_type refer_type;
      refer_type refer = concept::refer(m);
      GNTL_DEBUG_LOG("Should search for " << refer << std::endl)
      typedef typename document_traits::media_lookupable media_lookupable;
      media_lookupable lookupable = document_traits::media_lookup(document);
      typedef concept::lookupable_traits<media_lookupable> lookupable_traits;
      typedef typename lookupable_traits::result_type lookup_result;
      lookup_result media_lookup = lookupable_traits::lookup(lookupable, refer);
      if(media_lookup != lookupable_traits::not_found(lookupable))
      {
        GNTL_CONCEPT_ASSERT((concept::structure::Media<gntl::structure::new_instance_reused_media
                             <typename gntl::ref_once_meta<media_type>::type
                              , typename gntl::ref_once_meta<media_type>::type> >));
        gntl::structure::new_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
            new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::start_no_refer<StartMediaTraits>(new_media, l, interface_, descriptor, document, full
                                                BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
      }
      else
        GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                               , (typename error::reason<const char*>::type
                                  ("Media with refer, where referred media can't be found"))
                                 (typename error::component_identifier<refer_type>::type
                                  (concept::identifier(m)))
                                 (typename error::refer<refer_type>::type
                                  (concept::refer(m))));
    }
    else
    {
      start_no_refer<StartMediaTraits>(m, l, interface_, descriptor, document, full
                                       BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }
}
#endif
