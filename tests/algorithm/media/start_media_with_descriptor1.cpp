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

#include <gntl/algorithm/structure/media/start_normal_action.hpp>
#include <gntl/algorithm/structure/media/start.ipp>
#include <gntl/algorithm/structure/media/start_action_traits.ipp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
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

algorithm::structure::media::dimensions full = {0, 0, 1280, 720, 0};

struct void_ {};

namespace gntl { namespace concept { namespace structure {
template <>
struct executor_traits< ::executor>
{
  typedef boost::mpl::true_ is_executor;
  typedef boost::mpl::vector1
  <void(::executor, gntl::parser::libxml2::dom::xml_string<>
        , boost::optional<std::string> interface_
        , gntl::algorithm::structure::media::dimensions dimensions
        , dom::xml_string<> media)> start_function_overloads;
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
                     , boost::optional<std::string> interface_
                     , gntl::algorithm::structure::media::dimensions dimensions
                     , dom::xml_string<> media)
  {
    std::cout << "executor_start" << std::endl;
    executor_start_run = true;
    BOOST_CHECK_EQUAL (source, "source1");
    BOOST_CHECK_EQUAL(full, dimensions);
  }

  template <typename Source, typename Descriptor, typename Dimensions, typename Handler>
  static void async_start (::executor e, Source source, boost::optional<Descriptor> descriptor
                             , Dimensions dimensions, Handler handler)
  {
    std::cout << "executor_start_async" << std::endl;
    executor_start_async_run = true;
    BOOST_CHECK_EQUAL (source, "source1");
    BOOST_CHECK_EQUAL (full, dimensions);
    BOOST_REQUIRE(!!descriptor);
    typedef concept::parser::descriptor_traits<Descriptor> descriptor_traits;
    //BOOST_CHECK_EQUAL (descriptor_traits::identifier (*descriptor), "descriptor1");
  }

  static void stop (::executor e) {}
  static void pause (::executor e);
  static void resume (::executor e);
  static void abort (::executor e);
  static void start_area (::executor e, component_identifier) { std::abort(); }

  static void area_time_begin(::executor e, component_identifier, time_duration) { std::abort(); }
  static void area_time_end(::executor e, component_identifier, time_duration) { std::abort(); }
  static void area_time_begin_end(::executor e, component_identifier, time_duration, time_duration) { std::abort(); }
  static void area_frame_begin(::executor e, component_identifier, unsigned int) { std::abort(); }
  static void area_frame_end(::executor e, component_identifier, unsigned int) { std::abort(); }
  static void area_frame_begin_end(::executor e, component_identifier, unsigned int, unsigned int) { std::abort(); }
  static void area_npt_begin(::executor e, component_identifier, int) { std::abort(); }
  static void area_npt_end(::executor e, component_identifier, int) { std::abort(); }
  static void area_npt_begin_end(::executor e, component_identifier, int, int) { std::abort(); }
  static void explicit_duration(::executor, time_duration) { std::abort(); }
  static bool start_set_property(::executor, std::string, std::string);
  static bool commit_set_property(::executor, std::string);
  static bool wants_keys(::executor);
};
} } }


const char xml_media[]
  = "<media id=\"identifier\" descriptor=\"descriptor1\" src=\"source1\" />";
const char xml_descriptor_base[]
  = "<descriptorBase id=\"descriptor_base\">\n"
    "  <descriptor id=\"descriptor1\"/>"
    "</descriptorBase>"
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
  result_type operator()(std::string media, descriptor_type d) const
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

    typedef composed::media<dom::media, presentation_factory> media_type;
    media_type media (dom::media(xmldocument.root ()), presentation_factory());
    typedef composed::context<dom::body_context_type<dom::xml_string<> >, presentation_factory
                              , dom::connector_base> body_type;
    typedef composed::document<dom::document, presentation_factory, std::string> document_type;
    typedef gntl::concept::structure::document_traits<document_type> document_traits;
    dom::descriptor_base descriptor_base (xmldescriptordocument.root ());
    typedef concept::parser::descriptor_base_traits<dom::descriptor_base> descriptor_base_traits;
    document_type document;

    descriptor_type descriptor (*boost::begin(descriptor_base_traits::descriptor_all(descriptor_base)));

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));

    typedef concept::structure::media_traits<media_type> media_traits;

    boost::optional<document_traits::component_identifier> interface_;
    algorithm::structure::media::start (gntl::ref (media), interface_, descriptor_type()
                                        , gntl::ref (document), full);

    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
    BOOST_REQUIRE(media_traits::has_presentation(media, descriptor));
    presentation_type presentation = media_traits::get_presentation(media, descriptor);
    BOOST_CHECK(presentation_traits::is_occurring(presentation));
    presentation_traits::stop(presentation);
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));

    BOOST_CHECK(presentation_traits::is_occurring(presentation));

    typedef concept::structure::document_traits<document_type> document_traits;
    BOOST_CHECK_EQUAL (document_traits::pending_events (document), 2u);

    BOOST_CHECK_EQUAL (::executor_start_run, true);
    BOOST_CHECK_EQUAL (::executor_start_async_run, true);
}
