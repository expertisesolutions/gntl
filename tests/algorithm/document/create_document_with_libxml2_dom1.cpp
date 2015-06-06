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

#define BOOST_TEST_MODULE create_document_with_libxml2_dom1
#include <boost/test/included/unit_test.hpp>

#include <gntl/algorithm/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/concept/parser/document/document.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/causal_connector.hpp>
#include <gntl/parser/libxml2/dom/document.hpp>
#include <gntl/parser/libxml2/dom/xml_document.hpp>
#include <gntl/structure/composed/document.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/descriptor.hpp>
#include <gntl/structure/composed/descriptor_lookupable.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/presentation.hpp>

#include <boost/range/iterator_range.hpp>

namespace concept = gntl::concept;
namespace dom = gntl::parser::libxml2::dom;
namespace composed = gntl::structure::composed;

const char xml_doc[]
  = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
    "<ncl id=\"teste\" xmlns=\"http://www.ncl.org.br/NCL3.0/EDTVProfile\">\n"
    "  <head>\n"
    "   <descriptorBase>\n"
    "     <descriptor id=\"descriptor1\" region=\"region1\"/>\n"
    "   </descriptorBase>\n"
    "  </head>\n"
    "  <body>\n"
    "  </body>\n"
    "</ncl>\n"
    ;

struct region {};

struct executor {};
struct void_ {};

namespace gntl { namespace concept { namespace structure {
template <>
struct executor_traits< ::executor>
{
  typedef boost::mpl::vector1
  <void(::executor, gntl::parser::libxml2::dom::xml_string<>
        , gntl::concept::structure::unrestricted_tag<boost::optional<int> >
        , gntl::algorithm::structure::media::dimensions
        , int, gntl::parser::libxml2::dom::color)> start_function_overloads;
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
  typedef ::void_ color_type;

  static void add_border (::executor, int, color_type);
  static void remove_border (::executor);

  typedef boost::mpl::true_ is_executor;
  template <typename Descriptor>
  static void start (::executor e, gntl::parser::libxml2::dom::xml_string<> source
                     , boost::optional<Descriptor> descriptor
                     , gntl::algorithm::structure::media::dimensions dim
                     , int, gntl::parser::libxml2::dom::color);

  static void stop (::executor e);
  static void pause (::executor e);
  static void resume (::executor e);
  static void abort (::executor e);
  static void start_area (::executor e, component_identifier);

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

BOOST_AUTO_TEST_CASE (create_document_with_libxml2_dom1)
{
    ::xmlDocPtr xmldoc = xmlParseDoc(static_cast<const xmlChar*>(static_cast<const void*>(xml_doc)));
    dom::xml_document doc (xmldoc); // gets ownership
    dom::document parser_doc (doc.root ());

    GNTL_CONCEPT_ASSERT((concept::parser::Head<dom::head>));

    typedef concept::parser::document_traits<dom::document> parser_document_traits;
    typedef concept::parser::head_traits<dom::head> parser_head_traits;
    
    dom::head head = parser_document_traits::head (parser_doc);

    dom::descriptor_base descriptor_base;
    if(parser_head_traits::has_descriptor_base (head))
        descriptor_base = parser_head_traits::descriptor_base (head);

    std::cout << "descriptors: " 
              << std::distance (boost::begin (descriptor_base), boost::end (descriptor_base)) << std::endl;

    typedef composed::document<dom::document, presentation_factory, std::string> document_type;
    document_type d(parser_doc);
}
