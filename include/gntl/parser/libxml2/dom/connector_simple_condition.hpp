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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_SIMPLE_CONDITION_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_SIMPLE_CONDITION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/time_duration_parser.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#include <gntl/concept/parser/connector/connector_simple_condition.hpp>
#include <gntl/concept/parser/connector/connector_condition.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/event_enum.hpp>
#include <gntl/transition_enum.hpp>
#include <gntl/invalid_ncl_error.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_simple_condition
{
    connector_simple_condition (xml_node node)
        : node (node) {}

    typedef xml_string<> role_type;
    typedef boost::posix_time::time_duration delay_type;
    typedef gntl::event_type event_type_type;
    typedef xml_string<> key_type;
    typedef gntl::transition_type transition_type;
    typedef boost::optional<std::size_t> min_type;
    typedef boost::optional<std::size_t> max_type;
    typedef xml_string<> qualifier_type;
    
    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_simple_condition_traits<gntl::parser::libxml2::dom
                                         ::connector_simple_condition>
{
  typedef boost::mpl::true_ is_connector_simple_condition;
  typedef gntl::parser::libxml2::dom::connector_simple_condition
    connector_simple_condition;
  typedef connector_simple_condition::role_type role_type;
  typedef connector_simple_condition::delay_type delay_type;
  typedef connector_simple_condition::event_type_type event_type_type;
  typedef connector_simple_condition::key_type key_type;
  typedef connector_simple_condition::transition_type transition_type;
  typedef connector_simple_condition::min_type min_type;
  typedef connector_simple_condition::max_type max_type;
  typedef connector_simple_condition::qualifier_type qualifier_type;

  static role_type role (connector_simple_condition c)
  {
    return c.node["role"].value ();
  }

  static bool has_delay (connector_simple_condition c)
  {
    return c.node["delay"];
  }

  static delay_type delay (connector_simple_condition c)
  {
    return time_duration_parser (c.node["delay"].value ());
  }

  static bool has_key (connector_simple_condition c)
  {
    return c.node["key"];
  }

  static key_type key (connector_simple_condition c)
  {
    return c.node["key"].value ();
  }

  static bool has_event_type (connector_simple_condition c)
  {
    return c.node["eventType"];
  }

  static event_type_type event_type (connector_simple_condition c)
  {
    typedef gntl::parser::libxml2::dom::xml_string<> xml_string;
    if(c.node["eventType"].value() == "presentation")
      return gntl::event_enum::presentation;
    else if(c.node["eventType"].value() == "selection")
      return gntl::event_enum::selection;
    else if(c.node["eventType"].value() == "attribution")
      return gntl::event_enum::attribution;
    else
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("Invalid event type name in eventType attribute for simpleCondition"))
                               (error::event_type<xml_string>::type
                                (c.node["eventType"].value()))
                               (error::xml_attribute<const char*>::type("eventType")));
  }

  static bool has_transition (connector_simple_condition c)
  {
    return c.node["transition"];
  }

  static transition_type transition (connector_simple_condition c)
  {
    typedef gntl::parser::libxml2::dom::xml_string<> xml_string;
    if(c.node["transition"].value () == "starts")
      return gntl::transition_enum::starts;
    else if(c.node["transition"].value () == "stops")
      return gntl::transition_enum::stops;
    else if(c.node["transition"].value () == "aborts")
      return gntl::transition_enum::aborts;
    else if(c.node["transition"].value () == "pauses")
      return gntl::transition_enum::pauses;
    else if(c.node["transition"].value () == "resumes")
      return gntl::transition_enum::resumes;
    else
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("Invalid transition name in transition attribute for simpleCondition"))
                               (error::event_type<xml_string>::type
                                (c.node["transition"].value()))
                               (error::xml_attribute<const char*>::type("eventType")));
  }

  static bool has_min (connector_simple_condition c)
  {
    return c.node["min"]
      && (c.node["min"].value() == "unbounded"
          || uint_parser (c.node["min"].value()));
  }

  static min_type (min) (connector_simple_condition c)
  {
    if(c.node["min"].value() != "unbounded")
      return *uint_parser (c.node["min"].value ());
    else
      return boost::none;
  }

  static bool has_max (connector_simple_condition c)
  {
    return c.node["max"]
      && (c.node["max"].value() == "unbounded"
          || uint_parser (c.node["max"].value()));
  }

  static max_type (max) (connector_simple_condition c)
  {
    if(c.node["max"].value () != "unbounded")
      return *uint_parser (c.node["max"].value ());
    else
      return boost::none;
  }

  static bool has_qualifier (connector_simple_condition c)
  {
    return c.node["qualifier"];
  }

  static qualifier_type qualifier (connector_simple_condition c)
  {
    return c.node["qualifier"].value ();
  }
};

template <>
struct connector_condition_traits<gntl::parser::libxml2::dom
                                  ::connector_simple_condition>
{
  typedef boost::mpl::true_ is_connector_condition;
  typedef simple_condition_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
