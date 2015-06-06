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

#ifndef GNTL_CONCEPT_STRUCTURE_EXECUTOR_CALL_XXX_HPP
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_CALL_XXX_HPP

#include <gntl/detail/max_args.hpp>
#include <gntl/concept_check.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure { namespace executor_detail {

template <typename ExecutorTraits>
struct call_start
{
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_call start
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/executor_call_xxx.hpp"))
#include BOOST_PP_ITERATE ()
#undef GNTL_CONCEPT_STRUCTURE_EXECUTOR_call 

  typedef void result_type;
};

template <typename ExecutorTraits>
struct call_stop
{
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_call stop
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/executor_call_xxx.hpp"))
#include BOOST_PP_ITERATE ()
#undef GNTL_CONCEPT_STRUCTURE_EXECUTOR_call 

  typedef void result_type;
};

template <typename ExecutorTraits>
struct call_pause
{
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_call pause
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/executor_call_xxx.hpp"))
#include BOOST_PP_ITERATE ()
#undef GNTL_CONCEPT_STRUCTURE_EXECUTOR_call 

  typedef void result_type;
};

template <typename ExecutorTraits>
struct call_resume
{
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_call resume
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/executor_call_xxx.hpp"))
#include BOOST_PP_ITERATE ()
#undef GNTL_CONCEPT_STRUCTURE_EXECUTOR_call 

  typedef void result_type;
};

template <typename ExecutorTraits>
struct call_abort
{
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_call abort
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/executor_call_xxx.hpp"))
#include BOOST_PP_ITERATE ()
#undef GNTL_CONCEPT_STRUCTURE_EXECUTOR_call 

  typedef void result_type;
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
void operator()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  // If you have an error here, then you probably forgot to
  // to implement a static function in your executor_traits, e.g.,
  // start,stop,pause,resume,abort
  ExecutorTraits:: GNTL_CONCEPT_STRUCTURE_EXECUTOR_call (BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
}
#endif
