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

#ifndef GNTL_PARSER_LIBXML2_DOM_TRANSITION_HPP
#define GNTL_PARSER_LIBXML2_DOM_TRANSITION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/time_duration_parser.hpp>
#include <gntl/parser/libxml2/dom/float_parser.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#include <gntl/concept/parser/transition/transition.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct transition
{
    transition (xml_node node)
        : node (node) {}

    typedef xml_string<> identifier_type;
    typedef xml_string<> type_type;
    typedef boost::posix_time::time_duration duration_type;
    typedef float start_progress_type;
    typedef float end_progress_type;
    typedef xml_string<> direction_type;
    typedef xml_string<> fade_color_type;
    typedef std::size_t horizontal_repeat_type;
    typedef std::size_t vertical_repeat_type;
    typedef std::size_t border_width_type;
    typedef xml_string<> border_color_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct transition_traits<gntl::parser::libxml2::dom::transition>
{
  typedef boost::mpl::true_ is_transition;
  typedef gntl::parser::libxml2::dom::transition transition;
  
  typedef transition::identifier_type identifier_type;
  typedef transition::type_type type_type;
  typedef transition::duration_type duration_type;
  typedef transition::start_progress_type start_progress_type;
  typedef transition::end_progress_type end_progress_type;
  typedef transition::direction_type direction_type;
  typedef transition::fade_color_type fade_color_type;
  typedef transition::horizontal_repeat_type horizontal_repeat_type;
  typedef transition::vertical_repeat_type vertical_repeat_type;
  typedef transition::border_width_type border_width_type;
  typedef transition::border_color_type border_color_type;

  static identifier_type identifier (transition t)
  {
    return t.node["id"].value ();
  }

  static type_type type (transition t)
  {
    return t.node["type"].value ();
  }

  static duration_type duration (transition t)
  {
    return gntl::parser::libxml2::dom
      ::time_duration_parser (t.node["dur"].value ());
  }

  static bool has_duration (transition t)
  {
    return t.node["dur"];
  }

  static start_progress_type start_progress (transition t)
  {
    return gntl::parser::libxml2::dom
      ::float_parser (t.node["startProgress"].value ());
  }

  static bool has_start_progress (transition t)
  {
    return t.node["startProgress"];
  }

  static end_progress_type end_progress (transition t)
  {
    return gntl::parser::libxml2::dom
      ::float_parser (t.node["endProgress"].value ());
  }

  static bool has_end_progress (transition t)
  {
    return t.node["endProgress"];
  }

  static direction_type direction (transition t)
  {
    return t.node["direction"].value ();
  }

  static bool has_direction (transition t)
  {
    return t.node["direction"];
  }

  static fade_color_type fade_color (transition t)
  {
    return t.node["fadeColor"].value ();
  }

  static bool has_fade_color (transition t)
  {
    return t.node["fadeColor"];
  }

  static horizontal_repeat_type horizontal_repeat (transition t)
  {
    return *gntl::parser::libxml2::dom
      ::uint_parser (t.node["horRepeat"].value ());
  }

  static bool has_horizontal_repeat (transition t)
  {
    return t.node["horRepeat"]
      && gntl::parser::libxml2::dom::uint_parser(t.node["horRepeat"].value());
  }

  static vertical_repeat_type vertical_repeat (transition t)
  {
    return *gntl::parser::libxml2::dom
      ::uint_parser (t.node["vertRepeat"].value ());
  }

  static bool has_vertical_repeat (transition t)
  {
    return t.node["vertRepeat"]
      && gntl::parser::libxml2::dom::uint_parser(t.node["vertRepeat"].value());
  }

  static border_width_type border_width (transition t)
  {
    return *gntl::parser::libxml2::dom
      ::uint_parser (t.node["borderWidth"].value ());
  }

  static bool has_border_width (transition t)
  {
    return t.node["borderWidth"]
      && gntl::parser::libxml2::dom::uint_parser(t.node["borderWidth"].value());
  }

  static border_color_type border_color (transition t)
  {
    return t.node["borderColor"].value ();
  }

  static bool has_border_color (transition t)
  {
    return t.node["borderColor"];
  }
};

} } } 


#include <gntl/detail/pop_options.hpp>

#endif
