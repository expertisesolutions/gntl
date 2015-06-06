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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ATTRIBUTE_ASSESSMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ATTRIBUTE_ASSESSMENT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#include <gntl/concept/parser/connector/connector_attribute_assessment.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_attribute_assessment
{
    connector_attribute_assessment (xml_node node)
        : node (node) {}

    typedef xml_string<> role_type;
    typedef xml_string<> event_type_type;
    typedef xml_string<> key_type;
    typedef xml_string<> attribute_type_type;
    typedef std::size_t offset_type;

    xml_node node;
};


} } }

namespace concept { namespace parser {

template <>
struct connector_attribute_assessment_traits<gntl::parser::libxml2::dom
                                             ::connector_attribute_assessment>
{
  typedef boost::mpl::true_ is_connector_attribute_assessment;
  typedef gntl::parser::libxml2::dom::connector_attribute_assessment
    connector_attribute_assessment;
  typedef connector_attribute_assessment::role_type role_type;
  typedef connector_attribute_assessment::event_type_type event_type_type;
  typedef connector_attribute_assessment::key_type key_type;
  typedef connector_attribute_assessment::attribute_type_type attribute_type_type;
  typedef connector_attribute_assessment::offset_type offset_type;

  static role_type role (connector_attribute_assessment c)
  {
    assert (!!c.node["role"]);
    return c.node["role"].value ();
  }

  static bool has_event_type (connector_attribute_assessment c)
  {
    return c.node["eventType"];
  }

  static event_type_type event_type (connector_attribute_assessment c)
  {
    return c.node["eventType"].value ();
  }

  static bool has_key (connector_attribute_assessment c)
  {
    return c.node["key"];
  }

  static key_type key (connector_attribute_assessment c)
  {
    return c.node["key"].value ();
  }

  static bool has_attribute_type (connector_attribute_assessment c)
  {
    return c.node["attributeType"];
  }

  static attribute_type_type attribute_type (connector_attribute_assessment c)
  {
    return c.node["attributeType"].value ();
  }

  static bool has_offset (connector_attribute_assessment c)
  {
    return c.node["offset"]
      && gntl::parser::libxml2::dom::uint_parser (c.node["offset"].value());
  }

  static std::size_t offset (connector_attribute_assessment c)
  {
    return *gntl::parser::libxml2::dom
      ::uint_parser (c.node["offset"].value ());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
