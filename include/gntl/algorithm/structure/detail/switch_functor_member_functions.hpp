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

#ifndef BOOST_PP_IS_ITERATING
#error This header must not be included directly
#endif

#if 0
#include <gntl/algorithm/structure/detail/switch_functor_member_cases.hpp>
#endif

#if BOOST_PP_ITERATION_DEPTH() == 2
#ifdef GNTL_ALGORITHM_STRUCTURE_switch_has_default
#define GNTL_ALGORITHM_STRUCTURE_switch_size BOOST_PP_DEC(BOOST_PP_FRAME_ITERATION(1))
#else
#define GNTL_ALGORITHM_STRUCTURE_switch_size BOOST_PP_FRAME_ITERATION(1)
#endif
#else
#ifdef GNTL_ALGORITHM_STRUCTURE_switch_has_default
#define GNTL_ALGORITHM_STRUCTURE_switch_size BOOST_PP_DEC(GNTL_MAX_ARGS)
#else
#define GNTL_ALGORITHM_STRUCTURE_switch_size GNTL_MAX_ARGS
#endif
#endif

template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
result_type operator()(Enum e, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  switch(e)
  {
    // cases
#if BOOST_PP_ITERATION_DEPTH() == 2
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments BOOST_PP_FRAME_ITERATION(2)
#define BOOST_PP_FILENAME_3 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#else
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments BOOST_PP_FRAME_ITERATION(1)
#define BOOST_PP_FILENAME_2 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#endif
#if GNTL_ALGORITHM_STRUCTURE_switch_size
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(GNTL_ALGORITHM_STRUCTURE_switch_size))
#include BOOST_PP_ITERATE()
#endif
    // default
#ifdef GNTL_ALGORITHM_STRUCTURE_switch_has_default
#include "gntl/algorithm/structure/detail/switch_functor_member_default.hpp"
#endif
#undef GNTL_ALGORITHM_STRUCTURE_switch_arguments
 }
}

#undef GNTL_ALGORITHM_STRUCTURE_switch_size
