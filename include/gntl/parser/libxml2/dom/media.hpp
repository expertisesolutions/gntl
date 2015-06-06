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

#ifndef GNTL_PARSER_LIBXML2_DOM_MEDIA_HPP
#define GNTL_PARSER_LIBXML2_DOM_MEDIA_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/area.hpp>
#include <gntl/parser/libxml2/dom/property.hpp>
#include <gntl/parser/libxml2/dom/descriptor.hpp>
#include <gntl/parser/libxml2/dom/xml_property_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept/parser/descriptor/descriptor.hpp>
#include <gntl/range.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct media
{
    media (xml_node node)
        : node (node)
    {
      assert(node != xml_node());
    }

    typedef property property_type;
    typedef xml_element_node_iterator<property_type, xml_property_predicate> property_iterator;

    typedef area area_type;
    typedef xml_element_node_iterator<area_type, area_type::xml_predicate> area_iterator;

    typedef xml_string<> identifier_type;
    typedef xml_string<> source_type;
    typedef xml_string<> refer_type;
    typedef xml_string<> instance_type;
    typedef xml_string<> type_type;
    typedef xml_string<> descriptor_type;

    xml_node node;
};


inline media::property_iterator property_sequence_begin (media m)
{
    return m.node.begin ();
}

inline media::property_iterator property_sequence_end (media m)
{
    return m.node.end ();
}

} } }

namespace concept { namespace parser {

template <>
struct media_traits<gntl::parser::libxml2::dom::media>
{
    typedef gntl::parser::libxml2::dom::media media;
    typedef media::identifier_type identifier_type;
    typedef media::source_type source_type;
    typedef media::instance_type instance_type;
    typedef media::type_type type_type;
    typedef media::descriptor_type descriptor_type;
    typedef boost::mpl::true_ is_media;
    typedef media::area_iterator area_iterator;
    typedef boost::iterator_range<area_iterator> area_range;
    typedef media::property_iterator property_iterator;
    typedef boost::iterator_range<property_iterator> property_range;
    typedef parser::descriptor_traits<gntl::parser::libxml2::dom::descriptor>
      descriptor_traits;
    typedef descriptor_traits::player_type player_type;
    typedef descriptor_traits::explicit_duration_type explicit_duration_type;
    typedef descriptor_traits::freeze_type freeze_type;
    typedef descriptor_traits::focus_index_type focus_index_type;
    typedef descriptor_traits::color_type color_type;
    typedef descriptor_traits::transition_type transition_type;
    typedef descriptor_traits::region_type region_type;
    typedef descriptor_traits::width_type width_type;
    typedef descriptor_traits::transparency_type transparency_type;

    static identifier_type identifier (media m)
    {
      return m.node["id"].value ();
    }

    static bool has_source (media m)
    {
      return m.node["src"];
    }

    static source_type source (media m)
    {
      return m.node["src"].value ();
    }

    static bool has_refer (media m)
    {
      return m.node["refer"];
    }

    static identifier_type refer (media m)
    {
      return m.node["refer"].value ();
    }

    static bool has_instance (media m)
    {
      return m.node["instance"];
    }

    static instance_type instance (media m)
    {
      return m.node["instance"].value ();
    }

    static bool has_type (media m)
    {
      return m.node["type"];
    }

    static type_type type (media m)
    {
      return m.node["type"].value ();
    }

    static bool has_descriptor (media m)
    {
      return m.node["descriptor"];
    }

    static descriptor_type descriptor (media m)
    {
      return m.node["descriptor"].value ();
    }
    static area_range area_all(media m)
    {
      return area_range(m.node.begin(), m.node.end());
    }
    static property_range property_all(media m)
    {
      return property_range(m.node.begin(), m.node.end());
    }
private:
    static property_iterator get_property(media m, const char* name)
    {
      return gntl::range::find_if(property_all(m)
                                  , property_name_comparator("explicitDur"));
    }
    typedef boost::range_value<property_range>::type property_type;
    typedef parser::property_traits<property_type> property_traits;
    typedef property_traits::value_type property_value_type;
    static property_value_type property_value(media m, const char* name)
    {
      return property_traits::value(*get_property(m, name));
    }
    struct property_name_comparator
    {
      property_name_comparator(const char* name)
        : name(name) {}

      typedef bool result_type;
      template <typename Property>
      result_type operator()(Property const& other) const
      {
        typedef typename unwrap_parameter<Property>::type property_type;
        typedef parser::property_traits<property_type> property_traits;
        return name == property_traits::name(other);
      }

      const char* name;
    };
    static bool has_property(media m, const char* name)
    {
      return get_property(m, name) != boost::end(property_all(m));
    }
public:
    static bool has_player (media m)
    {
      return has_property(m, "player");
    }
    static player_type player (media m)
    {
      return property_value(m, "player");
    }
    static bool has_explicit_duration (media m)
    {
      return has_property(m, "explicitDur");
    }
    static boost::posix_time::time_duration explicit_duration (media m)
    {
      return time_duration_parser(property_value(m, "explicitDur"));
    }
    static bool has_region (media m)
    {
      return has_property(m, "region");
    }
    static region_type region (media m)
    {
      return property_value(m, "region");
    }
    static bool has_freeze (media m)
    {
      return has_property(m, "freeze");
    }
    static bool freeze (media m)
    {
      return property_value(m, "freeze") == "true"
        || property_value(m, "freeze") == "freeze";
    }
    static bool has_move_left (media m)
    {
      return has_property(m, "moveLeft")
        && uint_parser(property_value(m, "moveLeft"));
    }
    static focus_index_type move_left (media m)
    {
      return *uint_parser(property_value(m, "moveLeft"));
    }
    static bool has_move_right (media m);
    static int move_right (media m);
    static bool has_move_up (media m);
    static int move_up (media m);
    static bool has_move_down (media m);
    static int move_down (media m);
    static bool has_focus_index (media m);
    static int focus_index (media m);
    static bool has_focus_border_color (media m);
    static color_type focus_border_color (media m);
    static bool has_focus_border_width (media m);;
    static int focus_border_width (media m);
    static bool has_focus_border_transparency (media m);
    static transparency_type focus_border_transparency (media m);
    static bool has_focus_source (media m);
    static source_type focus_source (media m);
    static bool has_focus_selection_source (media m);
    static source_type focus_selection_source (media m);
    static bool has_selection_border_color (media m);
    static color_type selection_border_color (media m);
    static bool has_transition_in (media m);
    static transition_type transition_in (media m);
    static bool has_transition_out (media m);
    static transition_type transition_out (media m);
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
