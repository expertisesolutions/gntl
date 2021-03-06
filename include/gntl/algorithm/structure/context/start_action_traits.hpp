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

#ifndef GNTL_ALGORITHM_CONTEXT_START_ACTION_TRAITS_HPP
#define GNTL_ALGORITHM_CONTEXT_START_ACTION_TRAITS_HPP

#include <gntl/algorithm/structure/document/register_event.hpp>
#include <gntl/detail/max_args.hpp>
#include <gntl/algorithm/structure/port.hpp>
#include <gntl/concept_check.hpp>
#include <boost/optional.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

struct start_action_traits
{
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/context/start_action_traits.hpp"))
#include BOOST_PP_ITERATE ()
  template <typename Document, typename Context, typename Location>
  static void register_context_start_event(Document document, Context context
                                           , Location context_location)
  {
    typedef typename unwrap_parameter<Document>::type document_type;
    typedef concept::structure::document_traits<document_type> document_traits;
    typedef typename document_traits::component_identifier component_identifier;
    boost::optional<component_identifier> interface_;
    algorithm::structure::document::register_event(document, context
                                                   , interface_, gntl::transition_enum::starts
                                                   , gntl::event_enum::presentation);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
// normal_traits member functions
template <typename Port, typename Context, typename Location
          , typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
static void start (Port port, Context context, Location context_location
                   , Descriptor descriptor, Document document, media::dimensions full
                   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a));
#endif
