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

#ifndef GNTL_CONCEPT_PARSER_MEDIA_HPP
#define GNTL_CONCEPT_PARSER_MEDIA_HPP

#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct media_traits
{
  typedef boost::mpl::false_ is_media;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Media
{
    typedef media_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_media::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::source_type source_type;
    typedef typename traits::instance_type instance_type;
    typedef typename traits::type_type type_type;
    typedef typename traits::descriptor_type descriptor_type;
    typedef typename traits::area_range area_range;
    typedef typename traits::property_range property_range;
    typedef typename traits::player_type player_type;
    typedef typename traits::explicit_duration_type explicit_duration_type;
    typedef typename traits::region_type region_type;
    typedef typename traits::freeze_type freeze_type;
    typedef typename traits::focus_index_type focus_index_type;
    typedef typename traits::color_type color_type;
    typedef typename traits::width_type width_type;
    typedef typename traits::transparency_type transparency_type;
    typedef typename traits::transition_type transition_type;

    BOOST_CONCEPT_ASSERT ((boost::SinglePassRangeConcept<area_range>));

  
    BOOST_CONCEPT_USAGE (Media)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<bool>(traits::has_source (i));
        convertible_to<source_type>(traits::source (i));
        convertible_to<bool>(traits::has_refer (i));
        convertible_to<identifier_type>(traits::refer (i));
        convertible_to<bool>(traits::has_instance (i));
        convertible_to<instance_type>(traits::instance (i));
        convertible_to<bool>(traits::has_type (i));
        convertible_to<type_type>(traits::type (i));
        convertible_to<bool>(traits::has_descriptor (i));
        convertible_to<descriptor_type>(traits::descriptor (i));
        convertible_to<area_range>(traits::area_all (i));
        convertible_to<property_range>(traits::property_all (i));
        // properties
        convertible_to<player_type>(traits::player (i));
        convertible_to<bool>(traits::has_explicit_duration (i));
        convertible_to<explicit_duration_type>(traits::explicit_duration (i));
        convertible_to<bool>(traits::has_region (i));
        convertible_to<region_type>(traits::region (i));
        convertible_to<bool>(traits::has_freeze (i));
        convertible_to<freeze_type>(traits::freeze (i));
        convertible_to<bool>(traits::has_move_left (i));
        convertible_to<focus_index_type>(traits::move_left (i));
        convertible_to<bool>(traits::has_move_right (i));
        convertible_to<focus_index_type>(traits::move_right (i));
        convertible_to<bool>(traits::has_move_up (i));
        convertible_to<focus_index_type>(traits::move_up (i));
        convertible_to<bool>(traits::has_move_down (i));
        convertible_to<focus_index_type>(traits::move_down (i));
        convertible_to<bool>(traits::has_focus_index (i));
        convertible_to<focus_index_type>(traits::focus_index (i));
        convertible_to<bool>(traits::has_focus_border_color (i));
        convertible_to<color_type>(traits::focus_border_color (i));
        convertible_to<bool>(traits::has_focus_border_width (i));
        convertible_to<width_type>(traits::focus_border_width (i));
        convertible_to<bool>(traits::has_focus_border_transparency (i));
        convertible_to<transparency_type>(traits::focus_border_transparency (i));
        convertible_to<bool>(traits::has_focus_source (i));
        convertible_to<source_type>(traits::focus_source (i));
        convertible_to<bool>(traits::has_focus_selection_source (i));
        convertible_to<source_type>(traits::focus_selection_source (i));
        convertible_to<bool>(traits::has_selection_border_color (i));
        convertible_to<color_type>(traits::selection_border_color (i));
        convertible_to<bool>(traits::has_transition_in (i));
        convertible_to<transition_type>(traits::transition_in (i));
        convertible_to<bool>(traits::has_transition_out (i));
        convertible_to<transition_type>(traits::transition_out (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
