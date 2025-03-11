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

#ifndef GNTL_STRUCTURE_COMPOSED_SWITCH_HPP
#define GNTL_STRUCTURE_COMPOSED_SWITCH_HPP

#include <gntl/concept/parser/switch/switch.hpp>
#include <gntl/concept/structure/switch.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/algorithm/parser/causal_connector.hpp>
#include <gntl/structure/composed/context_lookupable.hpp>
#include <gntl/structure/composed/media_lookupable.hpp>
#include <gntl/structure/composed/media_recursive_lookupable.hpp>
#include <gntl/structure/composed/media_lookupable.hpp>
#include <gntl/structure/composed/context_lookupable.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/switch_port.hpp>
#include <gntl/structure/composed/bind_rule.hpp>
#include <gntl/structure/composed/context_fwd.hpp>
#include <gntl/parameter.hpp>
#include <gntl/range.hpp>

#include <boost/iterator/indirect_iterator.hpp>

#include <vector>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserSwitch, typename PresentationFactory, typename ParserConnectorBase>
struct switch_
{
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::Switch<ParserSwitch>));
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::ConnectorBase<ParserConnectorBase>));

  typedef typename unwrap_parameter<ParserSwitch>::type parser_switch_type;
  typedef concept::parser::switch_traits<parser_switch_type> parser_switch_traits;

  typedef typename unwrap_parameter<typename parser_switch_traits::context_range>::type parser_context_range;
  typedef typename boost::range_value<parser_context_range>::type parser_context_value_type;
  typedef concept::parser::context_traits
    <typename unwrap_parameter<parser_context_value_type>::type> parser_context_traits;

  typedef typename unwrap_parameter<typename parser_switch_traits::media_range>::type parser_media_range;
  typedef typename boost::range_value<parser_media_range>::type parser_media_value_type;
  typedef composed::media<parser_media_value_type, PresentationFactory> media_type;

  typedef concept::parser::media_traits
    <typename unwrap_parameter<parser_media_value_type>::type> parser_media_traits;

  typedef composed::context<parser_context_value_type, PresentationFactory, ParserConnectorBase> context_type;
  typedef switch_<ParserSwitch, PresentationFactory, ParserConnectorBase> self_type;
  typedef self_type switch_type;

  typedef typename parser_switch_traits::bind_rule_range parser_bind_rule_range;
  typedef typename boost::range_iterator<typename unwrap_parameter<parser_bind_rule_range>::type>::type
    parser_bind_rule_iterator;
  typedef typename boost::range_value<typename unwrap_parameter<parser_bind_rule_range>::type>::type
    parser_bind_rule_value_type;

  typedef composed::switch_port switch_port_type;
  typedef composed::bind_rule<parser_bind_rule_value_type> bind_rule_type;

  template <typename OtherParserSwitch, typename CausalConnectorLookupable>
  switch_(OtherParserSwitch s, PresentationFactory f, CausalConnectorLookupable causal_connector_lookupable)
    : parser_switch(s)
  {
    parser_context_range contexts = parser_switch_traits::context_all (parser_switch);
    typedef typename boost::range_iterator<parser_context_range>::type context_iterator;
    for(context_iterator first = boost::begin (contexts), last = boost::end (contexts)
          ;first != last;++first)
    {
      boost::shared_ptr<context_type> c(new context_type (*first, causal_connector_lookupable, f));
      this->contexts.push_back (c);
    }

    typedef typename parser_switch_traits::media_range media_range;
    media_range medias = parser_switch_traits::media_all (parser_switch);
    typedef typename boost::range_iterator<media_range>::type media_iterator;
    for(media_iterator first = boost::begin (medias), last = boost::end (medias)
          ;first != last;++first)
      this->medias.push_back (media_type (*first, f));
    
  }

  typedef std::vector<boost::shared_ptr<context_type> > context_container;
  typedef boost::indirect_iterator<typename context_container::iterator> context_iterator;
  typedef std::vector<boost::shared_ptr<switch_type> > switch_container;
  typedef boost::indirect_iterator<typename switch_container::iterator> switch_iterator;
  typedef std::vector<media_type> media_container;
  typedef std::vector<switch_port_type> switch_port_container;
  struct composed_bind_rule_transform
  {
    typedef bind_rule_type result_type;
    template <typename T>
    result_type operator()(T o) const
    {
      return o;
    }
  };
  typedef boost::transform_iterator<composed_bind_rule_transform, parser_bind_rule_iterator> bind_rule_iterator;

  typedef boost::iterator_range<context_iterator> context_range;
  typedef boost::iterator_range<switch_iterator> switch_range;
  typedef boost::iterator_range<typename media_container::iterator> media_range;
  typedef boost::iterator_range<switch_port_container::iterator> switch_port_range;
  typedef boost::iterator_range<bind_rule_iterator> bind_rule_range;

  typedef typename parser_context_traits::identifier_type context_identifier_type;
  typedef typename parser_media_traits::identifier_type media_identifier_type;

  BOOST_MPL_ASSERT((boost::is_convertible<context_identifier_type
                                          , media_identifier_type>));
  BOOST_MPL_ASSERT((boost::is_convertible<media_identifier_type
                                          , context_identifier_type>));

  typedef composed::media_lookupable<media_range> media_lookupable;
  typedef composed::context_lookupable<context_range> context_lookupable;

  typedef context_identifier_type identifier_type;

  boost::optional<identifier_type> active_component;
  ParserSwitch parser_switch;
  context_container contexts;
  media_container medias;
  switch_container switches;
  switch_port_container switch_ports;
};

} }

namespace concept { namespace structure {

template <typename ParserSwitch, typename PresentationFactory, typename ParserConnectorBase>
struct switch_traits<gntl::structure::composed::switch_<ParserSwitch, PresentationFactory, ParserConnectorBase> >
{
  typedef boost::mpl::true_ is_switch;
  typedef gntl::structure::composed::switch_<ParserSwitch, PresentationFactory, ParserConnectorBase> switch_type;
  typedef typename unwrap_parameter<ParserSwitch>::type parser_switch_type;
  typedef concept::parser::switch_traits<parser_switch_type> parser_switch_traits;
  typedef typename parser_switch_traits::identifier_type identifier_type;
  typedef typename parser_switch_traits::refer_type refer_type;
  typedef typename switch_type::context_range context_range;
  typedef typename switch_type::switch_range switch_range;
  typedef typename switch_type::media_range media_range;
  typedef typename switch_type::switch_port_range switch_port_range;
  typedef typename switch_type::bind_rule_range bind_rule_range;
  typedef typename switch_type::context_lookupable context_lookupable;
  typedef typename switch_type::media_lookupable media_lookupable;
  struct switch_lookupable {};

  static identifier_type active_component(switch_type const& s)
  {
    return *s.active_component;
  }
  static void activate_component(switch_type& s, identifier_type id)
  {
    s.active_component = id;
  }
  static identifier_type identifier(switch_type const& s)
  {
    return parser_switch_traits::identifier(s.parser_switch);
  }
  static bool has_refer(switch_type const& s)
  {
    return parser_switch_traits::has_refer(s.parser_switch);
  }
  static refer_type refer(switch_type const& s)
  {
    return parser_switch_traits::refer(s.parser_switch);
  }
  static bool has_default_component(switch_type const& s)
  {
    return parser_switch_traits::has_default_component(s.parser_switch);
  }
  static identifier_type default_component(switch_type const& s)
  {
    return parser_switch_traits::default_component(s.parser_switch);
  }
  static bool is_presentation_occurring(switch_type const&s)
  {
    return !!s.active_component;
  }
  static bool is_presentation_sleeping(switch_type const&s)
  {
    return !s.active_component;
  }
  static bool is_presentation_paused(switch_type const&s);
  static switch_port_range switch_port_all(switch_type const& s);
  static switch_range switch_all(switch_type const& s);
  static media_range media_all(switch_type& s)
  {
    return media_range(s.medias.begin(), s.medias.end());
  }
  static context_range context_all(switch_type& s)
  {
    typedef typename switch_type::context_iterator context_iterator;
    return context_range(context_iterator(s.contexts.begin()), context_iterator(s.contexts.end()));
  }
  static bind_rule_range bind_rule_all(switch_type const& s)
  {
    typedef typename switch_type::parser_switch_traits parser_switch_traits;
    typedef typename switch_type::parser_bind_rule_range
      parser_bind_rule_range;
    parser_bind_rule_range bind_rules = parser_switch_traits::bind_rule_all(s.parser_switch);
    return bind_rule_range(boost::begin(bind_rules), boost::end(bind_rules));
  }
  static context_lookupable context_lookup(switch_type& s)
  {
    return context_lookupable(context_all(s));
  }
  static media_lookupable media_lookup(switch_type& s)
  {
    return media_lookupable(media_all(s));
  }
  static switch_lookupable switch_lookup(switch_type const& s);
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
