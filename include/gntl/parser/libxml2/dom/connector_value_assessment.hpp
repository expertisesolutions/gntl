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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_VALUE_ASSESSMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_VALUE_ASSESSMENT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/concept/parser/connector/connector_value_assessment.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_value_assessment
{
    connector_value_assessment (xml_node node)
        : node (node) {}

    typedef xml_string<> value_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_value_assessment_traits<gntl::parser::libxml2::dom
                                         ::connector_value_assessment>
{
  typedef boost::mpl::true_ is_connector_value_assessment;
  typedef gntl::parser::libxml2::dom::connector_value_assessment
    connector_value_assessment;
  typedef connector_value_assessment::value_type value_type;
  
  static value_type value(connector_value_assessment c)
  {
    return c.node["value"].value();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
