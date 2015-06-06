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

#ifndef GNTL_CONCEPT_STRUCTURE_PRESENTATION_CALL_START_HPP
#define GNTL_CONCEPT_STRUCTURE_PRESENTATION_CALL_START_HPP

#include <gntl/detail/max_args.hpp>

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename Traits>
struct presentation_call_start
{
  typedef void result_type;
#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/concept/structure/presentation_call_start.hpp"))
#include BOOST_PP_ITERATE ()
};

} } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
void operator()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a)) const
{
  // If you have an error here, then you probably forgot to to
  // implement the correct static start function in your
  // presentation_traits.
  return Traits::start(BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), a));
}
#endif
