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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_SIMPLE_ACTION_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_SIMPLE_ACTION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/concept/parser/connector/connector_simple_action.hpp>
#include <gntl/action_enum.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_simple_action
{
  connector_simple_action(xml_node node)
    : node(node) {}

  xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_simple_action_traits<gntl::parser::libxml2::dom::connector_simple_action>
{
  typedef boost::mpl::true_ is_connector_simple_action;
  typedef gntl::parser::libxml2::dom::connector_simple_action
    connector_simple_action;

  typedef gntl::parser::libxml2::dom::xml_string<> string_type;
  typedef string_type role_type;
  typedef boost::posix_time::time_duration delay_type;
  typedef gntl::event_type event_type_type;
  typedef gntl::action_type action_type_type;
  typedef boost::optional<std::size_t> min_type;
  typedef boost::optional<std::size_t> max_type;
  typedef string_type qualifier_type;
  typedef string_type repeat_type;
  typedef string_type repeat_delay_type;
  typedef string_type duration_type;
  typedef string_type by_type;

  static bool has_delay(connector_simple_action a)
  {
    return a.node["delay"];
  }
  static bool has_event_type(connector_simple_action a)
  {
    return a.node["eventType"];
  }
  static bool has_action_type(connector_simple_action a)
  {
    return a.node["actionType"];
  }
  static bool has_value(connector_simple_action a)
  {
    return a.node["value"];
  }
  static bool has_min(connector_simple_action a)
  {
    return a.node["min"]
      && (a.node["min"].value() == "unbounded"
          || uint_parser (a.node["min"].value()));
  }
  static bool has_max(connector_simple_action a)
  {
    return a.node["max"]
      && (a.node["max"].value() == "unbounded"
          || uint_parser (a.node["max"].value()));
  }
  static bool has_qualifier(connector_simple_action a)
  {
    return a.node["qualifier"];
  }
  static bool has_repeat(connector_simple_action a)
  {
    return a.node["repeat"];
  }
  static bool has_repeat_delay(connector_simple_action a)
  {
    return a.node["repeatDelay"];
  }
  static bool has_duration(connector_simple_action a)
  {
    return a.node["duration"];
  }
  static bool has_by(connector_simple_action a)
  {
    return a.node["by"];
  }

  static role_type role(connector_simple_action a)
  {
    assert(!!a.node["role"]);
    return a.node["role"].value();
  }
  static delay_type delay(connector_simple_action a)
  {
    return time_duration_parser (a.node["delay"].value ());
  }
  static event_type_type event_type(connector_simple_action a)
  {
    typedef gntl::parser::libxml2::dom::xml_string<> xml_string;
    if(a.node["eventType"].value() == "presentation")
      return gntl::event_enum::presentation;
    else if(a.node["eventType"].value() == "selection")
      return gntl::event_enum::selection;
    else if(a.node["eventType"].value() == "attribution")
      return gntl::event_enum::attribution;
    else
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("Invalid event type name in eventType attribute for simpleAction"))
                               (error::event_type<xml_string>::type
                                (a.node["eventType"].value()))
                               (error::xml_attribute<const char*>::type("eventType")));
  }
  static action_type_type action_type(connector_simple_action a)
  {
    typedef gntl::parser::libxml2::dom::xml_string<> xml_string;
    if(a.node["actionType"].value() == "start")
      return gntl::action_enum::start;
    else if(a.node["actionType"].value() == "stop")
      return gntl::action_enum::stop;
    else if(a.node["actionType"].value() == "abort")
      return gntl::action_enum::abort;
    else if(a.node["actionType"].value() == "pause")
      return gntl::action_enum::pause;
    else if(a.node["actionType"].value() == "resume")
      return gntl::action_enum::resume;
    else
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("Invalid action type name in actionType attribute for simpleAction"))
                               (error::event_type<xml_string>::type
                                (a.node["actionType"].value()))
                               (error::xml_attribute<const char*>::type("actionType")));
  }
  static string_type value(connector_simple_action a)
  {
    return a.node["value"].value();
  }
  static min_type (min)(connector_simple_action a)
  {
    if(a.node["min"].value() != "unbounded")
      return *uint_parser (a.node["min"].value ());
    else
      return boost::none;
  }
  static max_type (max)(connector_simple_action a)
  {
    if(a.node["max"].value() != "unbounded")
      return *uint_parser (a.node["max"].value ());
    else
      return boost::none;
  }
  static qualifier_type qualifier(connector_simple_action a)
  {
    return a.node["qualifier"].value ();
  }
  static repeat_type repeat(connector_simple_action a)
  {
    return a.node["repeat"].value ();
  }
  static repeat_delay_type repeat_delay(connector_simple_action a)
  {
    return a.node["repeatDelay"].value ();
  }
  static duration_type duration(connector_simple_action a)
  {
    return a.node["duration"].value ();
  }
  static by_type by(connector_simple_action a)
  {
    return a.node["by"].value ();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
