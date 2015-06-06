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

#ifndef GNTL_ALGORITHM_STRUCTURE_SWITCH_START_IPP
#define GNTL_ALGORITHM_STRUCTURE_SWITCH_START_IPP

#include <gntl/concept/structure/switch.hpp>
#include <gntl/parameter.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace switch_ {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/switch/start.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename StartSwitchTraits, typename Switch, typename OptionalInterface
          , typename Document BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start(Switch switch_, OptionalInterface interface_, Document document
           , media::dimensions full BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  GNTL_DEBUG_LOG("should start switch" << std::endl)
  typedef typename unwrap_parameter<Switch>::type switch_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::switch_traits<switch_type> switch_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  if(switch_traits::is_presentation_sleeping(switch_))
  {
    GNTL_DEBUG_LOG("switch is sleeping" << std::endl)
    StartSwitchTraits::start(switch_, interface_, document, full
                             BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
  }
}

#endif
