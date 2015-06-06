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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_ABORT_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_ABORT_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/context/abort_action_traits.hpp>
#include <gntl/algorithm/structure/component/abort.hpp>
#include <gntl/algorithm/structure/port/abort.hpp>
#include <gntl/algorithm/structure/port/abort_normal_action.hpp>
#include <gntl/concept/parser/port/port.hpp>
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

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/context/abort_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Component, typename Context, typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void abort_action_traits::abort_component (Component component, Context context, Descriptor descriptor
                                           , Document document
                                           BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  GNTL_DEBUG_LOG("aborting component by context" << std::endl)
    typedef typename boost::unwrap_reference<Document>::type document_type;
    typedef typename boost::unwrap_reference<Context>::type context_type;
    typedef concept::structure::document_traits<document_type> document_traits;
    GNTL_CONCEPT_ASSERT ((concept::structure::Document<document_type>));
    GNTL_CONCEPT_ASSERT ((concept::structure::Context<context_type>));
    algorithm::structure::component::abort (component, descriptor, document
                                           BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    typedef typename concept::structure::document_traits
      <document_type>::component_identifier component_identifier;
    boost::optional<component_identifier> interface_;
    algorithm::structure::document::register_event(document, component
                                                   , interface_
                                                   , gntl::transition_enum::aborts
                                                   , gntl::event_enum::presentation);
}

template <typename Port, typename Context, typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void abort_action_traits::abort_port (Port port, Context context, Descriptor descriptor
                                      , Document document
                                      BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename boost::unwrap_reference<Document>::type document_type;
  typedef typename boost::unwrap_reference<Context>::type context_type;
  typedef typename boost::unwrap_reference<Port>::type port_type;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef concept::parser::port_traits<port_type> port_traits;
  GNTL_CONCEPT_ASSERT ((concept::structure::Document<document_type>));
  GNTL_CONCEPT_ASSERT ((concept::structure::Context<context_type>));
  GNTL_CONCEPT_ASSERT ((concept::parser::Port<port_type>));
  // algorithm::structure::port::abort (port, context, document, full
  //                                    BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
  typedef typename document_traits::component_identifier component_identifier;
  component_identifier interface_ = port_traits::identifier(port);
  algorithm::structure::document::register_event(document, context
                                                 , interface_
                                                 , gntl::transition_enum::aborts
                                                 , gntl::event_enum::presentation);
}
#endif

