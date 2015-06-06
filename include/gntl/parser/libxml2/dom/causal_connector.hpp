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

#ifndef GNTL_PARSER_LIBXML2_DOM_CAUSAL_CONNECTOR_HPP
#define GNTL_PARSER_LIBXML2_DOM_CAUSAL_CONNECTOR_HPP

#include <gntl/parser/libxml2/dom/causal_condition_expression.hpp>
#include <gntl/parser/libxml2/dom/connector_action.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_action_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_connector_parameter_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_simple_condition_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_compound_condition_predicate.hpp>
#include <gntl/concept/parser/connector/causal_connector.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct causal_connector
{
    causal_connector (xml_node node)
        : node (node)
    {
      internal_condition_iterator first (node.begin())
        , last (node.end());
      if(first == last)
        GNTL_UNWIND_ERROR(gntl::invalid_ncl_error());
      else
        condition = *first;
    }

    struct condition_predicate
    {
      typedef bool result_type;
      result_type operator()(xml_node& node) const
      {
        return xml_simple_condition_predicate()(node) || xml_compound_condition_predicate()(node);
      }
    };

    typedef xml_string<> identifier_type;
    typedef causal_condition_expression condition_type;
    typedef connector_action action_type;
    struct connector_parameter_type {};
    typedef xml_element_node_iterator<condition_type, condition_predicate> internal_condition_iterator;
    typedef xml_element_node_iterator<action_type, xml_action_predicate> action_iterator;
    typedef xml_element_node_iterator<connector_parameter_type
                                      , xml_connector_parameter_predicate> connector_parameter_iterator;

    condition_type condition;
    xml_node node;
};

inline causal_connector::connector_parameter_iterator connector_parameter_begin (causal_connector c)
{
    return causal_connector::connector_parameter_iterator (c.node.begin ());
}

inline causal_connector::connector_parameter_iterator connector_parameter_end (causal_connector c)
{
    return causal_connector::connector_parameter_iterator (c.node.end ());
}

} } }

namespace concept { namespace parser {

template <>
struct causal_connector_traits<gntl::parser::libxml2::dom
                               ::causal_connector>
{
  typedef boost::mpl::true_ is_causal_connector;
  typedef gntl::parser::libxml2::dom::causal_connector
    causal_connector;
  typedef causal_connector::identifier_type identifier_type;
  typedef causal_connector::condition_type condition_type;
  typedef causal_connector::action_type action_type;
  typedef causal_connector::connector_parameter_type connector_parameter_type;
  typedef causal_connector::connector_parameter_iterator connector_parameter_iterator;

  static identifier_type identifier (causal_connector c)
  {
    return c.node["id"].value();
  }
  static condition_type condition (causal_connector c)
  {
    return c.condition;
  }
  static action_type action (causal_connector c)
  {
    return *causal_connector::action_iterator(c.node.begin());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
