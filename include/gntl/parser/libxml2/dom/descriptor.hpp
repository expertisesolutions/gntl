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

#ifndef GNTL_PARSER_LIBXML2_DOM_DESCRIPTOR_HPP
#define GNTL_PARSER_LIBXML2_DOM_DESCRIPTOR_HPP

#include <gntl/parser/libxml2/dom/color.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/time_duration_parser.hpp>
#include <gntl/parser/libxml2/dom/uint_parser.hpp>
#include <gntl/parser/libxml2/dom/descriptor_param.hpp>
#include <gntl/parser/libxml2/dom/xml_descriptor_param_predicate.hpp>
#include <gntl/parser/libxml2/dom/color_parser.hpp>
#include <gntl/concept/parser/descriptor/descriptor.hpp>
#include <gntl/range.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct descriptor
{
    descriptor (xml_node node)
        : node (node)
        {}

    typedef gntl::parser::libxml2::dom::xml_element_node_iterator
        <descriptor_param
         , xml_descriptor_param_predicate> 
      descriptor_param_iterator;

    xml_node node;
};

inline bool operator==(descriptor const& lhs, descriptor const& rhs)
{
  return lhs.node == rhs.node;
}

inline bool operator!=(descriptor const& lhs, descriptor const& rhs)
{
  return !(lhs == rhs);
}

} } }

namespace concept { namespace parser {

template <>
struct descriptor_traits<gntl::parser::libxml2::dom::descriptor>
{
    typedef boost::mpl::true_ is_descriptor;
    typedef gntl::parser::libxml2::dom
      ::descriptor
      descriptor;
    typedef gntl::parser::libxml2::dom
      ::descriptor_param
      descriptor_param;
    typedef gntl::parser::libxml2::dom::xml_string<> string;
    typedef gntl::parser::libxml2::dom::color color;
    typedef string identifier_type;
    typedef string player_type;
    typedef boost::posix_time::time_duration explicit_duration_type;
    typedef string region_type;
    typedef bool freeze_type;
    typedef int focus_index_type;
    typedef color color_type;
    typedef int width_type;
    struct transparency_type {};
    typedef string source_type;
    typedef std::vector<string > transition_type;
    typedef gntl::parser::libxml2::dom::descriptor_param
      descriptor_param_type;
  typedef descriptor::descriptor_param_iterator descriptor_param_iterator;

  static string identifier (descriptor d)
  {
    return d.node["id"].value ();
  }

  static bool has_player (descriptor d)
  {
    return d.node["player"];
  }
  static player_type player (descriptor d)
  {
    return d.node["player"].value();
  }
  static bool has_explicit_duration (descriptor d)
  {
    return d.node["explicitDur"];
  }
  static boost::posix_time::time_duration explicit_duration (descriptor d)
  {
    return time_duration_parser (d.node["explicitDur"].value ());
  }
  static bool has_region (descriptor d)
  {
    return d.node["region"];
  }
  static string region (descriptor d)
  {
    return d.node["region"].value ();
  }
  static bool has_freeze (descriptor d)
  {
    return d.node["freeze"];
  }
  static bool freeze (descriptor d)
  {
    string s = d.node["freeze"].value ();
    return s == "true" || s == "freeze";
  }
  static bool has_move_left (descriptor d)
  {
    return d.node["moveLeft"]
      && focus_index_parser(d.node["moveLeft"].value());
  }
  static int move_left (descriptor d)
  {
    return *focus_index_parser(d.node["moveLeft"].value());
  }
  static bool has_move_right (descriptor d)
  {
    return d.node["moveRight"]
      && focus_index_parser(d.node["moveRight"].value());
  }
  static int move_right (descriptor d)
  {
    return *focus_index_parser(d.node["moveRight"].value ());
  }
  static bool has_move_up (descriptor d)
  {
    return d.node["moveUp"]
      && focus_index_parser(d.node["moveUp"].value());
  }
  static int move_up (descriptor d)
  {
    return *focus_index_parser(d.node["moveUp"].value ());
  }
  static bool has_move_down (descriptor d)
  {
    return d.node["moveDown"]
      && focus_index_parser(d.node["moveDown"].value());
  }
  static int move_down (descriptor d)
  {
    return *focus_index_parser(d.node["moveDown"].value ());
  }

  static bool has_focus_index (descriptor d)
  {
    return d.node["focusIndex"] && focus_index_parser(d.node["focusIndex"].value());
  }
  static int focus_index (descriptor d)
  {
    return *focus_index_parser(d.node["focusIndex"].value());
  }

  static bool has_focus_border_color (descriptor d)
  {
    return d.node["focusBorderColor"]
      && color_parser(d.node["focusBorderColor"].value());
  }
  static color focus_border_color (descriptor d)
  {
    return *color_parser(d.node["focusBorderColor"].value ());
  }

  static bool has_focus_border_width (descriptor d)
  {
    return d.node["focusBorderWidth"]
      && uint_parser(d.node["focusBorderWidth"].value());
  }
  static int focus_border_width (descriptor d)
  {
    return *int_parser (d.node["focusBorderWidth"].value ());
  }

  static bool has_focus_border_transparency (descriptor d)
  {
    return d.node["focusBorderTransparency"];
  }
  static transparency_type focus_border_transparency (descriptor)
  {
    return transparency_type();
  }

  static bool has_focus_source (descriptor d)
  {
    return d.node["focusSrc"];
  }
  static string focus_source (descriptor d)
  {
    return d.node["focusSrc"].value ();
  }

  static bool has_focus_selection_source (descriptor d)
  {
    return d.node["focusSelSrc"];
  }
  static string focus_selection_source (descriptor d)
  {
    return d.node["focusSelSrc"].value ();
  }

  static bool has_selection_border_color (descriptor d)
  {
    return d.node["selBorderColor"]
      && color_parser(d.node["selBorderColor"].value());
  }
  static color selection_border_color (descriptor d)
  {
    return *color_parser(d.node["selBorderColor"].value ());
  }

  static bool has_transition_in (descriptor d)
  {
    return d.node["transIn"];
  }

  static transition_type transition_in (descriptor d)
  {
    std::vector<string > r;
    return r;
  }

  static bool has_transition_out (descriptor d)
  {
    return d.node["transOut"];
  }

  static transition_type transition_out (descriptor)
  {
    std::vector<string > r;
    return r;
  }
};

template <>
struct has_descriptor_param_traits<gntl::parser::libxml2::dom
                                   ::descriptor>
{
  typedef gntl::parser::libxml2::dom::descriptor descriptor;
  typedef descriptor::descriptor_param_iterator descriptor_param_iterator;
   typedef boost::iterator_range<descriptor_param_iterator> 
    descriptor_param_range;
  typedef boost::mpl::true_ has_descriptor_param;

  static descriptor_param_range descriptor_param(descriptor d)
  {
    return descriptor_param_range
      (descriptor_param_iterator(d.node.begin ())
       , descriptor_param_iterator(d.node.end()));
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
