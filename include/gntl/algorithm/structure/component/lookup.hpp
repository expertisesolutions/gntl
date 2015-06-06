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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_LOOKUP_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_LOOKUP_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/parameter.hpp>
#include <gntl/ref.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/log/log.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

struct lookup_failed_error : gntl_error
{};

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/component/lookup.hpp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#elif BOOST_PP_ITERATION_DEPTH() == 1
template <typename Identifier, typename Functor, BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename L)>
typename Functor::result_type
lookup(Identifier id, Functor f, BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), L, l))
{
#define BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_PP_DEC(BOOST_PP_ITERATION()), "gntl/algorithm/structure/component/lookup.hpp"))
#include BOOST_PP_ITERATE ()
  
  GNTL_UNWIND_ERROR_INFO(lookup_failed_error()
                         , (typename error::reason<const char*>::type
                            ("Searching for component failed"))
                           (typename error::component_identifier<Identifier>::type(id)));
}
#elif BOOST_PP_ITERATION_DEPTH() == 2
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_type \
  BOOST_PP_CAT(lookupable_type, BOOST_PP_ITERATION())
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits \
  BOOST_PP_CAT(lookupable_traits, BOOST_PP_ITERATION())
{
  typedef typename unwrap_parameter<BOOST_PP_CAT(L, BOOST_PP_ITERATION())>::type 
    GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_type;
  typedef concept::lookupable_traits<GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_type>
    GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits;
  typedef typename GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits::result_type lookup_result;
  lookup_result r = GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits::lookup
    (BOOST_PP_CAT(l, BOOST_PP_ITERATION()), id);
  GNTL_DEBUG_LOG("searching in L" << BOOST_PP_ITERATION() << " " << id << std::endl)
  if(r != GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits::not_found(BOOST_PP_CAT(l, BOOST_PP_ITERATION())))
  {
    GNTL_DEBUG_LOG("found" << std::endl)
    return f(gntl::ref_if_by_ref(*r));
  }
}
#undef GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_type
#undef GNTL_ALGORITHM_STRUCTURE_COMPONENT_lookupable_traits
#endif
