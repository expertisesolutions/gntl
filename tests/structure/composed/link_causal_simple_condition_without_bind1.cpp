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

#define BOOST_TEST_MODULE link_causal_simple_condition_without_bind1
#include <boost/test/included/unit_test.hpp>

#include <gntl/structure/composed/link.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/causal_connector.hpp>

#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/find_if.hpp>

namespace parser = gntl::parser;
namespace concept = gntl::concept;
namespace composed = gntl::structure::composed;

const char link_xml[]
  = "<link id=\"link1\" xconnector=\"connector1\">\n"
    "</link>\n"
    ;

const char connector_xml[]
  = "<causalConnector id=\"connector1\">\n"
    "  <simpleCondition role=\"start\" delay=\"5s\" eventType=\"presentation\""
    "                   key=\"ENTER\" transition=\"trans1\" min=\"1\" max=\"1\" "
    "                   qualifier=\"seq\" />\n"
    "</causalConnector>\n"
    ;

template <typename T, typename Tag>
struct predicate
{
  typedef gntl::concept::structure::condition_traits
  <T> traits;
  typedef typename
    boost::is_convertible
    <typename traits::category_tag
     , Tag>::type
    type;
};

BOOST_AUTO_TEST_CASE (link_test1)
{
  ::xmlInitParser ();
  {  
    ::xmlDocPtr xml_link_doc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(::link_xml)));
    parser::libxml2::dom::xml_document link_document(xml_link_doc); // gets ownership
    parser::libxml2::dom::link parser_link(link_document.root());

    ::xmlDocPtr xml_connector_doc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(::connector_xml)));
    parser::libxml2::dom::xml_document connector_document(xml_connector_doc); // gets ownership
    parser::libxml2::dom::causal_connector parser_connector(connector_document.root());
    
    GNTL_CONCEPT_ASSERT((concept::parser::CausalConnector
                                         <parser::libxml2::dom::causal_connector>));
    GNTL_CONCEPT_ASSERT((concept::parser::Link
                                         <parser::libxml2::dom::link>));

    typedef composed::link<parser::libxml2::dom::link
                           , parser::libxml2::dom::causal_connector>
      link_type;

    GNTL_CONCEPT_ASSERT((concept::structure::Link<link_type>));

    link_type link(parser_link, parser_connector);

    typedef concept::structure::link_traits<link_type> link_traits;

    BOOST_REQUIRE(link_traits::has_identifier(link));
    typedef link_traits::condition_expression_type condition_type;
    condition_type condition = link_traits::condition_expression (link);

    typedef gntl::concept::structure::condition_expression_traits
      <condition_type> link_condition_expr_traits;

    typedef 
      boost::mpl::deref
      <boost::mpl::find_if
      <link_condition_expr_traits::condition_list_type
      , predicate<boost::mpl::_, gntl::concept::structure::simple_condition_tag>
      >::type>::type
      bounded_simple_condition_type;

    typedef 
      boost::mpl::deref
      <boost::mpl::find_if
      <link_condition_expr_traits::condition_list_type
      , predicate<boost::mpl::_, gntl::concept::structure::compound_condition_tag>
      >::type>::type
      compound_condition_type;

    BOOST_MPL_ASSERT((boost::mpl::equal_to
                      <boost::mpl::size
                        <link_condition_expr_traits::condition_list_type>::type
                      , boost::mpl::int_<2> >));
    BOOST_MPL_ASSERT((boost::mpl::equal<boost::mpl::vector2
                                        <bounded_simple_condition_type
                                        , compound_condition_type>
                                        , link_condition_expr_traits::condition_list_type>));

    BOOST_REQUIRE(link_condition_expr_traits::is_type<bounded_simple_condition_type>(condition));

    BOOST_CHECK_THROW((link_condition_expr_traits::get
                       <bounded_simple_condition_type>(condition))
                      , gntl::invalid_ncl_error);
  }
  ::xmlCleanupParser ();
}
