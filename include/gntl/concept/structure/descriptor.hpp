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

#ifndef GNTL_CONCEPT_STRUCTURE_DESCRIPTOR_HPP
#define GNTL_CONCEPT_STRUCTURE_DESCRIPTOR_HPP

#include <gntl/concept/rgb_color.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T, typename Enable = void>
struct descriptor_traits
{
  typedef boost::mpl::false_ is_descriptor;
};

template <typename T>
struct descriptor_traits<T const> : descriptor_traits<T>
{};

template <typename T>
struct descriptor_traits<T, typename boost::enable_if<boost::is_reference_wrapper<T> >::type>
  : descriptor_traits<typename boost::unwrap_reference<T>::type>
{};
      
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Descriptor : boost::CopyConstructible<X>
  , boost::EqualityComparable<X>
{
    typedef descriptor_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_descriptor::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::player_type player_type;
    typedef typename traits::explicit_duration_type explicit_duration_type;
    typedef typename traits::region_type region_type;
    typedef typename traits::document_uri_type document_uri_type;
    typedef typename traits::freeze_type freeze_type;
    typedef typename traits::focus_index_type focus_index_type;
    typedef typename traits::width_type width_type;
    typedef typename traits::transparency_type transparency_type;
    typedef typename traits::source_type source_type;
    typedef typename traits::color_type color_type;
    typedef typename traits::transition_type transition_type;

    BOOST_CONCEPT_ASSERT((RGB_Color<color_type>));

    BOOST_CONCEPT_USAGE (Descriptor)
    {
        convertible_to<identifier_type>(traits::identifier (i));
        convertible_to<bool>(traits::has_player (i));
        traits::set_player(i, player);
        convertible_to<player_type>(traits::player (i));
        convertible_to<bool>(traits::has_explicit_duration (i));
        traits::set_explicit_duration (i, explicit_duration);
        convertible_to<explicit_duration_type>(traits::explicit_duration (i));
        convertible_to<bool>(traits::has_region (i));
        traits::set_region (i, region);
        convertible_to<region_type>(traits::region (i));
        traits::set_region_document_uri (i, document_uri);
        convertible_to<document_uri_type>(traits::region_document_uri (i));
        convertible_to<bool>(traits::has_freeze (i));
        traits::set_freeze (i, freeze);
        convertible_to<freeze_type>(traits::freeze (i));
        convertible_to<bool>(traits::has_move_left (i));
        traits::set_move_left (i, focus_index);
        convertible_to<focus_index_type>(traits::move_left (i));
        convertible_to<bool>(traits::has_move_right (i));
        traits::set_move_right (i, focus_index);
        convertible_to<focus_index_type>(traits::move_right (i));
        convertible_to<bool>(traits::has_move_up (i));
        traits::set_move_up (i, focus_index);
        convertible_to<focus_index_type>(traits::move_up (i));
        convertible_to<bool>(traits::has_move_down (i));
        traits::set_move_down (i, focus_index);
        convertible_to<focus_index_type>(traits::move_down (i));
        convertible_to<bool>(traits::has_focus_index (i));
        traits::set_focus_index (i, focus_index);
        convertible_to<focus_index_type>(traits::focus_index (i));
        convertible_to<bool>(traits::has_focus_border_color (i));
        traits::set_focus_border_color (i, color);
        convertible_to<color_type>(traits::focus_border_color (i));
        convertible_to<bool>(traits::has_focus_border_width (i));
        traits::set_focus_border_width (i, width);
        convertible_to<width_type>(traits::focus_border_width (i));
        convertible_to<bool>(traits::has_focus_border_transparency (i));
        traits::set_focus_border_transparency (i, transparency);
        convertible_to<transparency_type>(traits::focus_border_transparency (i));
        convertible_to<bool>(traits::has_focus_source (i));
        traits::set_focus_source (i, source);
        convertible_to<source_type>(traits::focus_source (i));
        convertible_to<bool>(traits::has_focus_selection_source (i));
        traits::set_focus_selection_source (i, source);
        convertible_to<source_type>(traits::focus_selection_source (i));
        convertible_to<bool>(traits::has_selection_border_color (i));
        traits::set_selection_border_color (i, color);
        convertible_to<color_type>(traits::selection_border_color (i));
        convertible_to<bool>(traits::has_transition_in (i));
        traits::set_transition_in (i, transition);
        convertible_to<transition_type>(traits::transition_in (i));
        convertible_to<bool>(traits::has_transition_out (i));
        traits::set_transition_out (i, transition);
        convertible_to<transition_type>(traits::transition_out (i));
        convertible_to<X>(traits::compose (i, i));
    }

    void is_descriptor(X const&);

    template <typename D>
    void is_descriptor(D const&)
    {
      BOOST_CONCEPT_ASSERT((Descriptor<D>));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T0, T1>));
    }

    X i;
    player_type player;
    explicit_duration_type explicit_duration;
    region_type region;
    document_uri_type document_uri;
    freeze_type freeze;
    focus_index_type focus_index;
    color_type color;
    width_type width;
    transparency_type transparency;
    source_type source;
    transition_type transition;
};
#endif
}

template <typename D>
bool has_explicit_duration
  (D const& d, typename boost::enable_if<typename structure::descriptor_traits<D>::is_descriptor>::type* = 0)
{
  return structure::descriptor_traits<D>::has_explicit_duration(d);
}

template <typename D>
void set_explicit_duration
  (D& d, typename structure::descriptor_traits<D>::explicit_duration_type duration)
{
  structure::descriptor_traits<D>::set_explicit_duration(d, duration);
}

template <typename D>
typename structure::descriptor_traits<D>::explicit_duration_type
set_explicit_duration (D const& d)
{
  return structure::descriptor_traits<D>::explicit_duration(d);
}

} }


#include <gntl/detail/pop_options.hpp>

#endif
