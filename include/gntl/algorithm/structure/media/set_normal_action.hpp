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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_HPP

#include <gntl/algorithm/structure/media/set_action_traits.hpp>
#include <gntl/algorithm/structure/media/set.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/log/log.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/media/set_normal_action.hpp"))
#include BOOST_PP_ITERATE ()
} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Media, typename Interface, typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void set
(Media m, Interface interface_, Descriptor descriptor, Value value
   , Document document, media::dimensions full
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
  )
{
  GNTL_DEBUG_LOG("set algorithm" << std::endl)
  media::set<set_action_traits>
    (m, interface_, descriptor, value, document, full
     BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
}

template <typename Media, typename Interface, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void commit_set
  (Media m, Interface interface_, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
  )
{
  media::commit_set<set_action_traits>
    (m, interface_, document
     BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
}

template <typename Media, typename Interface, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
struct BOOST_PP_CAT(commit_set_context_visitor, BOOST_PP_ITERATION())
{
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_initialization_list(z, n, data) \
  , BOOST_PP_CAT(a, n) ( BOOST_PP_CAT(a, n) )

  BOOST_PP_CAT(commit_set_context_visitor, BOOST_PP_ITERATION())
    (Media m, Interface i, Document d
     BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
    : m(m), i(i), d(d)
    BOOST_PP_REPEAT
    (BOOST_PP_ITERATION()
     , GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_initialization_list, ~)
  {}
#undef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_initialization_list

  typedef void result_type;
  result_type operator()() const
  {
    media::commit_set(m, i, d
                      BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), a));
  }

  Media m;
  Interface i;
  Document d;

#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_variables(z, n, data) \
  BOOST_PP_CAT(A, n) BOOST_PP_CAT(a, n);

  BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                  , GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_variables, ~)
#undef GNTL_ALGORITHM_STRUCTURE_MEDIA_SET_NORMAL_ACTION_commit_set_context_visitor_variables
};

template <typename Media, typename Interface, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
BOOST_PP_CAT(commit_set_context_visitor, BOOST_PP_ITERATION())
  <Media, Interface, Document BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), A)>
BOOST_PP_CAT(make_commit_set_context_visitor, BOOST_PP_ITERATION())
  (Media m, Interface i, Document d BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  return BOOST_PP_CAT(commit_set_context_visitor, BOOST_PP_ITERATION())
    <Media, Interface, Document
    BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), A)>
    (m, i, d BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), a));
}

#endif
