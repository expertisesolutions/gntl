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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ASSESSMENT_STATEMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_ASSESSMENT_STATEMENT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/connector_attribute_assessment.hpp>
#include <gntl/parser/libxml2/dom/connector_value_assessment.hpp>
#include <gntl/concept/parser/connector/connector_assessment_statement.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/invalid_ncl_error.hpp>

#include <boost/utility.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_assessment_statement
{
    connector_assessment_statement (xml_node node)
        : node (node) {}

    typedef xml_string<> comparator_type;
    typedef connector_attribute_assessment attribute_assessment_type;
    typedef connector_value_assessment value_assessment_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct connector_assessment_statement_traits<gntl::parser::libxml2::dom
                                             ::connector_assessment_statement>
{
  typedef boost::mpl::true_ is_connector_assessment_statement;
  typedef gntl::parser::libxml2::dom::connector_assessment_statement
    connector_assessment_statement;
  typedef connector_assessment_statement::comparator_type comparator_type;
  typedef connector_assessment_statement::attribute_assessment_type attribute_assessment_type;
  typedef connector_assessment_statement::value_assessment_type value_assessment_type;

  static comparator_type comparator(connector_assessment_statement c)
  {
    return c.node["comparator"].value ();
  }
  static attribute_assessment_type first (connector_assessment_statement c)
  {
    using namespace gntl::parser::libxml2::dom;
    xml_node n = c.node.begin ();
    xml_node end (0);
    while(n != end
          && (n.type () != XML_ELEMENT_NODE
              || n.name () != "attributeAssessment"))
    {
        ++n;
    }
    if(n == end)
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("No attributeAssessment in assessmentStatement")));
    return n;
  }

  template <typename T>
  struct tag {};

  static gntl::parser::libxml2::dom::xml_node
    return_second(connector_assessment_statement c)
  {
    gntl::parser::libxml2::dom::xml_node n = c.node.begin ();
    gntl::parser::libxml2::dom::xml_node end (0);
    while(n != end
          && (n.type () != XML_ELEMENT_NODE
              || n.name () != "attributeAssessment"))
    {
        ++n;
    }
    if(n != end)
        ++n;
    while(n != end
          && n.type() != XML_ELEMENT_NODE)
      ++n;
    return n;
  }

  static bool is_second_aux(connector_assessment_statement c
                        , tag<attribute_assessment_type>)
  {
    gntl::parser::libxml2::dom::xml_node n = return_second(c);
    return (n.name() == "attributeAssessment");
  }

  static bool is_second_aux(connector_assessment_statement c
                        , tag<value_assessment_type>)
  {
    gntl::parser::libxml2::dom::xml_node n = return_second(c);
    return (n.name() == "valueAssessment");
  }

  template <typename T>
  static bool is_second(connector_assessment_statement c)
  {
    return is_second_aux(c, tag<T>());
  }

  template <typename T>
  static T second (connector_assessment_statement c)
  {
    return return_second(c);
  }
};

template <>
struct connector_condition_traits<gntl::parser::libxml2::dom::connector_assessment_statement>
{
  typedef boost::mpl::true_ is_connector_condition;
  typedef assessment_statement_tag category_tag;
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
