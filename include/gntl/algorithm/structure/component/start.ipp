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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_START_IPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_START_IPP

#include <gntl/algorithm/structure/component/start.hpp>
#include <gntl/algorithm/structure/component/start_functor.hpp>
#include <gntl/algorithm/structure/media.hpp>
#include <gntl/algorithm/structure/context.hpp>
#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context.hpp>

#include <boost/ref.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/component/start.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>
#endif
#else

template <typename Media, typename Location, typename OptionalInterface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_aux(Media c, Location l, OptionalInterface i
               , Descriptor descriptor, boost::optional<Value>, Document d
               , media::dimensions full_screen, media_tag
               BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
               )
{
  typedef typename boost::unwrap_reference<Media>::type component_type;
  typedef concept::structure::media_traits<component_type> media_traits;
  typedef typename boost::unwrap_reference<Document>::type document_type;

  // typedef gntl::concept::structure::document_traits
  //   <document_type> document_traits;
  // typedef typename document_traits::descriptor_range_type
  //   descriptor_range_type;
  // descriptor_range_type descriptor_range
  //   = document_traits::descriptor_range (d);
  // typedef typename boost::range_iterator
  //   <descriptor_range_type>::type
  //   descriptor_iterator;
  // descriptor_iterator descriptor
  //   = boost::end (descriptor_range);

  typedef typename media_traits::descriptor_type descriptor_type;

  gntl::algorithm::structure::media
    ::start (c, l, i, descriptor, d, full_screen
             BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename Context, typename Location, typename Interface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_aux(Context c, Location l, boost::optional<Interface> i
               , Descriptor descriptor, boost::optional<Value> v, Document d
               , media::dimensions full_screen, context_tag
               BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
               )
{
  typedef typename boost::unwrap_reference<Context>::type component_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
  gntl::algorithm::structure::context
    ::start (c, l, descriptor, d, full_screen
             BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename Switch, typename Location, typename Interface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_aux(Switch s, Location l, boost::optional<Interface> i
               , Descriptor descriptor, boost::optional<Value> v, Document d
               , media::dimensions full_screen, switch_tag
               BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
               )
{
  // gntl::algorithm::structure::switch_::start (s, i, d, full_screen);
}

template <typename Switch, typename Location, typename Interface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_aux(Switch s, Location l, boost::optional<Interface> i
               , Descriptor descriptor, boost::optional<Value> v, Document d
               , media::dimensions full_screen, port_tag
               BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
               )
{
}

template <typename Component, typename Location, typename Interface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start(Component c, Location location, boost::optional<Interface> i
           , Descriptor descriptor, boost::optional<Value> v, Document d
           , media::dimensions full_screen
           BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
           )
{
  typedef typename unwrap_parameter<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  component::start_aux(c, location, i, descriptor, v, d, full_screen, tag_type()
                       BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}

template <typename Component, typename Location, typename OptionalInterface
          , typename Descriptor, typename Value, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
inline typename start_functor::result_type start_functor::operator()
  (Component c, Location location, OptionalInterface i, Descriptor descriptor
   , boost::optional<Value> v, Document d, media::dimensions full_screen
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a)
   ) const
{
  component::start(c, location, i, descriptor, v, d, full_screen
                   BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
}  

#endif
