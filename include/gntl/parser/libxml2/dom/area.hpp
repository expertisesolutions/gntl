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

#ifndef GNTL_PARSER_LIBXML2_DOM_AREA_HPP
#define GNTL_PARSER_LIBXML2_DOM_AREA_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/time_duration_parser.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#include <gntl/concept/parser/media/area.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/invalid_ncl_error.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct area
{
    area (xml_node node)
        : node (node) {}

    struct xml_predicate
    {
        typedef bool result_type;
        result_type operator()(xml_node n) const { return n.name () == "area"; }
    };

    typedef xml_string<> identifier_type;
    typedef xml_string<> coordinate_type;
    typedef xml_string<> text_type;
    typedef unsigned int frame_type;
    typedef xml_string<> label_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct area_traits<gntl::parser::libxml2::dom
                   ::area>
{
  typedef gntl::parser::libxml2::dom::area area;
  typedef boost::mpl::true_ is_area;

  typedef area::identifier_type identifier_type;
  typedef area::coordinate_type coordinate_type;
  typedef boost::posix_time::time_duration time_type;
  typedef area::text_type text_type;
  typedef area::frame_type frame_type;
  typedef area::label_type label_type;
  
  static identifier_type identifier(area a)
  {
    if(!a.node["id"])
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (error::reason<const char*>::type
                                ("Area defined without a id attribute"))
                               (error::xml_attribute<const char*>::type
                                ("id")));
    return a.node["id"].value();
  }

  static bool has_begin(area a)
  {
    return a.node["begin"];
  }
  static time_type begin(area a)
  {
    return time_duration_parser(a.node["begin"].value());
  }
  static bool has_end(area a)
  {
    return a.node["end"];
  }
  static time_type end(area a)
  {
    return time_duration_parser(a.node["end"].value());
  }
  static bool has_first(area a)
  {
    return a.node["first"] && uint_parser(a.node["first"].value());
  }
  static frame_type first(area a)
  {
    return *uint_parser(a.node["first"].value());
  }
  static bool has_last(area a)
  {
    return a.node["last"] && uint_parser(a.node["last"].value());
  }
  static frame_type last(area a)
  {
    return *uint_parser(a.node["last"].value());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
