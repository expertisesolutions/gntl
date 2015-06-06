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

#ifndef GNTL_STRUCTURE_COMPOSED_CONTEXT_HPP
#define GNTL_STRUCTURE_COMPOSED_CONTEXT_HPP

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/algorithm/parser/causal_connector.hpp>
#include <gntl/structure/composed/media_lookupable.hpp>
#include <gntl/structure/composed/causal_connector_lookupable.hpp>
#include <gntl/structure/composed/switch_lookupable.hpp>
#include <gntl/structure/composed/context_lookupable.hpp>
#include <gntl/structure/composed/port_lookupable.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/switch.hpp>
#include <gntl/parameter.hpp>
#include <gntl/range.hpp>

#include <boost/iterator/iterator_adaptor.hpp>

#include <vector>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserContext, typename PresentationFactory, typename ParserConnectorBase>
struct context
{
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::Context<ParserContext>));
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::ConnectorBase<ParserConnectorBase>));

  typedef typename unwrap_parameter<ParserContext>::type parser_context_type;
  typedef concept::parser::context_traits<parser_context_type> parser_context_traits;

  typedef typename unwrap_parameter<ParserConnectorBase>::type connector_base;
  typedef concept::parser::connector_base_traits<connector_base> connector_base_traits;
  typedef typename connector_base_traits::causal_connector_range causal_connector_range_value_type;
  typedef typename unwrap_parameter<causal_connector_range_value_type>::type causal_connector_range;
  typedef typename boost::range_value<causal_connector_range>::type causal_connector_value_type;
  typedef typename unwrap_parameter<causal_connector_value_type>::type causal_connector_type;

  typedef typename parser_context_traits::context_range parser_context_range;
  typedef typename boost::range_value<parser_context_range>::type inner_parser_context_type;
  typedef context<inner_parser_context_type, PresentationFactory, ParserConnectorBase> inner_context_type;

  typedef typename parser_context_traits::media_range parser_media_range_value_type;
  typedef typename unwrap_parameter<parser_media_range_value_type>::type parser_media_range;
  typedef typename boost::range_value<parser_media_range>::type parser_media_value_type;
  typedef composed::media<parser_media_value_type, PresentationFactory> media_type;

  typedef typename parser_context_traits::link_range parser_link_range_value_type;
  typedef typename unwrap_parameter<parser_link_range_value_type>::type parser_link_range;
  typedef typename boost::range_value<parser_link_range>::type parser_link_value_type;
  typedef composed::link<parser_link_value_type, causal_connector_type> link_type;

  typedef typename unwrap_parameter<typename parser_context_traits::switch_range>::type parser_switch_value_range;
  typedef typename boost::range_value<parser_switch_value_range>::type parser_switch_value_type;
  typedef composed::switch_<parser_switch_value_type, PresentationFactory, ParserConnectorBase> switch_type;

  typedef typename parser_context_traits::port_range port_range;
  typedef boost::iterator_range<typename std::vector<inner_context_type>::iterator> context_range;
  typedef boost::iterator_range<typename std::vector<media_type>::iterator> media_range;
  typedef boost::iterator_range<typename std::vector<media_type>::const_iterator> media_const_range;
  typedef boost::iterator_range<typename std::vector<link_type>::iterator> link_range;
  typedef boost::iterator_range<typename std::vector<switch_type>::iterator> switch_range;

  template <typename OtherParserContext, typename CausalConnectorLookupable>
  context (OtherParserContext p
           , CausalConnectorLookupable causal_connector_lookupable
           , PresentationFactory f = PresentationFactory())
    : parser_context(p)
  {
    initialize(f, causal_connector_lookupable);
  }

  template <typename OtherParserContext>
  context (OtherParserContext p
           , PresentationFactory f = PresentationFactory())
    : parser_context(p)
  {
    composed::causal_connector_lookupable<ParserConnectorBase> causal_connector_lookupable;
    initialize(f, causal_connector_lookupable);
  }

  context ()
  {
    composed::causal_connector_lookupable<ParserConnectorBase> causal_connector_lookupable;
    initialize(PresentationFactory(), causal_connector_lookupable);
  }

private:
  template <typename CausalConnectorLookupable>
  void initialize(PresentationFactory f
                  , CausalConnectorLookupable causal_connector_lookupable)
  {
    parser_context_range contexts = parser_context_traits::context_all (parser_context);
    typedef typename boost::range_iterator<parser_context_range>::type context_iterator;
    for(context_iterator first = boost::begin (contexts), last = boost::end (contexts)
          ;first != last;++first)
      this->contexts.push_back (inner_context_type (*first, causal_connector_lookupable, f));

    typedef typename parser_context_traits::media_range media_range;
    media_range medias = parser_context_traits::media_all (parser_context);
    typedef typename boost::range_iterator<media_range>::type media_iterator;
    for(media_iterator first = boost::begin (medias), last = boost::end (medias)
          ;first != last;++first)
      this->medias.push_back (media_type (*first, f));
        
    typedef typename parser_context_traits::switch_range switch_range;
    switch_range switches = parser_context_traits::switch_all (parser_context);
    typedef typename boost::range_iterator<switch_range>::type switch_iterator;
    for(switch_iterator first = boost::begin (switches), last = boost::end (switches)
          ;first != last;++first)
      this->switches.push_back (switch_type (*first, f, causal_connector_lookupable));

    {
      typedef typename unwrap_parameter<CausalConnectorLookupable>::type lookupable_type;
      typedef concept::lookupable_traits<lookupable_type> lookupable_traits;

      typedef typename parser_context_traits::link_range link_range_value_type;
      link_range_value_type links = parser_context_traits::link_all (parser_context);
      typedef typename unwrap_parameter<link_range_value_type>::type link_range;
      typedef typename boost::range_iterator<link_range>::type link_iterator;
      for(link_iterator first = boost::begin (links), last = boost::end (links)
            ;first != last;++first)
      {
        typedef typename boost::range_value<link_range>::type link_value_type;
        typedef typename unwrap_parameter<link_value_type>::type parser_link_type;
        typedef concept::parser::link_traits<parser_link_type> link_traits;

        typedef typename lookupable_traits::result_type lookup_result;

        lookup_result r = lookupable_traits::lookup(causal_connector_lookupable
                                                    , link_traits::xconnector(*first));
        if(r != lookupable_traits::not_found(causal_connector_lookupable))
        {
          this->links.push_back (link_type(*first, *r));
        }
      }
    }
  }
public:

  typedef composed::media_lookupable<media_range> media_lookupable;
  typedef composed::context_lookupable<context_range> context_lookupable;
  typedef composed::switch_lookupable<switch_range> switch_lookupable;
  typedef composed::port_lookupable<port_range> port_lookupable;

  ParserContext parser_context;
  std::vector<inner_context_type> contexts;
  std::vector<media_type> medias;
  std::vector<link_type> links;
  std::vector<switch_type> switches;
};

} }

namespace concept { namespace structure {

template <typename ParserContext, typename PresentationFactory, typename ParserCausalConnector>
struct context_traits<gntl::structure::composed::context<ParserContext, PresentationFactory
                                                         , ParserCausalConnector> >
{
  typedef boost::mpl::true_ is_context;
  typedef gntl::structure::composed::context<ParserContext, PresentationFactory, ParserCausalConnector>
    context_type;
  typedef typename context_type::parser_context_type parser_context_type;
  typedef concept::parser::context_traits<parser_context_type> parser_traits;
  typedef typename parser_traits::identifier_type identifier_type;

  typedef typename context_type::port_range port_range;
  typedef typename context_type::media_range media_range;
  typedef typename context_type::media_const_range media_const_range;
  typedef typename context_type::context_range context_range;
  typedef typename context_type::link_range link_range;
  typedef typename context_type::switch_range switch_range;
  typedef typename context_type::media_lookupable media_lookupable;
  typedef typename context_type::context_lookupable context_lookupable;
  typedef typename context_type::switch_lookupable switch_lookupable;
  typedef typename context_type::port_lookupable port_lookupable;
  typedef typename parser_traits::refer_type refer_type;

    static identifier_type identifier(context_type const& c)
    {
      return parser_traits::identifier(c.parser_context);
    }
    static switch_lookupable switch_lookup(context_type& c)
    {
      return switch_lookupable(switch_range(c.switches.begin(), c.switches.end()));
    }
    static port_lookupable port_lookup(context_type& c)
    {
      return port_lookupable(parser_traits::port_all(c.parser_context));
    }
    static media_lookupable media_lookup(context_type& c)
    {
      return media_lookupable(media_range(c.medias.begin(), c.medias.end()));
    }
    static context_lookupable context_lookup(context_type& c)
    {
      return context_lookupable(context_range(c.contexts.begin(), c.contexts.end()));
    }
    static port_range port_all (context_type const& c)
    {
      return parser_traits::port_all (c.parser_context);
    }
    static media_const_range media_all (context_type const& c)
    {
      return media_const_range
        (c.medias.begin (), c.medias.end ());
    }
    static media_range media_all (context_type& c)
    {
      return media_range
        (c.medias.begin (), c.medias.end ());
    }
    static context_range context_all (context_type& c)
    {
      return context_range(c.contexts.begin(), c.contexts.end());
    }
    static link_range link_all (context_type& c)
    {
      return link_range(c.links.begin(), c.links.end());
    }
    static switch_range switch_all (context_type& c)
    {
      return switch_range(c.switches.begin(), c.switches.end());
    }

    static bool is_presentation_occurring (context_type const& c)
    {
      media_const_range medias = media_all(c);
      typedef typename boost::range_iterator<media_const_range>::type media_iterator;
      for(media_iterator first = boost::begin(medias)
            , last = boost::end(medias);first != last;++first)
      {
        typedef typename boost::range_value<media_const_range>::type media_value_type;
        typedef typename boost::unwrap_reference<media_value_type>::type media_type;
        typedef concept::structure::media_traits<media_type> media_traits;
        typedef typename media_traits::presentation_range presentation_range;
        presentation_range presentations = media_traits::presentation_all
          (const_cast<media_type&>(*first));
        for(typename boost::range_iterator<presentation_range>::type
              first = boost::begin(presentations)
              , last = boost::end(presentations)
              ;first != last
              ;++first)
        {
          typedef typename boost::range_value<presentation_range>::type
            presentation_value_type;
          typedef typename boost::unwrap_reference<presentation_value_type>::type
            presentation_type;
          typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
          if(presentation_traits::is_occurring(*first))
            return true;
        }
      }

      {
        context_range contexts = context_all(const_cast<context_type&>(c));
        typedef typename boost::range_iterator<context_range>::type context_iterator;
        for(context_iterator first = boost::begin(contexts)
              , last = boost::end(contexts);first != last;++first)
        {
          typedef typename boost::range_value<context_range>::type context_value_type;
          typedef typename unwrap_parameter<context_value_type>::type context_type;
          typedef concept::structure::context_traits<context_type> inner_context_traits;
          if(inner_context_traits::is_presentation_occurring(*first))
            return true;
        }
      }

      {
        switch_range switches = switch_all(const_cast<context_type&>(c));
        typedef typename boost::range_iterator<switch_range>::type switch_iterator;
        for(switch_iterator first = boost::begin(switches)
              , last = boost::end(switches);first != last;++first)
        {
          typedef typename boost::range_value<switch_range>::type switch_value_type;
          typedef typename unwrap_parameter<switch_value_type>::type switch_type;
          typedef concept::structure::switch_traits<switch_type> switch_traits;
          if(switch_traits::is_presentation_occurring(*first))
            return true;
        }
      }

      return false;
    }
    static bool is_presentation_paused (context_type const& c)
    {
      return false;
    }
    static bool is_presentation_sleeping (context_type const& c)
    {
      return !is_presentation_occurring(c);
    } 
    static bool has_refer (context_type const& c)
    {
      return parser_traits::has_refer (c.parser_context);
    }
    static refer_type refer (context_type const& c)
    {
      return parser_traits::refer (c.parser_context);
    }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
