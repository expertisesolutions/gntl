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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_HPP

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/algorithm/structure/media/dimensions.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/set.hpp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename MediaTraits, typename Media, typename Interface, typename Descriptor
          , typename Value, typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void set
  (Media m, Interface interface_, Descriptor descriptor, Value value, Document document, media::dimensions full
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a));

template <typename MediaTraits, typename Media, typename Interface, typename Document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), typename A)>
void commit_set
  (Media m, Interface interface_, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a));
#endif
