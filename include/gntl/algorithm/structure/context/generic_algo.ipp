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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_GENERIC_ALGO_IPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_GENERIC_ALGO_IPP

#include <gntl/algorithm/structure/wrap_if.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/log/log.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/context/generic_algo.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else

namespace context_detail {

template <typename GenericContextTraits, typename Iterator, typename Context
          , typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void generic_algo_component_iterator (Iterator iterator, Context context
                                      , Descriptor descriptor, Document document
                                      BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef std::iterator_traits<Iterator> iterator_traits;
  typedef typename iterator_traits::value_type value_type;
  typedef typename boost::is_convertible
    <typename iterator_traits::iterator_category
     , std::forward_iterator_tag>::type is_forward;
  typename wrapper_if_c
  <boost::is_reference_wrapper<Context>::value
   && is_forward::value, value_type
   >::type 
   component = wrap_if<boost::is_reference_wrapper<Context>::value && is_forward::value>(*iterator);

  GNTL_DEBUG_LOG("component will be ref" 
            << (boost::is_reference_wrapper<Context>::value && is_forward::value)
                 << std::endl)

  GenericContextTraits::action_component (component, context, descriptor, document
                                          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
}

}

template <typename GenericContextTraits, typename Context, typename Descriptor
          , typename Document BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void generic_algo (Context context, Descriptor descriptor
                   , Document document BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
    typedef typename boost::unwrap_reference<Context>::type context_type;
    GNTL_CONCEPT_ASSERT ((concept::structure::Context<context_type>));

    typedef typename concept::structure::context_traits<context_type> context_traits;

    typedef typename context_traits::port_range port_value_range;
    port_value_range ports = context_traits::port_all (context);
    typedef typename unwrap_parameter<port_value_range>::type port_range;
    typedef typename boost::range_iterator<port_range>::type port_iterator;
    for(port_iterator first = boost::begin(ports), last = boost::end(ports)
          ;first != last; ++first)
    {
      typedef typename boost::range_value<port_range>::type port_value_type;
      typedef typename unwrap_parameter<port_value_type>::type port_type;
      GenericContextTraits::action_port (*first, context, descriptor, document
                                         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }

    typedef typename context_traits::media_range media_value_range;
    media_value_range medias = context_traits::media_all (context);
    typedef typename unwrap_parameter<media_value_range>::type media_range;
    typedef typename boost::range_iterator<media_range>::type media_iterator;
    for(media_iterator first = boost::begin (medias), last = boost::end (medias)
          ;first != last;++first)
    {
      context_detail::generic_algo_component_iterator<GenericContextTraits>
        (first, context, descriptor, document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }

    typedef typename context_traits::context_range context_value_range;
    context_value_range contexts = context_traits::context_all (context);
    typedef typename unwrap_parameter<context_value_range>::type context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;
    for(context_iterator first = boost::begin (contexts), last = boost::end (contexts)
          ;first != last;++first)
    {
      context_detail::generic_algo_component_iterator<GenericContextTraits>
        (first, context, descriptor, document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }

    typedef typename context_traits::switch_range switch_value_range;
    switch_value_range switches = context_traits::switch_all (context);
    typedef typename unwrap_parameter<switch_value_range>::type switch_range;
    typedef typename boost::range_iterator<switch_range>::type switch_iterator;
    for(switch_iterator first = boost::begin (switches), last = boost::end (switches)
          ;first != last;++first)
    {
      context_detail::generic_algo_component_iterator<GenericContextTraits>
        (first, context, descriptor, document
         BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
    }

    GenericContextTraits::register_context_action_event(document, context);
}
#endif
