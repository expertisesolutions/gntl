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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_FIND_OWNER_CONTEXT_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_FIND_OWNER_CONTEXT_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/algorithm/structure/component/lookup.hpp>
#include <gntl/parameter.hpp>
#include <gntl/ref.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/log/log.hpp>
#include <gntl/algorithm/structure/component/tag.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/optional.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/component/find_owner_context.hpp"))
#include BOOST_PP_ITERATE ()

} } } }

#endif
#else
namespace component_detail {

template <typename Context, typename OwnerContext, typename Functor
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename L)>
boost::optional<typename Functor::result_type>
find_owner_context_aux(Context context, OwnerContext owner_context, Functor f
                       , context_tag
                       , BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), L, l))
{
  return boost::none;
}

template <typename Media, typename OwnerContext, typename Functor
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename L)>
boost::optional<typename Functor::result_type>
find_owner_context_aux(Media media, OwnerContext owner_context, Functor f
                       , media_tag
                       , BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), L, l))
{
  return boost::none;
}

template <typename Switch, typename OwnerContext, typename Functor
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename L)>
boost::optional<typename Functor::result_type>
find_owner_context_aux(Switch switch_, OwnerContext owner_context, Functor f
                       , switch_tag
                       , BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), L, l))
{
  return boost::none;
}

}

template <typename Component, typename OwnerContext, typename Functor
          , BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename L)>
boost::optional<typename Functor::result_type>
find_owner_context(Component component, OwnerContext owner_context, Functor f
                   , BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_ITERATION(), L, l))
{
  typedef typename boost::unwrap_reference<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  return component_detail::find_owner_context_aux
    (component, owner_context, f, tag_type()
     BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), l));
}
#endif
