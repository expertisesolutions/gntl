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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_RESUME_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_RESUME_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/media/resume_action_traits.hpp>
#include <gntl/algorithm/structure/document/register_event.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, GNTL_MAX_ARGS               \
  , "gntl/algorithm/structure/media/resume_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Media, typename Presentation, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void resume_action_traits::resume
  (Media m, Presentation presentation, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
  )
{
  typedef typename boost::unwrap_reference<Presentation>::type presentation_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  presentation_traits::resume
    (presentation BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));

  boost::optional<typename document_traits::component_identifier> interface_;
  algorithm::structure::document::register_event (document, m, interface_
                                                  , gntl::transition_enum::resumes
                                                  , gntl::event_enum::presentation);
}  
#endif
