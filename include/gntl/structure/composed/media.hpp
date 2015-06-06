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

#ifndef GNTL_STRUCTURE_COMPOSED_MEDIA_HPP
#define GNTL_STRUCTURE_COMPOSED_MEDIA_HPP

#include <gntl/algorithm/structure/property_container.hpp>
#include <gntl/concept/lookupable.hpp>
#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/executor.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/structure/composed/presentation.hpp>
#include <gntl/structure/composed/property.hpp>
#include <gntl/structure/composed/property_container.hpp>
#include <gntl/ref.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <set>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserMedia, typename PresentationFactory>
struct media
{
  typedef typename unwrap_parameter<ParserMedia>::type parser_media_type;
  typedef typename unwrap_parameter<PresentationFactory>::type presentation_factory_type;
  typedef typename presentation_factory_type::result_type presentation_value_type;
  typedef typename unwrap_parameter<presentation_value_type>::type presentation_type;
  GNTL_CONCEPT_ASSERT ((concept::parser::Media<parser_media_type>));
  GNTL_CONCEPT_ASSERT ((concept::structure::Presentation<presentation_type>));

  template <typename OtherParserMedia>
  media (OtherParserMedia parser_media, PresentationFactory presentation_factory = PresentationFactory())
    : parser_media (parser_media), presentation_factory(presentation_factory)
  {
    algorithm::structure::property_container::initialize_from_parser_media
      (properties, gntl::ref_once(parser_media));
  }

  typedef concept::parser::media_traits<parser_media_type> parser_media_traits;

  typedef typename parser_media_traits::property_range parser_property_range_value_type;
  typedef typename unwrap_parameter<parser_property_range_value_type>::type parser_property_range;
  typedef typename boost::range_value<parser_property_range>::type parser_property_value_type;
  typedef typename unwrap_parameter<parser_property_value_type>::type parser_property_type;
  typedef concept::parser::property_traits<parser_property_type> parser_property_traits;
  typedef typename parser_property_traits::name_type interface_type;

  typedef composed::property_container<std::string, int, double> property_container;
  typedef property_container::property_type property_type;

  property_container properties;
  ParserMedia parser_media;
  PresentationFactory presentation_factory;
  std::vector<presentation_value_type> presentations;
};

} }

namespace concept { namespace structure {

template <typename ParserMedia, typename PresentationFactory>
struct media_traits<gntl::structure::composed::media<ParserMedia, PresentationFactory> >
{
  typedef gntl::structure::composed::media<ParserMedia, PresentationFactory> media_type;
  typedef boost::true_type is_media;
  typedef typename boost::unwrap_reference<ParserMedia>::type media_parser_type;
  typedef concept::parser::media_traits<media_parser_type> parser_media_traits;
  typedef std::string interface_type;
  typedef std::string string_type;
  typedef int integer_type;
  typedef typename parser_media_traits::descriptor_type descriptor_identifier_type;
  typedef typename media_type::presentation_type presentation_type;
  typedef typename media_type::presentation_value_type presentation_value_type;
  typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
  typedef typename presentation_traits::descriptor_type descriptor_value_type;
  typedef typename unwrap_parameter<descriptor_value_type>::type descriptor_type;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  typedef boost::iterator_range<typename std::vector<presentation_value_type>::iterator> presentation_range;
  typedef typename media_type::property_type property_type;
  typedef typename media_type::property_container property_container;
  typedef typename property_container::iterator property_iterator;
  typedef boost::iterator_range<property_iterator> property_range;

  typedef typename parser_media_traits::identifier_type identifier_type;
  typedef typename parser_media_traits::source_type source_type;
  typedef typename parser_media_traits::instance_type instance_type;
  typedef typename parser_media_traits::type_type type_type;
  typedef typename parser_media_traits::area_range area_range;
  typedef typename parser_media_traits::player_type player_type;
  typedef typename parser_media_traits::explicit_duration_type explicit_duration_type;
  typedef typename parser_media_traits::region_type region_type;
  typedef typename parser_media_traits::freeze_type freeze_type;
  typedef typename parser_media_traits::focus_index_type focus_index_type;
  typedef typename parser_media_traits::color_type color_type;
  typedef typename parser_media_traits::width_type width_type;
  typedef typename parser_media_traits::transparency_type transparency_type;
  typedef typename parser_media_traits::transition_type transition_type;

  static bool is_same_instance_refer(media_type const& m)
  {
    return false;
  }
  static identifier_type same_instance_referred(media_type const& m)
  {
    std::abort();
  }
  static bool has_property(media_type const& m, interface_type name)
  {
    typedef typename media_type::property_container::iterator iterator;
    iterator i = m.properties.find(name);
    return i != m.properties.end();
  }
  static void start_set_property(media_type& m, interface_type name, string_type v)
  {
    m.properties.start_set(name, v);
  }
  static void start_set_property(media_type& m, interface_type name, integer_type v)
  {
    m.properties.start_set(name, v);
  }
  static void commit_set_property(media_type& m, interface_type name)
  {
    m.properties.commit_set(name);
  }
  static property_type get_property(media_type const& m, interface_type name)
  {
    return *m.properties.find(name);
  }
  static property_range property_all(media_type const& m)
  {
    return property_range(m.properties.begin(), m.properties.end());
  }

  struct descriptor_predicate
  {
    descriptor_predicate(descriptor_type d)
      : d(d) {}
    typedef bool result_type;
    result_type operator()(presentation_type p) const
    {
      return d == presentation_traits::current_descriptor(p);
    }
    descriptor_type d;
  };

  static bool has_presentation(media_type const& m, descriptor_type d)
  {
    return std::find_if(m.presentations.begin()
                        , m.presentations.end()
                        , descriptor_predicate(d))
      != m.presentations.end();
  }

  static presentation_type get_presentation(media_type const& m
                                            , descriptor_type d)
  {
    return *std::find_if(m.presentations.begin()
                         , m.presentations.end()
                         , descriptor_predicate(d));
  }

  static presentation_range presentation_all(media_type& m)
  {
    return presentation_range(m.presentations.begin()
                              , m.presentations.end());
  }

  static presentation_type prepare_presentation(media_type& m, descriptor_type d)
  {
    typename std::vector<presentation_type>::const_iterator
      iterator = std::find_if(m.presentations.begin(), m.presentations.end(), descriptor_predicate(d));
    if(iterator != m.presentations.end())
    {
      assert(presentation_traits::is_sleeping(*iterator));
      return *iterator;
    }
    else
    {
      presentation_type p = m.presentation_factory(d);
      m.presentations.push_back(p);
      return p;
    }
  }

  static bool has_descriptor_identifier(media_type const& m)
  {
    return parser_media_traits::has_descriptor(m.parser_media);
  }
  static descriptor_identifier_type descriptor_identifier(media_type const& m)
  {
    return parser_media_traits::descriptor(m.parser_media);
  }
  static identifier_type identifier(media_type const& m)
  {
    return parser_media_traits::identifier(m.parser_media);
  }
  static bool has_source(media_type const& m)
  {
    return parser_media_traits::has_source(m.parser_media);
  }
  static source_type source(media_type const& m)
  {
    return parser_media_traits::source(m.parser_media);
  }
  static bool has_refer(media_type const& m)
  {
    return parser_media_traits::has_refer(m.parser_media);
  }
  static identifier_type refer(media_type const& m)
  {
    return parser_media_traits::refer(m.parser_media);
  }
  static bool has_instance(media_type const& m)
  {
    return parser_media_traits::has_instance(m.parser_media);
  }
  static instance_type instance(media_type const& m)
  {
    return parser_media_traits::instance(m.parser_media);
  }
  static bool has_type(media_type const& m)
  {
    return parser_media_traits::has_type(m.parser_media);
  }
  static type_type type(media_type const& m)
  {
    return parser_media_traits::type(m.parser_media);
  }
  static area_range area_all(media_type const& m)
  {
    return parser_media_traits::area_all(m.parser_media);
  }
  static bool has_player (media_type const& m)
  {
    return parser_media_traits::has_player (m.parser_media);
  }
  static player_type player (media_type const& m)
  {
    return parser_media_traits::player (m.parser_media);
  }
  static bool has_explicit_duration (media_type const& m)
  {
    return parser_media_traits::has_explicit_duration (m.parser_media);
  }
  static boost::posix_time::time_duration explicit_duration (media_type const& m)
  {
    return parser_media_traits::explicit_duration (m.parser_media);
  }
  static bool has_region (media_type const& m)
  {
    return parser_media_traits::has_region (m.parser_media);
  }
  static region_type region (media_type const& m)
  {
    return parser_media_traits::region (m.parser_media);
  }
  static bool has_freeze (media_type const& m)
  {
    return parser_media_traits::has_freeze (m.parser_media);
  }
  static bool freeze (media_type const& m)
  {
    return parser_media_traits::freeze (m.parser_media);
  }
  static bool has_move_left (media_type const& m)
  {
    return parser_media_traits::has_move_left (m.parser_media);
  }
  static int move_left (media_type const& m)
  {
    return parser_media_traits::move_left (m.parser_media);
  }
  static bool has_move_right (media_type const& m)
  {
    return parser_media_traits::has_move_right (m.parser_media);
  }
  static int move_right (media_type const& m)
  {
    return parser_media_traits::move_right (m.parser_media);
  }
  static bool has_move_up (media_type const& m)
  {
    return parser_media_traits::has_move_up (m.parser_media);
  }
  static int move_up (media_type const& m)
  {
    return parser_media_traits::move_up (m.parser_media);
  }
  static bool has_move_down (media_type const& m)
  {
    return parser_media_traits::has_move_down (m.parser_media);
  }
  static int move_down (media_type const& m)
  {
    return parser_media_traits::move_down (m.parser_media);
  }
  static bool has_focus_index (media_type const& m)
  {
    return parser_media_traits::has_focus_index (m.parser_media);
  }
  static int focus_index (media_type const& m)
  {
    return parser_media_traits::focus_index (m.parser_media);
  }
  static bool has_focus_border_color (media_type const& m)
  {
    return parser_media_traits::has_focus_border_color (m.parser_media);
  }
  static color_type focus_border_color (media_type const& m)
  {
    return parser_media_traits::focus_border_color (m.parser_media);
  }
  static bool has_focus_border_width (media_type const& m)
  {
    return parser_media_traits::has_focus_border_width (m.parser_media);
  }
  static int focus_border_width (media_type const& m)
  {
    return parser_media_traits::focus_border_width (m.parser_media);
  }
  static bool has_focus_border_transparency (media_type const& m)
  {
    return parser_media_traits::has_focus_border_transparency (m.parser_media);
  }
  static transparency_type focus_border_transparency (media_type const& m)
  {
    return parser_media_traits::focus_border_transparency (m.parser_media);
  }
  static bool has_focus_source (media_type const& m)
  {
    return parser_media_traits::has_focus_source (m.parser_media);
  }
  static source_type focus_source (media_type const& m)
  {
    return parser_media_traits::focus_source (m.parser_media);
  }
  static bool has_focus_selection_source (media_type const& m)
  {
    return parser_media_traits::has_focus_selection_source (m.parser_media);
  }
  static source_type focus_selection_source (media_type const& m)
  {
    return parser_media_traits::focus_selection_source (m.parser_media);
  }
  static bool has_selection_border_color (media_type const& m)
  {
    return parser_media_traits::has_selection_border_color (m.parser_media);
  }
  static color_type selection_border_color (media_type const& m)
  {
    return parser_media_traits::selection_border_color (m.parser_media);
  }
  static bool has_transition_in (media_type const& m)
  {
    return parser_media_traits::has_transition_in (m.parser_media);
  }
  static transition_type transition_in (media_type const& m)
  {
    return parser_media_traits::transition_in (m.parser_media);
  }
  static bool has_transition_out (media_type const& m)
  {
    return parser_media_traits::has_transition_out (m.parser_media);
  }
  static transition_type transition_out (media_type const& m)
  {
    return parser_media_traits::transition_out (m.parser_media);
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
