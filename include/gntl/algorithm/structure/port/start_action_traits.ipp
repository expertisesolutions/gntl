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

#ifndef GNTL_ALGORITHM_PORT_START_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_PORT_START_ACTION_TRAITS_IPP

#include <gntl/concept/structure/component_location.hpp>
#include <gntl/algorithm/structure/port/start_action_traits.hpp>
#include <gntl/detail/max_args.hpp>
#include <gntl/algorithm/structure/component/start.hpp>
#include <gntl/algorithm/structure/document/register_event.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace port {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/port/start_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Port, typename Component, typename ContextLocation
          , typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_action_traits::start_port_component (Port port, Component component, ContextLocation context_location
                                  , Document document, media::dimensions full
                                  BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
    typedef typename boost::unwrap_reference<Document>::type document_type;
    typedef typename boost::unwrap_reference<ContextLocation>::type context_location_type;
    GNTL_CONCEPT_ASSERT ((concept::structure::Document<document_type>));
    GNTL_CONCEPT_ASSERT ((concept::structure::ComponentLocation<context_location_type>));
    typedef concept::structure::document_traits<document_type> document_traits;
    typedef concept::structure::component_location_traits<context_location_type> location_traits;
    typedef typename document_traits::component_identifier component_identifier;
    typedef typename document_traits::descriptor_type descriptor_type;
    typedef typename document_traits::property_type property_type;
    typedef concept::structure::property_traits<property_type> property_traits;
    typedef typename property_traits::string_type string_type;
    boost::optional<component_identifier> interface_;
    descriptor_type descriptor;
    boost::optional<string_type> value;
    algorithm::structure::component::start (component
                                            , location_traits::compose
                                            (context_location
                                             , structure::component::identifier(component))
                                            , interface_
                                            , descriptor, value, document, full
                                            BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    algorithm::structure::document::register_event(document, port, interface_
                                                   , gntl::transition_enum::starts
                                                   , gntl::event_enum::presentation);
}

#endif
