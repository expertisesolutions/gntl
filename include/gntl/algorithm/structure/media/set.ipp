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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_IPP

#include <gntl/structure/new_instance_reused_media.hpp>
#include <gntl/structure/same_instance_reused_media.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/set.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename SetMediaTraits, typename Media, typename Interface, typename Descriptor
          , typename Value, typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void set_no_refer
  (Media m, Interface interface_, Descriptor descriptor, Value value
   , Document document, media::dimensions full
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  GNTL_DEBUG_LOG("setting value for media interface" << std::endl)
  SetMediaTraits::set
    (m, interface_, descriptor, value, document, full
     BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename SetMediaTraits, typename Media, typename Interface
          , typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void commit_set_no_refer
  (Media m, Interface interface_, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  GNTL_DEBUG_LOG("commit setting value for media interface" << std::endl)
  SetMediaTraits::commit_set
    (m, interface_, document
     BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename SetMediaTraits, typename Media, typename Interface, typename Descriptor
          , typename Value, typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void set
  (Media m, Interface interface_, Descriptor descriptor, Value value
   , Document document, media::dimensions full
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
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

  if(media_traits::has_refer(m))
  {
    GNTL_DEBUG_LOG("Has refer, should do something different" << std::endl)
    typedef typename media_traits::identifier_type refer_type;
    refer_type refer = media_traits::refer(m);
    GNTL_DEBUG_LOG("Should search for " << refer << std::endl)
    typedef typename document_traits::media_lookupable media_lookupable;
    media_lookupable lookupable = document_traits::media_lookup(document);
    typedef concept::lookupable_traits<media_lookupable> lookupable_traits;
    typedef typename lookupable_traits::result_type lookup_result;
    lookup_result media_lookup = lookupable_traits::lookup(lookupable, refer);
    if(media_lookup != lookupable_traits::not_found(lookupable))
    {
      if(!media_traits::has_instance(m) || media_traits::instance(m) == "new")
      {
        gntl::structure::new_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::set_no_refer<SetMediaTraits>
          (new_media, interface_, descriptor, value, document, full
           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      }
      else if(media_traits::instance(m) == "instSame")
      {
        gntl::structure::same_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::set_no_refer<SetMediaTraits>
          (new_media, interface_, descriptor, value, document, full
           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      }
    }
  }
  else
  {
    media::set_no_refer<SetMediaTraits>
      (m, interface_, descriptor, value, document, full
       BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
  }
}

template <typename SetMediaTraits, typename Media, typename Interface
          , typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void commit_set
  (Media m, Interface interface_, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
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
      if(!concept::has_instance(m) || concept::instance(m) == "new")
      {
        gntl::structure::new_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::commit_set_no_refer<SetMediaTraits>
          (new_media, interface_, document
           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      }
      else if(concept::instance(m) == "instSame")
      {
        gntl::structure::same_instance_reused_media
          <typename gntl::ref_once_meta<media_type>::type
           , typename gntl::ref_once_meta<media_type>::type>
          new_media(gntl::ref_once(m), gntl::ref_once(*media_lookup));
        media::commit_set_no_refer<SetMediaTraits>
          (new_media, interface_, document
           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      }
    }
  }
  else
  {
    media::commit_set_no_refer<SetMediaTraits>
      (m, interface_, document
       BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
  }
}
#endif
