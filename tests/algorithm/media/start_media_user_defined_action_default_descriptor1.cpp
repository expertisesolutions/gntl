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

#define BOOST_TEST_MODULE start_media_user_defined_action_default_descriptor1
#include <boost/test/included/unit_test.hpp>

#include <gntl/algorithm/structure/media/start.hpp>
#include <gntl/algorithm/structure/media/start.ipp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/descriptor.hpp>
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
  typedef boost::mpl::vector1
  <void(::executor/*, gntl::parser::libxml2::dom::xml_string<>
        , gntl::concept::structure::unrestricted_tag<boost::optional<int> >
        , gntl::algorithm::structure::media::dimensions
        , int, gntl::parser::libxml2::dom::color*/)> start_function_overloads;
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
  typedef ::void_ color_type;
  
  static void add_border (executor e, int, color_type);
  static void remove_border (executor e);

  typedef boost::mpl::true_ is_executor;
  static void start (executor e/*, Source source, boost::optional<Descriptor> descriptor
                     , gntl::algorithm::structure::media::dimensions dimensions, int border_width
                     , gntl::parser::libxml2::dom::color border_color*/)
  {
    std::cout << "executor_start" << std::endl;
    executor_start_run = true;
    // BOOST_CHECK_EQUAL (source, "source1");
    // BOOST_CHECK (!descriptor);
    // BOOST_CHECK_EQUAL (full, dimensions);
  }

  static void stop (::executor e) {}
  static void pause (::executor e);
  static void resume (::executor e);
  static void abort (::executor e);
  static void start_area (::executor e, component_identifier) { std::abort(); }

  static void area_time_begin(::executor e, component_identifier, time_duration);
  static void area_time_end(::executor e, component_identifier, time_duration);
  static void area_time_begin_end(::executor e, component_identifier, time_duration, time_duration);
  static void area_frame_begin(::executor e, component_identifier, unsigned int);
  static void area_frame_end(::executor e, component_identifier, unsigned int);
  static void area_frame_begin_end(::executor e, component_identifier, unsigned int, unsigned int);
  static void area_npt_begin(::executor e, component_identifier, int);
  static void area_npt_end(::executor e, component_identifier, int);
  static void area_npt_begin_end(::executor e, component_identifier, int, int);
  static void explicit_duration(::executor, time_duration);
  static bool start_set_property(::executor, std::string, std::string);
  static bool commit_set_property(::executor, std::string);
  static bool wants_keys(::executor);
};
} } }

const char xml_media[]
  = "<media id=\"identifier\" src=\"source1\" />";

void handler ()
{
    std::cout << "handler" << std::endl;
}

struct start_traits
{
  template <typename Media, typename OptionalInterface, typename Descriptor>
  static void start(Media m, OptionalInterface interface_, Descriptor descriptor
                    , gntl::algorithm::structure::media::dimensions)
  {
    typedef typename gntl::unwrap_parameter<Media>::type media_type;
    typedef gntl::concept::structure::media_traits<media_type> media_traits;
    typedef typename media_traits::presentation_type presentation_type;
    typedef gntl::concept::structure::presentation_traits<presentation_type> presentation_traits;
    presentation_type p = media_traits::prepare_presentation
      (m, descriptor);
    presentation_traits::start(p);
  }
};

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

BOOST_AUTO_TEST_CASE (start_media_user_defined_action_default_descriptor1)
{
    ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_media)));
    dom::xml_document xmldocument (xmldoc); // gets ownership
    typedef composed::media<dom::media, presentation_factory> media_type;
    typedef composed::context<dom::body_context_type<dom::xml_string<> >, presentation_factory
                              , dom::connector_base> context_type;
    typedef composed::descriptor_lookupable<dom::descriptor_base, std::string>
      descriptor_lookupable;
    typedef composed::document<dom::document, presentation_factory
                               , std::string> document_type;
    typedef gntl::concept::structure::document_traits<document_type> document_traits;
    context_type context(dom::body_context_type<dom::xml_string<> >
                         (dom::xml_node()
                          , dom::xml_string<>
                          (static_cast<xmlChar const*>(static_cast<void const*>("dummy")))));
    document_type document;

    GNTL_CONCEPT_ASSERT ((concept::structure::Media<media_type>));
    typedef concept::structure::media_traits<media_type> media_traits;
    media_type media (dom::media(xmldocument.root ()));

    typedef gntl::concept::structure::presentation_traits<presentation_type> presentation_traits;
    presentation_type presentation = media_traits::prepare_presentation (media, descriptor_type());
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));

    boost::optional<document_traits::component_identifier> interface_;
    algorithm::structure::media::start<start_traits> (gntl::ref (media), interface_
                                                      , descriptor_type()
                                                      , gntl::ref(document), full);

    BOOST_CHECK(presentation_traits::is_occurring(presentation));
    presentation_traits::stop(presentation);
    BOOST_CHECK(presentation_traits::is_sleeping(presentation));

    // algorithm::structure::media::async_start (boost::ref (media), boost::ref (document)
    //                                , descriptor_base.end ()
    //                                , full
    //                                , &::handler);
    BOOST_CHECK(presentation_traits::is_occurring(presentation));

    BOOST_CHECK_EQUAL (::executor_start_run, true);
    BOOST_CHECK_EQUAL (::executor_start_async_run, true);
}
