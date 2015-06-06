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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/document/register_event.hpp>
#include <gntl/algorithm/structure/media/concrete_identifier.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/spirit/home/qi.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, GNTL_MAX_ARGS               \
  , "gntl/algorithm/structure/media/set_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Media, typename Interface, typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void set_action_traits::set
  (Media m, Interface interface_, Descriptor descriptor, Value value
   , Document document, media::dimensions full
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  GNTL_DEBUG_LOG(" set action for media "
                 << concept::identifier(m)
                 << " interface " << interface_
                 << " with value " << value
                 << std::endl)

  if(document_traits::has_global_properties_media(document))
  {
    if(document_traits::global_properties_media(document) == media::concrete_identifier(m))
    {
      GNTL_DEBUG_LOG("Setting as document property " << interface_
                     << " with value " << value << std::endl)
      document_traits::start_set_property(document, interface_, value);
      boost::optional<typename document_traits::component_identifier>
        optional_interface = typename document_traits::component_identifier(interface_);
      algorithm::structure::document::register_event (document, m, optional_interface
                                                      , gntl::transition_enum::starts
                                                      , gntl::event_enum::attribution);
      return;
    }
  }

  bool set = false;
  {
    GNTL_DEBUG_LOG("Setting in own media" << std::endl)
    typedef typename media_traits::presentation_range presentation_range_value_type;
    typedef typename unwrap_parameter<presentation_range_value_type>::type presentation_range;
    presentation_range_value_type presentations = concept::presentation_all(m);
    typedef typename boost::range_iterator<presentation_range>::type presentation_iterator;

    for(presentation_iterator first = boost::begin(presentations)
          , last = boost::end(presentations)
          ;first != last; ++first)
    {
      typedef typename boost::range_value<presentation_range>::type presentation_value_type;
      typedef typename unwrap_parameter<presentation_value_type>::type presentation_type;
      typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
      if(presentation_traits::is_occurring(*first))
      {
        bool integer_property;
        int int_value;
        integer_property =
          (
           interface_ == "left"
           || interface_ == "right"
           || interface_ == "top"
           || interface_ == "bottom"
           || interface_ == "width"
           || interface_ == "height"
          )
          && boost::spirit::qi::parse(value.begin(), value.end(), boost::spirit::qi::int_, int_value);
        // typedef typename presentation_traits::descriptor_type descriptor_type;
        // descriptor_type descriptor = concept::structure::current_descriptor(*first);
        // media::dimensions dimensions
        //   = calculate_dimensions_from_media_descriptor(m, document, descriptor, full);
        if((integer_property && concept::start_set_property(*first, interface_, int_value))
           || (!integer_property && concept::start_set_property(*first, interface_, value)))
        {
          std::cout << "descriptor has explicit duration "
                    << concept::has_explicit_duration(descriptor) << std::endl;
          boost::optional<typename document_traits::component_identifier>
            optional_interface = typename document_traits::component_identifier(interface_);
          algorithm::structure::document::register_event (document, m, optional_interface
                                                          , gntl::transition_enum::starts
                                                          , gntl::event_enum::attribution);
          set = true;
          break;
        }
      }
      break;
    }

    if(!set && concept::has_property(m, interface_))
    {
      boost::optional<typename document_traits::component_identifier>
        optional_interface = typename document_traits::component_identifier(interface_);
      algorithm::structure::document::register_event (document, m, optional_interface
                                                      , gntl::transition_enum::starts
                                                      , gntl::event_enum::attribution);
      GNTL_DEBUG_LOG("has property" << std::endl)
      media_traits::start_set_property(m, interface_, value);
    }
  }  
}

template <typename Media, typename Interface, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void set_action_traits::commit_set(Media m, Interface interface_, Document document
                                   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  GNTL_DEBUG_LOG("commit_set " << std::endl)
  
  GNTL_DEBUG_LOG(" commit set action for media "
                 << concept::identifier(m)
                 << " interface " << interface_
                 << std::endl)

  if(document_traits::has_global_properties_media(document))
  {
    if(document_traits::global_properties_media(document) == media::concrete_identifier(m))
    {
      document_traits::commit_set_property(document, interface_);
      boost::optional<typename document_traits::component_identifier>
        optional_interface = typename document_traits::component_identifier(interface_);
      algorithm::structure::document::register_event (document, m, optional_interface
                                                      , gntl::transition_enum::stops
                                                      , gntl::event_enum::attribution);
      return;
    }
  }

  bool set = false;
  {
    GNTL_DEBUG_LOG("Setting in own media" << std::endl)
    typedef typename media_traits::presentation_range presentation_range_value_type;
    typedef typename unwrap_parameter<presentation_range_value_type>::type presentation_range;
    presentation_range_value_type presentations = concept::presentation_all(m);
    typedef typename boost::range_iterator<presentation_range>::type presentation_iterator;

    for(presentation_iterator first = boost::begin(presentations)
          , last = boost::end(presentations);first != last; ++first)
    {
      typedef typename boost::range_value<presentation_range>::type presentation_value_type;
      typedef typename unwrap_parameter<presentation_value_type>::type presentation_type;
      typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
      if(presentation_traits::is_occurring(*first))
      {
        if(presentation_traits::commit_set_property(*first, interface_))
        {
          boost::optional<typename document_traits::component_identifier>
            optional_interface = typename document_traits::component_identifier(interface_);
          algorithm::structure::document::register_event (document, m, optional_interface
                                                          , gntl::transition_enum::stops
                                                          , gntl::event_enum::attribution);
          set = true;
          break;
        }
      }
      break;
    }

    if(!set && concept::has_property(m, interface_))
    {
      GNTL_DEBUG_LOG("has property" << std::endl)
      media_traits::commit_set_property(m, interface_);
      boost::optional<typename document_traits::component_identifier>
        optional_interface = typename document_traits::component_identifier(interface_);
      algorithm::structure::document::register_event (document, m, optional_interface
                                                      , gntl::transition_enum::stops
                                                      , gntl::event_enum::attribution);
    }
  }  
}
#endif
