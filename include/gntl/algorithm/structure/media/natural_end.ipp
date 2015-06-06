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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_IPP

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/structure/new_instance_reused_media.hpp>
#include <gntl/structure/same_instance_reused_media.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/natural_end.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename NaturalEndMediaTraits, typename Media, typename Descriptor
          , typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void natural_end_no_refer
  (Media m, Descriptor descriptor, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)
  )
{
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typedef typename media_traits::descriptor_type descriptor_type;
    typedef typename media_traits::presentation_type presentation_type;
    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
    GNTL_DEBUG_LOG("natural_ending media no refer " << concept::identifier(m) << std::endl)
    GNTL_DEBUG_LOG("Media has " << boost::distance(concept::presentation_all(m))
                   << " presentations" << std::endl)

    descriptor_type result_descriptor = media::descriptor_compose(m, descriptor, document);

    if(concept::has_presentation(m, result_descriptor))
    {
      GNTL_DEBUG_LOG("found presentation media/result_descriptor" << std::endl)
      presentation_type p = concept::get_presentation(m, result_descriptor);
      if(!presentation_traits::is_sleeping (p))
      {
        GNTL_DEBUG_LOG("media is running, really natural_ending" << std::endl)
        NaturalEndMediaTraits::natural_end
          (m, p, document BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      }
      else
        GNTL_DEBUG_LOG("Media/descriptor not running" << std::endl)
    }
    else
    {
      GNTL_DEBUG_LOG("Couldn't find presentation with media/descriptor descriptor: "
                     << result_descriptor << std::endl)
    }
}

template <typename NaturalEndMediaTraits, typename Media, typename Descriptor
          , typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void natural_end
  (Media m, Descriptor descriptor, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)
  )
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef typename media_traits::descriptor_type descriptor_type;
  typedef typename media_traits::presentation_type presentation_type;
  typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
  GNTL_DEBUG_LOG("natural_ending media" << std::endl)

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
      if(!concept::has_instance(m) || concept::instance(m) == "new")
      {
        GNTL_DEBUG_LOG("Refer is of type instance \"new\"" << std::endl)
        gntl::structure::new_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::natural_end_no_refer<NaturalEndMediaTraits>
          (new_media, descriptor, document
           BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
      }
      else if(concept::instance(m) == "instSame")
      {
        GNTL_DEBUG_LOG("Refer is of type instance \"instSame\"" << std::endl)
        gntl::structure::same_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::natural_end_no_refer<NaturalEndMediaTraits>
          (new_media, descriptor, document
           BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
      }
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
    media::natural_end_no_refer<NaturalEndMediaTraits>(m, descriptor, document
                                                       BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
  }
}
#endif
