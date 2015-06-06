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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_BASE_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_BASE_HPP

#include <gntl/concept/parser/connector/connector_base.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/import_base.hpp>
#include <gntl/parser/libxml2/dom/causal_connector.hpp>
#include <gntl/parser/libxml2/dom/xml_import_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_causal_connector_predicate.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_base
{
    connector_base (xml_node node = xml_node())
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef dom::causal_connector causal_connector_type;
    typedef xml_element_node_iterator<causal_connector_type
                                      , xml_causal_connector_predicate> causal_connector_iterator;

    typedef import_base import_base_type;
    typedef xml_element_node_iterator<import_base, xml_import_base_predicate> import_base_iterator;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_base_traits<gntl::parser::libxml2::dom
                             ::connector_base>
{
  typedef boost::mpl::true_ is_connector_base;
  typedef gntl::parser::libxml2::dom::connector_base connector_base;
  typedef connector_base::identifier_type identifier_type;
  typedef boost::iterator_range<connector_base::causal_connector_iterator>
    causal_connector_range;
  typedef connector_base::import_base_iterator import_base_iterator;
  typedef boost::iterator_range<import_base_iterator> import_base_range;
  
  static identifier_type identifier(connector_base c)
  {
    return c.node["id"].value();
  }
  static bool has_identifier(connector_base c)
  {
    return c.node["id"];
  }
  static causal_connector_range causal_connector_all(connector_base c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return causal_connector_range(c.node.begin(), c.node.end());
    else
      return causal_connector_range(end, end);
  }
  static import_base_range import_base_all(connector_base c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return import_base_range(c.node.begin(), c.node.end());
    else
      return import_base_range(end, end);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
