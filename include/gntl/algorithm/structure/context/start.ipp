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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_IPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_IPP

#include <gntl/concept/structure/component_location.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/structure/new_instance_reused_context.hpp>
#include <gntl/algorithm/structure/context/start.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

#define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC (GNTL_MAX_ARGS), "gntl/algorithm/structure/context/start.ipp"))
#include BOOST_PP_ITERATE ()

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <typename StartContextTraits, typename Context, typename Location
          , typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start_no_refer (Context context, Location context_location
                     , Descriptor descriptor, Document document
                     BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  GNTL_DEBUG_LOG("starting context" << std::endl)
  typedef typename boost::unwrap_reference<Context>::type context_type;
  GNTL_CONCEPT_ASSERT ((concept::structure::Context<context_type>));

  typedef typename concept::structure::context_traits<context_type> context_traits;
  typedef typename context_traits::port_range port_range;

  port_range ports = context_traits::port_all (unwrap_ref (context));
  for(typename boost::range_iterator<port_range>::type
        first = boost::begin (ports)
        , last = boost::end (ports)
        ;first != last
        ;++first)
  {
    StartContextTraits::start (*first, context, context_location, descriptor, document
                               BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
  }

  StartContextTraits::register_context_start_event(document, context, context_location);
}

namespace context_detail {

#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor   \
  BOOST_PP_CAT(start_no_refer_visitor, BOOST_PP_ITERATION())

template <typename StartContextTraits, typename Context, typename Location
          , typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), typename A)>
struct GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor
{
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor_initialization_list(z, n, data) \
  , BOOST_PP_CAT(a, n) ( BOOST_PP_CAT(a, n) )

  GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor
  (Context context, Location context_location, Descriptor descriptor, Document document
   BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
    : context(context), context_location(context_location), descriptor(descriptor), document(document)
      BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                      , GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor_initialization_list, ~)
  {}
#undef GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor_initialization_list

  typedef void result_type;
  template <typename LookupContext>
  result_type operator()(LookupContext lookup_context) const
  {
    gntl::structure::new_instance_reused_context
      <typename gntl::ref_once_meta<Context>::type
       , typename gntl::ref_once_meta<LookupContext>::type>
      new_context(gntl::ref_once(context), gntl::ref_once(lookup_context));
    context::start_no_refer<StartContextTraits>(new_context, context_location, descriptor, document
                                                BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), a));
  }

  Context context;
  Location context_location;
  Descriptor descriptor;
  Document document;

#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_member_variables(z, n, data) \
  BOOST_PP_CAT(A, n) BOOST_PP_CAT(a, n);
  
  BOOST_PP_REPEAT(BOOST_PP_ITERATION()
                  , GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_member_variables, ~)
#undef GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_member_variables
};

}

template <typename StartContextTraits, typename Context
          , typename Location, typename Descriptor, typename Document
          BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION (), typename A)>
void start (Context context, Location context_location
            , Descriptor descriptor, Document document
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS (BOOST_PP_ITERATION (), A, a))
{
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename unwrap_parameter<Location>::type location_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::context_traits<context_type> context_traits;
  typedef concept::structure::component_location_traits<location_type> location_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  GNTL_DEBUG_LOG("Location identifier: " << location_traits::identifier(context_location) << std::endl);
  if(context_traits::has_refer(context))
  {
    GNTL_DEBUG_LOG("context has refer " << context_traits::refer(context) << std::endl)
    typedef typename context_traits::identifier_type refer_type;
    refer_type refer = context_traits::refer(context);
    GNTL_DEBUG_LOG("Should search for " << refer << std::endl)
    typedef typename document_traits::context_lookupable context_lookupable;
    context_lookupable lookupable = document_traits::context_lookup(document);
    typedef concept::lookupable_traits<context_lookupable> lookupable_traits;
    typedef typename lookupable_traits::result_type lookup_result;
    lookup_result context_lookup = lookupable_traits::lookup(lookupable, refer);
    if(context_lookup != lookupable_traits::not_found(lookupable))
    {
      context_detail::GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor
        <StartContextTraits, Context, Location, Descriptor, Document
         BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), A)>
        visitor(context, context_location, descriptor, document
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
      (*context_lookup).apply_visitor(visitor);
    }
    else
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Context with refer, where referred context can't be found"))
                               (typename error::component_identifier<refer_type>::type
                                (context_traits::identifier(context)))
                               (typename error::refer<refer_type>::type
                                (context_traits::refer(context))));
  }
  else
    context::start_no_refer<StartContextTraits>
      (context, context_location, descriptor, document
       BOOST_PP_ENUM_TRAILING_PARAMS (BOOST_PP_ITERATION(), a));
}
#undef GNTL_ALGORITHM_STRUCTURE_CONTEXT_START_start_no_refer_visitor
#endif
