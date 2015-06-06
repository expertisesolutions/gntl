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

#ifndef GNTL_PARSER_LIBXML2_DOM_REGION_HPP
#define GNTL_PARSER_LIBXML2_DOM_REGION_HPP

#include <gntl/concept/parser/region/region.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>
#endif
#include <boost/variant.hpp>

#include <iosfwd>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

namespace spirit {
#if BOOST_VERSION >= 104200
    namespace arg_names = boost::spirit::qi;
#else
    namespace arg_names = boost::spirit::arg_names;
#endif
}

struct coordinate
{
  typedef std::size_t pixel_type;
  typedef double percentage_type;

  coordinate()
    : variant (pixel_type(0u))
  {}
  coordinate(pixel_type pixel)
    : variant (pixel)
  {}

  coordinate(percentage_type percentage)
    : variant (percentage)
  {}

  bool is_percentual() const
  {
    return boost::get<percentage_type>(&variant) != 0;
  }

  pixel_type pixel() const
  {
    return boost::get<pixel_type>(variant);
  }

  percentage_type percentage() const
  {
    return boost::get<percentage_type>(variant);
  }

private:
  boost::variant<pixel_type, percentage_type> variant;
};

inline std::ostream& operator<<(std::ostream& s, coordinate c)
{
  if(c.is_percentual())
    s << c.percentage() << '%';
  else
    s << c.pixel() << 'p';
  return s;
}

#if BOOST_VERSION >= 104000
inline coordinate coordinate_parser(xml_string<> string)
{
  namespace qi = boost::spirit::qi;
  namespace spirit = boost::spirit;
  namespace arg_names = dom::spirit::arg_names;
  namespace phoenix = boost::phoenix;
  
  xml_string<>::const_iterator iterator = string.begin ();
  coordinate::percentage_type percentual = 0.0;
  coordinate::pixel_type pixel = 0;
  if(qi::parse (iterator, string.end()
                , spirit::double_[phoenix::ref(percentual) = arg_names::_1]
                >> '%'))
  {
    return coordinate (percentual/100);
  }
  else if(qi::parse (iterator, string.end()
                     , spirit::uint_[phoenix::ref(pixel) = arg_names::_1]))
    return coordinate (pixel);
  else
    return coordinate ();
}
#else
coordinate coordinate_parser(xml_string<> string); // not implemented yet
#endif

struct region
{
    region (xml_node node)
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef xml_string<> title_type;
    typedef dom::coordinate coordinate_type;
    typedef int zindex_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct region_traits<gntl::parser::libxml2::dom
                     ::region>
{
  typedef boost::mpl::true_ is_region;
  typedef gntl::parser::libxml2::dom::region region;
  typedef region::identifier_type identifier_type;
  typedef region::title_type title_type;
  typedef region::coordinate_type coordinate_type;
  typedef region::zindex_type zindex_type;
  ;

  static identifier_type identifier (region r)
  {
    return r.node["id"].value ();
  }

  static bool has_title (region r)
  {
    return r.node["title"];
  }

  static bool has_left (region r)
  {
    return r.node["left"];
  }

  static bool has_right (region r)
  {
    return r.node["right"];
  }

  static bool has_top (region r)
  {
    return r.node["top"];
  }

  static bool has_bottom (region r)
  {
    return r.node["bottom"];
  }

  static bool has_height (region r)
  {
    return r.node["height"];
  }

  static bool has_width (region r)
  {
    return r.node["width"];
  }

  static title_type title (region r)
  {
    return r.node["title"].value ();
  }

  static bool has_zindex (region r)
  {
    return r.node["zIndex"]
      && gntl::parser::libxml2::dom::int_parser(r.node["zIndex"].value());
  }

  static coordinate_type left (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["left"].value ());
  }

  static coordinate_type right (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["right"].value ());
  }

  static coordinate_type top (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["top"].value ());
  }

  static coordinate_type bottom (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["bottom"].value ());
  }

  static coordinate_type height (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["height"].value ());
  }

  static coordinate_type width (region r)
  {
    return gntl::parser::libxml2::dom::coordinate_parser
      (r.node["width"].value ());
  }

  static zindex_type zindex (region r)
  {
    return *gntl::parser::libxml2::dom::int_parser
      (r.node["zIndex"].value ());
  }
};

template <>
struct coordinate_traits<gntl::parser::libxml2::dom
                         ::coordinate>
{
  typedef gntl::parser::libxml2::dom
    ::coordinate coordinate;
  typedef coordinate::pixel_type pixel_type;
  typedef coordinate::percentage_type percentage_type;

  static bool is_percentual (coordinate const& c)
  {
    return c.is_percentual ();
  }

  static pixel_type pixel (coordinate const& c)
  {
    return c.pixel ();
  }

  static percentage_type percentage (coordinate const& c)
  {
    return c.percentage ();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
