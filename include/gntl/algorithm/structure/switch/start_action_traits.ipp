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

#ifndef GNTL_ALGORITHM_STRUCTURE_SWITCH_START_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_SWITCH_START_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/switch/evaluate.hpp>
#include <gntl/algorithm/structure/component/start.hpp>
#include <gntl/parameter.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace switch_ {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/switch/start_action_traits.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename Switch, typename OptionalInterface
          , typename Document, typename Dimensions
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_action_traits::start(Switch switch_, OptionalInterface interface_
                                , Document document, Dimensions dim
                                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename unwrap_parameter<Switch>::type switch_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::switch_traits<switch_type> switch_traits;
  typedef concept::structure::document_traits<document_type> document_traits;

  GNTL_DEBUG_LOG("start_action_traits::start" << std::endl)

  evaluate(switch_, document);
    
  if(switch_traits::is_presentation_occurring(switch_))
  {
    GNTL_DEBUG_LOG("start active component" << std::endl)
    boost::optional<typename document_traits::property_name> value;
    typedef typename switch_traits::media_range media_value_range;
    typedef typename unwrap_parameter<media_value_range>::type media_range;
    typedef typename boost::range_value<media_range>::type media_value_type;
    typedef typename unwrap_parameter<media_value_type>::type media_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typename media_traits::descriptor_type descriptor;
    component::lookup(switch_traits::active_component(switch_)
                      , boost::bind(component::start_functor(), _1, 0
                                    , interface_
                                    , descriptor, value, document, dim)
                      , switch_traits::media_lookup(switch_)
                      , switch_traits::context_lookup(switch_));

    typedef typename document_traits::component_identifier component_identifier;
    boost::optional<component_identifier> interface_;
    algorithm::structure::document::register_event
      (document, switch_, interface_, gntl::transition_enum::starts
       , gntl::event_enum::presentation);
  }
}

#endif
