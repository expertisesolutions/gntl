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

#ifndef GNTL_ALGORITHM_STRUCTURE_SWITCH_FUNCTOR_HPP
#define GNTL_ALGORITHM_STRUCTURE_SWITCH_FUNCTOR_HPP

#include <gntl/detail/max_args.hpp>
#include <gntl/detail/void.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>

#if 0
#include <gntl/algorithm/structure/detail/switch_functor_member_functions.hpp>
#include <gntl/algorithm/structure/detail/switch_functor_member_cases.hpp>
#endif

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure {

template <typename V, typename F>
struct case_
{
  typedef V first;
  typedef F second;
};

template <typename F>
struct default_
{
};

template <typename Enum
          , BOOST_PP_ENUM_BINARY_PARAMS(GNTL_MAX_ARGS, typename C
                                        , = gntl::detail::void_ BOOST_PP_INTERCEPT)>
struct switch_functor
{
  typedef typename C0::second::result_type result_type;

  result_type operator()(Enum e) const
  {
    switch(e)
    {
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments 0
#define BOOST_PP_FILENAME_1 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(GNTL_MAX_ARGS))
#include BOOST_PP_ITERATE()
#undef GNTL_ALGORITHM_STRUCTURE_switch_arguments
    }
  }  

#define BOOST_PP_FILENAME_1 "gntl/algorithm/structure/detail/switch_functor_member_functions.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, GNTL_MAX_ARGS)
#include BOOST_PP_ITERATE()
};

template <typename Enum
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(GNTL_MAX_ARGS), typename C)
          , typename DefaultFunctor>
struct switch_functor<Enum
                      , BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(GNTL_MAX_ARGS), C)
                      , default_<DefaultFunctor> >
{
#define GNTL_ALGORITHM_STRUCTURE_switch_has_default
  typedef typename DefaultFunctor::result_type result_type;

  result_type operator()(Enum e) const
  {
    switch(e)
    {
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments 0
      // cases
#define BOOST_PP_FILENAME_1 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(GNTL_MAX_ARGS, 2))
#include BOOST_PP_ITERATE()
      // default
#include "gntl/algorithm/structure/detail/switch_functor_member_default.hpp"
#undef GNTL_ALGORITHM_STRUCTURE_switch_arguments
    }
  }  

#define BOOST_PP_FILENAME_1 "gntl/algorithm/structure/detail/switch_functor_member_functions.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, GNTL_MAX_ARGS)
#include BOOST_PP_ITERATE()

#undef GNTL_ALGORITHM_STRUCTURE_switch_has_default
};

} } }

#define BOOST_PP_FILENAME_1 "gntl/algorithm/structure/switch_functor.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, BOOST_PP_DEC(GNTL_MAX_ARGS))
#include BOOST_PP_ITERATE()

#include <gntl/detail/pop_options.hpp>

#endif
#else
namespace gntl { namespace algorithm { namespace structure {

template <typename Enum
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename C)>
struct switch_functor<Enum
                      , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), C)
                      , BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(GNTL_MAX_ARGS, BOOST_PP_ITERATION())
                                             , gntl::detail::void_ BOOST_PP_INTERCEPT)
                     >
{
  typedef typename C0::second::result_type result_type;

  result_type operator()(Enum e) const
  {
    switch(e)
    {
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments 0
#define BOOST_PP_FILENAME_2 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_DEC(BOOST_PP_ITERATION()))
#include BOOST_PP_ITERATE()
#undef GNTL_ALGORITHM_STRUCTURE_switch_arguments
    }
  }  

#define BOOST_PP_FILENAME_2 "gntl/algorithm/structure/detail/switch_functor_member_functions.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, GNTL_MAX_ARGS)
#include BOOST_PP_ITERATE()
};

template <typename Enum
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(BOOST_PP_ITERATION()), typename C)
          , typename DefaultFunctor>
struct switch_functor<Enum
                      BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_DEC(BOOST_PP_ITERATION()), C)
                      , default_<DefaultFunctor>
                      , BOOST_PP_ENUM_PARAMS(BOOST_PP_SUB(GNTL_MAX_ARGS, BOOST_PP_ITERATION())
                                             , gntl::detail::void_ BOOST_PP_INTERCEPT)
                     >
{
#define GNTL_ALGORITHM_STRUCTURE_switch_has_default
  typedef typename DefaultFunctor::result_type result_type;

  result_type operator()(Enum e) const
  {
    switch(e)
    {
#define GNTL_ALGORITHM_STRUCTURE_switch_arguments 0
      // cases
#if BOOST_PP_DEC(BOOST_PP_ITERATION())
#define BOOST_PP_FILENAME_2 "gntl/algorithm/structure/detail/switch_functor_member_cases.hpp"
#define BOOST_PP_ITERATION_LIMITS (0, BOOST_PP_SUB(BOOST_PP_ITERATION(), 2))
#include BOOST_PP_ITERATE()
#endif
      // default
#include "gntl/algorithm/structure/detail/switch_functor_member_default.hpp"
#undef GNTL_ALGORITHM_STRUCTURE_switch_arguments
    }
  }  

#define BOOST_PP_FILENAME_2 "gntl/algorithm/structure/detail/switch_functor_member_functions.hpp"
#define BOOST_PP_ITERATION_LIMITS (1, GNTL_MAX_ARGS)
#include BOOST_PP_ITERATE()

#undef GNTL_ALGORITHM_STRUCTURE_switch_has_default
};

} } }
#endif
