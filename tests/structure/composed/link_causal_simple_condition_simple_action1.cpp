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

#define BOOST_TEST_MODULE link_causal_simple_condition_simple_action11
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
    " <bind role=\"onBegin\" component=\"somecomponent\" />\n"
    " <bind role=\"start\" component=\"othercomponent\" />\n"
    "</link>\n"
    ;

const char connector_xml[]
  = "<causalConnector id=\"connector1\">\n"
    "  <simpleCondition role=\"onBegin\" delay=\"5s\" eventType=\"presentation\""
    "                   key=\"ENTER\" transition=\"starts\" min=\"1\" max=\"1\" "
    "                   qualifier=\"seq\" />\n"
    "  <simpleAction role=\"start\" delay=\"10s\" eventType=\"presentation\""
    "                actionType=\"start\" value=\"value1\" min=\"1\" max=\"2\""
    "                qualifier=\"seq\" repeat=\"5\" repeatDelay=\"10s\" duration=\"50s\""
    "                by=\"2\" />\n"
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

BOOST_AUTO_TEST_CASE (link_causal_simple_condition_simple_action11)
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

    // typedef gntl::structure::composed::compound_condition
    //   <gntl::parser::libxml2::dom::link, gntl::parser::libxml2::dom::connector_compound_condition>
    //   compound_condition_type;

    BOOST_MPL_ASSERT((boost::mpl::equal_to
                      <boost::mpl::size
                        <link_condition_expr_traits::condition_list_type>::type
                      , boost::mpl::int_<2> >));
    BOOST_MPL_ASSERT((boost::mpl::equal<boost::mpl::vector2
                                        <bounded_simple_condition_type
                                        , compound_condition_type>
                                        , link_condition_expr_traits::condition_list_type>));

    BOOST_REQUIRE(link_condition_expr_traits::is_type<bounded_simple_condition_type>(condition));
    bounded_simple_condition_type
      simple_cond = link_condition_expr_traits
      ::get<bounded_simple_condition_type>(condition);

    typedef concept::structure::bounded_simple_condition_traits
      <bounded_simple_condition_type> bounded_simple_condition_traits;
    
    BOOST_CHECK_EQUAL(bounded_simple_condition_traits::role(simple_cond), "onBegin");
    BOOST_REQUIRE(bounded_simple_condition_traits::has_event_type(simple_cond));
    BOOST_CHECK_EQUAL(bounded_simple_condition_traits::event_type(simple_cond), gntl::event_enum::presentation);
    BOOST_REQUIRE(bounded_simple_condition_traits::has_transition(simple_cond));
    BOOST_CHECK_EQUAL(bounded_simple_condition_traits::transition(simple_cond), gntl::transition_enum::starts);
    BOOST_REQUIRE(bounded_simple_condition_traits::has_min(simple_cond));
    BOOST_CHECK_EQUAL((bounded_simple_condition_traits::min)(simple_cond), 1u);
    BOOST_REQUIRE(bounded_simple_condition_traits::has_max(simple_cond));
    BOOST_CHECK_EQUAL((bounded_simple_condition_traits::max)(simple_cond), 1u);
    BOOST_REQUIRE(bounded_simple_condition_traits::has_qualifier(simple_cond));
    BOOST_CHECK_EQUAL(bounded_simple_condition_traits::qualifier(simple_cond), "seq");

    {
      typedef bounded_simple_condition_traits::component_range
        component_range;

      component_range components = bounded_simple_condition_traits
        ::components(simple_cond);

      typedef boost::range_value<component_range>::type bound_component;
      typedef concept::structure::condition_bound_component_traits
        <bound_component> bound_component_traits;

      BOOST_REQUIRE_EQUAL(boost::distance(components), 1);
      bound_component component = *boost::begin(components);
      BOOST_CHECK_EQUAL(bound_component_traits::component(component), "somecomponent");
      BOOST_CHECK(!bound_component_traits::has_interface(component));
      BOOST_CHECK(!bound_component_traits::has_descriptor(component));
      BOOST_REQUIRE(bound_component_traits::has_delay(component));
      BOOST_CHECK_EQUAL(bound_component_traits::delay(component)
                        , boost::posix_time::seconds(5));
      BOOST_REQUIRE(bound_component_traits::has_key(component));
      BOOST_CHECK_EQUAL(bound_component_traits::key(component), "ENTER");
    }

    typedef link_traits::action_expression_type action_expression_type;
    action_expression_type action_expression
      = link_traits::action_expression (link);

    typedef concept::structure::action_expression_traits
      <action_expression_type> action_expression_traits;
    typedef action_expression_traits
      ::bound_simple_action bound_simple_action;

    BOOST_REQUIRE(action_expression_traits::is_type<bound_simple_action>(action_expression));
    
    bound_simple_action simple_action
      = action_expression_traits::get<bound_simple_action>(action_expression);

    typedef concept::structure::bound_simple_action_traits
      <bound_simple_action> simple_action_traits;
    
    BOOST_CHECK_EQUAL(simple_action_traits::role (simple_action), "start");
    BOOST_REQUIRE(simple_action_traits::has_event_type (simple_action));
    BOOST_CHECK_EQUAL(simple_action_traits::event_type (simple_action), gntl::event_enum::presentation);
    BOOST_REQUIRE(simple_action_traits::has_action_type (simple_action));
    BOOST_CHECK_EQUAL(simple_action_traits::action_type (simple_action), gntl::action_enum::start);
    BOOST_REQUIRE(simple_action_traits::has_min (simple_action));
    BOOST_CHECK_EQUAL((simple_action_traits::min) (simple_action), 1u);
    BOOST_REQUIRE(simple_action_traits::has_max (simple_action));
    BOOST_CHECK_EQUAL((simple_action_traits::max) (simple_action), 2u);

    typedef simple_action_traits::component_range component_range;
    component_range
      components = simple_action_traits::component_all(simple_action);
    BOOST_REQUIRE_EQUAL(boost::distance(components), 1);

    typedef boost::range_value<component_range>::type component_type;
    
    typedef gntl::concept::structure::action_bound_component_traits
      <component_type>
      action_bound_component_traits;

    component_type component = *boost::begin(components);

    BOOST_CHECK_EQUAL(action_bound_component_traits::component (component), "othercomponent");
    BOOST_CHECK(!action_bound_component_traits::has_interface (component));
    BOOST_CHECK(!action_bound_component_traits::has_descriptor (component));
    BOOST_REQUIRE(action_bound_component_traits::has_delay (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::delay (component)
                      , boost::posix_time::seconds(10));
    BOOST_REQUIRE(action_bound_component_traits::has_value (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::value (component), "value1");
    BOOST_REQUIRE(action_bound_component_traits::has_qualifier (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::qualifier (component), "seq");
    BOOST_REQUIRE(action_bound_component_traits::has_repeat (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::repeat (component), "5");
    BOOST_REQUIRE(action_bound_component_traits::has_repeat_delay (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::repeat_delay (component), "10s");
    BOOST_REQUIRE(action_bound_component_traits::has_duration (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::duration (component), "50s");
    BOOST_REQUIRE(action_bound_component_traits::has_by (component));
    BOOST_CHECK_EQUAL(action_bound_component_traits::by (component), "2");
  }
  ::xmlCleanupParser ();
}
