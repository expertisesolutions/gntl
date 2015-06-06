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

#ifndef GNTL_STRUCTURE_COMPOSED_LINK_HPP
#define GNTL_STRUCTURE_COMPOSED_LINK_HPP

#include <gntl/concept/structure/link.hpp>
#include <gntl/concept/parser/link/link.hpp>
#include <gntl/concept/parser/connector/causal_connector.hpp>
#include <gntl/structure/composed/condition/condition_expression.hpp>
#include <gntl/structure/composed/action/action_expression.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

namespace mpl = boost::mpl;

template <typename LinkParser, typename CausalConnectorParser>
struct link
{
  link(LinkParser link_parser, CausalConnectorParser
       causal_connector)
    : link_parser(link_parser), causal_connector(causal_connector)
  {
    role_conditions.reset(new std::map<role_type, bool>);
  }

  typedef typename boost::unwrap_reference<LinkParser>::type link_type;
  typedef concept::parser::link_traits<link_type> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_value_type;
  typedef typename boost::unwrap_reference<bind_value_type>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;
  boost::shared_ptr<std::map<role_type, bool> > role_conditions;
  LinkParser link_parser;
  CausalConnectorParser causal_connector;
};

} }

namespace concept { namespace structure {

template <typename LinkParser, typename CausalConnectorParser>
struct link_traits<gntl::structure::composed
                   ::link<LinkParser, CausalConnectorParser> >
{
  typedef boost::mpl::true_ is_link;
  typedef gntl::structure::composed::link<LinkParser, CausalConnectorParser>
    link_type;
  typedef concept::parser::link_traits<LinkParser> link_parser_traits;
  typedef concept::parser::causal_connector_traits<CausalConnectorParser>
    connector_traits;
  typedef typename link_parser_traits::identifier_type identifier_type;
  typedef gntl::structure::composed::condition_expression
    <LinkParser, CausalConnectorParser>
    condition_expression_type;
  typedef gntl::structure::composed::action_expression
    <LinkParser, CausalConnectorParser>
    action_expression_type;

  static identifier_type identifier(link_type const& l)
  {
    return link_parser_traits::identifier(l.link_parser);
  }

  static bool has_identifier(link_type const& l)
  {
    return link_parser_traits::has_identifier(l.link_parser);
  }

  static condition_expression_type condition_expression(link_type& l)
  {
    return condition_expression_type (l.link_parser, l.causal_connector
                                      , l.role_conditions.get());
  }

  static action_expression_type action_expression(link_type const& l)
  {
    return action_expression_type (l.link_parser, l.causal_connector);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
