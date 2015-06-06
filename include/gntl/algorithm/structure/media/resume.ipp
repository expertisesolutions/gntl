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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_RESUME_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_RESUME_IPP

#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/parameter.hpp>
#include <gntl/algorithm/structure/media/descriptor_compose.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/resume.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename ResumeMediaTraits, typename Media, typename Descriptor
          , typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void resume
  (Media m, Descriptor descriptor, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
  )
{
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typedef typename media_traits::presentation_type presentation_type;

    typedef typename media_traits::descriptor_type descriptor_value_type;
    typedef typename boost::unwrap_reference<descriptor_value_type>::type descriptor_type;
    typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;

    descriptor_type result_descriptor = media::descriptor_compose(m, descriptor, document);

    if(concept::has_presentation (m, result_descriptor))
    {
      typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
      presentation_type presentation = concept::get_presentation(m, result_descriptor);
      if(presentation_traits::is_paused(presentation))
      {
        GNTL_CONCEPT_ASSERT((concept::structure::Media<media_type>)); 
        ResumeMediaTraits::resume
          (m, presentation, document
           BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a)
          );
      }
    }
}
#endif
