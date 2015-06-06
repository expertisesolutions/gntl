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

#ifndef GNTL_ALGORITHM_STRUCTURE_PORT_STOP_IPP
#define GNTL_ALGORITHM_STRUCTURE_PORT_STOP_IPP

#include <gntl/algorithm/structure/port/lookup_functor_base.hpp>
#include <gntl/algorithm/structure/component/lookup.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace port {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/port/stop.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
#define GNTL_ALGORITHM_STRUCTURE_PORT_STOP_stop_lookup_functor \
  BOOST_PP_CAT(stop_lookup_functor, BOOST_PP_ITERATION())
#define GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base \
  BOOST_PP_CAT(lookup_functor_base, BOOST_PP_ITERATION())
#define GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base_type    \
  GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base               \
  <Port, Context, ContextLocation, Document BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), A)>

template <typename StopPortTraits, typename Port, typename Context
          , typename ContextLocation, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
struct GNTL_ALGORITHM_STRUCTURE_PORT_STOP_stop_lookup_functor
  : GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base_type
{
  typedef GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base_type base_type;

  GNTL_ALGORITHM_STRUCTURE_PORT_STOP_stop_lookup_functor
  (Port port, Context context, ContextLocation context_location, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
    : base_type(port, context, context_location, document BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a))
  {}

  typedef void result_type;
  template <typename Component>
  result_type operator()(Component component) const
  {
    StopPortTraits::stop_port_component(this->port, component, this->context, this->document
                                          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), this->a));
  }
};

template <typename StopPortTraits, typename Port, typename Context, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void stop (Port port, Context context, Document document
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename boost::unwrap_reference<Port>::type port_type;
  typedef typename boost::unwrap_reference<Context>::type context_type;
  typedef gntl::concept::parser::port_traits<port_type> port_traits;
  typedef gntl::concept::structure::context_traits<context_type> context_traits;

  GNTL_CONCEPT_ASSERT ((concept::parser::Port<port_type>));
  GNTL_CONCEPT_ASSERT ((concept::structure::Context<context_type>));

  typedef typename concept::structure::context_traits<context_type> context_traits;

  try
  {
  algorithm::structure::component::lookup(port_traits::component(port)
                                          , GNTL_ALGORITHM_STRUCTURE_PORT_STOP_stop_lookup_functor
                                          <StopPortTraits, Port, Context, int, Document
                                          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), A)>
                                          (port, context, 0, document
                                           BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a))
                                          , context_traits::media_lookup(context)
                                          , context_traits::context_lookup(context)
                                          , context_traits::switch_lookup(context));
  }
  catch(structure::component::lookup_failed_error& e)
  {
    GNTL_DEBUG_LOG("Error lookup " << __LINE__ << std::endl)
  }
}
#undef GNTL_ALGORITHM_STRUCTURE_PORT_STOP_stop_lookup_functor
#undef GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base
#undef GNTL_ALGORITHM_STRUCTURE_PORT_STOP_lookup_functor_base_type

#endif
