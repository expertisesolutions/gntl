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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_PAUSE_ACTION_TRAITS_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_PAUSE_ACTION_TRAITS_HPP

#include <gntl/detail/max_args.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

struct pause_action_traits
{
#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, GNTL_MAX_ARGS               \
  , "gntl/algorithm/structure/media/pause_action_traits.hpp"))
#include BOOST_PP_ITERATE ()
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Media, typename Presentation, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
static void pause
  (Media m, Presentation p, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
  );
#endif
