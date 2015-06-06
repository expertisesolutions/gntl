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

#ifndef GNTL_ALGORITHM_STRUCTURE_PORT_LOOKUP_FUNCTOR_BASE_HPP
#define GNTL_ALGORITHM_STRUCTURE_PORT_LOOKUP_FUNCTOR_BASE_HPP

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace port {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/port/lookup_functor_base.hpp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
#define GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base \
  BOOST_PP_CAT(lookup_functor_base, BOOST_PP_ITERATION())
template <typename Port, typename Context, typename ContextLocation, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
struct GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base
{
#define GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_initialization_list(z, n, data) \
  , BOOST_PP_CAT(a, n) ( BOOST_PP_CAT(a, n) )

  GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base(Port port, Context context
                                                          , ContextLocation context_location, Document document
                                                          BOOST_PP_ENUM_TRAILING_BINARY_PARAMS
                                                          (BOOST_PP_ITERATION(), A, a))
    : port(port), context(context), context_location(context_location), document(document)
      BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                      , GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_initialization_list, ~)
  {}
#undef GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_initialization_list

  Port port;
  Context context;
  ContextLocation context_location;
  Document document;
  
#define GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_variables(z, n, data) \
  BOOST_PP_CAT(A, n) BOOST_PP_CAT(a, n);

  BOOST_PP_REPEAT(BOOST_PP_ITERATION(), GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_variables, ~)
#undef GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base_variables
};
#undef GNTL_ALGORITHM_STRUCTURE_PORT_START_lookup_functor_base
#endif
