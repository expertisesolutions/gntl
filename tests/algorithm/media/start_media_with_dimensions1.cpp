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

#define BOOST_TEST_MODULE start_media_with_descriptor1
#include <boost/test/included/unit_test.hpp>

#include <gntl/algorithm/structure/media.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/region_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/document.hpp>
#include <gntl/structure/composed/descriptor.hpp>
#include <gntl/structure/composed/descriptor_lookupable.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/presentation.hpp>

namespace concept = gntl::concept;
namespace algorithm = gntl::algorithm;
namespace dom = gntl::parser::libxml2::dom;
namespace composed = gntl::structure::composed;

bool executor_start_run = false
    , executor_start_async_run = false;

struct executor
{
};

algorithm::structure::media::dimensions full = {0,0,1280,720,0};
algorithm::structure::media::dimensions region1 = {0,100,1280,620,0};

struct void_ {};

namespace gntl { namespace concept { namespace structure {
template <>
struct executor_traits< ::executor>
{
  typedef boost::mpl::true_ is_executor;
  typedef composed::descriptor<dom::descriptor, std::string> descriptor_type;
  typedef boost::mpl::vector1
  <void(::executor, gntl::parser::libxml2::dom::xml_string<>
        , gntl::algorithm::structure::media::dimensions)> start_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> stop_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> resume_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> pause_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> abort_function_overloads;
  typedef gntl::parser::libxml2::dom::xml_string<> component_identifier;
  typedef boost::posix_time::time_duration time_duration;
  typedef gntl::parser::libxml2::dom::color color_type;

  static void add_border (::executor, int, color_type) {}
  static void remove_border (::executor);

  static void start (::executor e, gntl::parser::libxml2::dom::xml_string<> source
                     , gntl::algorithm::structure::media::dimensions dimensions)
  {
    std::cout << "executor_start" << std::endl;
    executor_start_run = true;
    BOOST_CHECK_EQUAL (source, "source1");
    BOOST_CHECK_EQUAL (region1, dimensions);
    // BOOST_REQUIRE(!!descriptor);
    // typedef concept::structure::descriptor_traits<descriptor_type>
    //   descriptor_traits;
    // BOOST_CHECK_EQUAL (descriptor_traits::identifier (*descriptor), "descriptor1");
  }

  template <typename Source, typename Descriptor, typename Dimensions, typename Handler>
  static void async_start ( ::executor e, Source source
                           , boost::optional<Descriptor> descriptor
                           , Dimensions dimensions, Handler handler)
  {
    std::cout << "executor_start_async" << std::endl;
    executor_start_async_run = true;
    BOOST_CHECK_EQUAL (source, "source1");
    BOOST_CHECK_EQUAL (region1, dimensions);
    BOOST_REQUIRE(!!descriptor);
    typedef concept::structure::descriptor_traits<Descriptor> descriptor_traits;
    BOOST_CHECK_EQUAL (descriptor_traits::identifier (*descriptor), "descriptor1");
  }

  static void stop (::executor e) {}
  static void pause (::executor e);
  static void resume (::executor e);
  static void abort (::executor e);

  static void listen_time(::executor, component_identifier, component_identifier, time_duration, gntl::transition_type) {}
  static void listen_frame(::executor, component_identifier, component_identifier, int, gntl::transition_type) {}
  static void listen_npt(::executor, component_identifier, component_identifier, int, gntl::transition_type) {}
};
} } }

const char xml_media[]
  = "<media id=\"identifier\" descriptor=\"descriptor1\" src=\"source1\" />";
const char xml_descriptor_base[]
  = "<descriptorBase id=\"descriptor_base\">\n"
    "  <descriptor id=\"descriptor1\" region=\"region1\" />"
    "</descriptorBase>"
 ;
const char xml_region_base[]
  = "<regionBase id=\"region_base\">\n"
    "  <region id=\"region1\" top=\"100\" />"
    "</regionBase>"
 ;

template <typename T>
T const& as_const (T& x) { return x; }

void handler ()
{
    std::cout << "handler" << std::endl;
}

typedef composed::descriptor<dom::descriptor, std::string> descriptor_type;
typedef composed::presentation<executor, descriptor_type> presentation_type;

struct presentation_factory
{
  typedef presentation_type result_type;
  result_type operator()(std::string media, std::string context, descriptor_type d) const
  { 
    return result_type(executor(), d); 
  }
};

BOOST_AUTO_TEST_CASE (start_media_with_descriptor1)
{
    ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_media)));
    dom::xml_document xmldocument (xmldoc); // gets ownership
    ::xmlDocPtr xmldescriptordoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_descriptor_base)));
    dom::xml_document xmldescriptordocument (xmldescriptordoc); // gets ownership
    ::xmlDocPtr xmlregiondoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_region_base)));
    dom::xml_document xmlregiondocument (xmlregiondoc); // gets ownership

    typedef composed::media<dom::media, presentation_factory> media_type;
    media_type media (dom::media(xmldocument.root ()));
    typedef composed::context<dom::body_context_type<dom::xml_string<> >, presentation_factory
                              , dom::connector_base> context_type;
    typedef composed::document<dom::document, presentation_factory, std::string> document_type;
    typedef gntl::concept::structure::document_traits<document_type> document_traits;
    dom::descriptor_base descriptor_base (xmldescriptordocument.root ());
    dom::region_base region_base (xmlregiondocument.root ());

    context_type context(dom::body_context_type<std::string>
                         (dom::xml_node()
                          , static_cast<xmlChar const*>(static_cast<void const*>("dummy"))));
    document_type document;

    descriptor_type descriptor = *descriptor_base.begin();

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));
    typedef concept::structure::media_traits<media_type> media_traits;

    boost::optional<document_traits::component_identifier> interface_;
    algorithm::structure::media::start (gntl::ref (media), gntl::ref(context)
                                        , interface_
                                        , descriptor_type()
                                        , gntl::ref (document), full);

    BOOST_REQUIRE(media_traits::has_presentation(media, descriptor));
    presentation_type presentation = media_traits::get_presentation(media, descriptor);
    typedef gntl::concept::structure::presentation_traits<presentation_type> presentation_traits;
    BOOST_CHECK(presentation_traits::is_occurring(presentation));
    presentation_traits::stop(presentation);
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));

    BOOST_CHECK(presentation_traits::is_occurring(presentation));

    typedef concept::structure::document_traits<document_type> document_traits;
    BOOST_CHECK_EQUAL (document_traits::pending_events (document), 2u);

    BOOST_CHECK_EQUAL (::executor_start_run, true);
    BOOST_CHECK_EQUAL (::executor_start_async_run, true);
}
