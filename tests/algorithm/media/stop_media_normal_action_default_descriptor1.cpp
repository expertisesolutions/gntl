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

#define BOOST_TEST_MODULE stop_media_normal_action_default_descriptor1
#include <boost/test/included/unit_test.hpp>

#include <gntl/algorithm/structure/media/stop_normal_action.hpp>
#include <gntl/algorithm/structure/media/stop.ipp>
#include <gntl/algorithm/structure/media/stop_action_traits.ipp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/descriptor.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/region_base.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/descriptor.hpp>
#include <gntl/structure/composed/descriptor_lookupable.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/document.hpp>
#include <gntl/structure/composed/presentation.hpp>

#include <boost/mpl/vector.hpp>

namespace concept = gntl::concept;
namespace algorithm = gntl::algorithm;
namespace dom = gntl::parser::libxml2::dom;
namespace composed = gntl::structure::composed;

bool executor_stop_run = false
    , executor_stop_async_run = false;

struct executor
{
};

struct void_ {};

namespace gntl { namespace concept { namespace structure {

template <>
struct executor_traits< ::executor>
{
  typedef boost::mpl::vector1
  <void(::executor)> start_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> stop_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> resume_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> pause_function_overloads;
  typedef boost::mpl::vector1
  <void(::executor)> abort_function_overloads;
  typedef ::void_ component_identifier;
  typedef ::void_ time_duration;
  typedef dom::color color_type;

  static void add_border (::executor e, int, color_type)
  {
    std::abort();
  }
  static void remove_border (::executor e) {}

  typedef boost::mpl::true_ is_executor;
  static void stop (::executor e)
  {
    std::cout << "executor_stop" << std::endl;
    executor_stop_run = true;
  }

  template <typename Handler>
  static void async_stop (::executor e, Handler handler)
  {
    std::cout << "executor_stop_async" << std::endl;
    executor_stop_async_run = true;
  }

  static void start (::executor e) {}
  static void pause (::executor e);
  static void resume (::executor e);
  static void abort (::executor e);
  static void start_area (::executor, component_identifier);

  static void area_time_begin(::executor, component_identifier, time_duration);
  static void area_time_end(::executor, component_identifier, time_duration);
  static void area_time_begin_end(::executor, component_identifier, time_duration, time_duration);
  static void area_frame_begin(::executor, component_identifier, unsigned int);
  static void area_frame_end(::executor, component_identifier, unsigned int);
  static void area_frame_begin_end(::executor, component_identifier, unsigned int, unsigned int);
  static void area_npt_begin(::executor, component_identifier, int);
  static void area_npt_end(::executor, component_identifier, int);
  static void area_npt_begin_end(::executor, component_identifier, int, int);
  static void explicit_duration(::executor, time_duration);
  static bool start_set_property(::executor, std::string, std::string);
  static bool commit_set_property(::executor, std::string);
  static bool wants_keys(::executor);
};

} } }

const char xml_media[]
  = "<media id=\"identifier\" src=\"source1\" />";

template <typename T>
T const& as_const (T& x) { return x; }

void handler ()
{
    std::cout << "handler" << std::endl;
}

typedef composed::descriptor<dom::descriptor, std::string> descriptor_type;
typedef composed::presentation< ::executor, descriptor_type> presentation_type;

struct presentation_factory
{
  typedef presentation_type result_type;
  result_type operator()(std::string media, descriptor_type d) const
  {
    return presentation_type(executor(), d);
  }
};

BOOST_AUTO_TEST_CASE (stop_media_normal_action_default_descriptor1)
{
    ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_media)));
    dom::xml_document xmldocument (xmldoc); // gets ownership
    typedef composed::media<dom::media, presentation_factory> media_type;
    typedef composed::context<dom::body_context_type<std::string>, presentation_factory
                              , dom::connector_base> context_type;
    typedef composed::descriptor_lookupable<dom::descriptor_base, std::string> descriptor_lookupable;
    typedef composed::document<dom::document, presentation_factory, std::string> document_type;
    context_type context(dom::body_context_type<std::string>
                         (dom::xml_node(), "dummy"));
    document_type document;

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));
    typedef gntl::concept::structure::media_traits<media_type> media_traits;
    media_type media (dom::media(xmldocument.root ()));

    typedef gntl::concept::structure::presentation_traits<presentation_type> presentation_traits;
    presentation_type presentation = media_traits::prepare_presentation (media, descriptor_type());
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));
    presentation_traits::start(presentation);
    BOOST_CHECK(presentation_traits::is_occurring(presentation));

    algorithm::structure::media::stop (gntl::ref (media), descriptor_type(), gntl::ref(document));

    BOOST_CHECK(presentation_traits::is_sleeping(presentation));
    presentation_traits::start(presentation);
    BOOST_CHECK(presentation_traits::is_occurring(presentation));

    // algorithm::structure::media::async_stop (boost::ref (media), &::handler);
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));

    BOOST_CHECK_EQUAL (::executor_stop_run, true);
    BOOST_CHECK_EQUAL (::executor_stop_async_run, true);
}
