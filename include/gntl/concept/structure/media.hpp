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

#ifndef GNTL_CONCEPT_STRUCTURE_MEDIA_HPP
#define GNTL_CONCEPT_STRUCTURE_MEDIA_HPP

#include <gntl/concept/parser/media/media.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept/structure/property.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/ref.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/optional.hpp>

#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T, typename Enable = void>
struct media_traits
{
    typedef boost::false_type is_media;
};

template <typename T>
struct media_traits<T const> : media_traits<T>
{};

template <typename T>
struct media_traits<T, typename boost::enable_if<boost::is_reference_wrapper<T> >::type>
  : media_traits<typename boost::unwrap_reference<T>::type>
{};

/*
template <>
struct media_traits : concept::parser::media_traits<media_type>
{
    typedef boost::true_type is_media;
    typedef typename T::executor_type executor_type;
    typedef typename T::identifier_type identifier_type;
    typedef typename T::interface_type interface_type;

    static executor_type executor (media_type);
    static identifier_type identifier (media_type);
    static interface_type interface (media_type);
    static bool is_running (media_type);
    static bool is_paused (media_type);
    static bool is_stopped (media_type);
    static bool is_selected (media_type);
    static bool is_focused (media_type);
    static void running (media_type);
    static void pause (media_type);
    static void stop (media_type);
};
*/

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Media
{
    typedef media_traits<X> traits;
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::source_type source_type;
    typedef typename traits::instance_type instance_type;
    typedef typename traits::type_type type_type;
    typedef typename traits::interface_type interface_type;
    typedef typename traits::string_type string_type;
    typedef typename traits::integer_type integer_type;
    typedef typename traits::descriptor_type descriptor_type;
    typedef typename traits::descriptor_identifier_type descriptor_identifier_type;
    typedef typename traits::presentation_type presentation_type;
    typedef typename traits::presentation_range presentation_range;
    typedef typename traits::area_range area_range;
    typedef typename traits::property_type property_type;
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

    BOOST_CONCEPT_ASSERT((Descriptor<descriptor_type>));
    BOOST_CONCEPT_ASSERT((Presentation<presentation_type>));
    BOOST_CONCEPT_ASSERT((Property<property_type>));

    BOOST_CONCEPT_USAGE (Media)
    {
        convertible_to<bool>(traits::has_presentation (const_i, descriptor));
        convertible_to<presentation_type>(traits::prepare_presentation (i, descriptor));
        convertible_to<presentation_type>(traits::get_presentation (i, descriptor));
        convertible_to<presentation_range>(traits::presentation_all(i));
        convertible_to<identifier_type>(traits::identifier (const_i));
        convertible_to<bool>(traits::has_source (const_i));
        convertible_to<source_type>(traits::source (const_i));
        convertible_to<bool>(traits::has_refer (const_i));
        convertible_to<identifier_type>(traits::refer (const_i));
        convertible_to<bool>(traits::has_instance (const_i));
        convertible_to<instance_type>(traits::instance (const_i));
        convertible_to<bool>(traits::is_same_instance_refer (const_i));
        convertible_to<identifier_type>(traits::same_instance_referred (const_i));

        convertible_to<bool>(traits::has_type (const_i));
        convertible_to<type_type>(traits::type (const_i));
        convertible_to<bool>(traits::has_descriptor_identifier (const_i));
        convertible_to<descriptor_identifier_type>(traits::descriptor_identifier (const_i));
        convertible_to<area_range>(traits::area_all(i));
        convertible_to<bool>(traits::has_property (const_i, property_name));
        traits::start_set_property(i, property_name, property_string);
        traits::start_set_property(i, property_name, property_integer);
        traits::commit_set_property(i, property_name);
        convertible_to<property_type>(traits::get_property(const_i, property_name));
        convertible_to<property_range>(traits::property_all(const_i));

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

    Media() : const_i() {}

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_STATIC_ASSERT ((boost::is_convertible<T1,T0>::type::value));
    }

    descriptor_type descriptor;
    interface_type property_name;
    string_type property_string;
    integer_type property_integer;
    identifier_type identifier;
    X i;
    X const const_i;
};
#endif

} // end of structure namespace

template <typename M>
inline
bool has_presentation
 (M const& m, typename structure::media_traits<M>::descriptor_type descriptor)
{
  return structure::media_traits<M>::has_presentation (m, descriptor);
}
      
template <typename M>
inline
typename structure::media_traits<M>::presentation_type
prepare_presentation
  (M& i
   , typename structure::media_traits<M>::descriptor_type descriptor)
{
  return structure::media_traits<M>::prepare_presentation (i, descriptor);
}
      
template <typename M>
inline
typename structure::media_traits<M>::presentation_type
get_presentation
  (M& i
   , typename structure::media_traits<M>::descriptor_type descriptor)
{
  return structure::media_traits<M>::get_presentation (i, descriptor);
}

template <typename M>
inline
typename structure::media_traits<M>::presentation_range
presentation_all(M& i)
{
  return structure::media_traits<M>::presentation_all(i);
}

template <typename M>
inline
typename structure::media_traits<M>::identifier_type
identifier(M const& const_i)
{
  return structure::media_traits<M>::identifier (const_i);
}

// convertible_to<bool>(traits::has_source (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_source(M const& const_i)
{
  return structure::media_traits<M>::has_source (const_i);
}


// convertible_to<source_type>(traits::source (const_i));
template <typename M>
inline
typename structure::media_traits<M>::source_type
source(M const& const_i)
{
  return structure::media_traits<M>::source (const_i);
}

// convertible_to<bool>(traits::has_refer (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_refer(M const& const_i)
{
  return structure::media_traits<M>::has_refer (const_i);
}

// convertible_to<identifier_type>(traits::refer (const_i));
template <typename M>
inline
typename structure::media_traits<M>::identifier_type
refer(M const& const_i)
{
  return structure::media_traits<M>::refer (const_i);
}

// convertible_to<bool>(traits::has_instance (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_instance(M const& const_i)
{
  return structure::media_traits<M>::has_instance (const_i);
}

// convertible_to<instance_type>(traits::instance (const_i));
template <typename M>
inline
typename structure::media_traits<M>::instance_type
instance(M const& const_i)
{
  return structure::media_traits<M>::instance (const_i);
}

// convertible_to<bool>(traits::is_same_instance_refer (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
is_same_instance_refer(M const& const_i)
{
  return structure::media_traits<M>::is_same_instance_refer (const_i);
}

// convertible_to<identifier_type>(traits::same_instance_referred (const_i));
template <typename M>
inline
typename structure::media_traits<M>::identifier_type
same_instance_referred(M const& const_i)
{
  return structure::media_traits<M>::same_instance_referred (const_i);
}

// convertible_to<bool>(traits::has_type (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_type(M const& const_i)
{
  return structure::media_traits<M>::has_type (const_i);
}

// convertible_to<type_type>(traits::type (const_i));
template <typename M>
inline
typename structure::media_traits<M>::type_type
type(M const& const_i)
{
  return structure::media_traits<M>::type (const_i);
}

// convertible_to<bool>(traits::has_descriptor_identifier (const_i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_descriptor_identifier(M const& const_i)
{
  return structure::media_traits<M>::has_descriptor_identifier (const_i);
}

// convertible_to<descriptor_identifier_type>(traits::descriptor_identifier (const_i));
template <typename M>
inline
typename structure::media_traits<M>::descriptor_identifier_type
descriptor_identifier(M const& const_i)
{
  return structure::media_traits<M>::descriptor_identifier (const_i);
}

// convertible_to<area_range>(traits::area_all(i));
template <typename M>
inline
typename structure::media_traits<M>::area_range
area_all(M& i)
{
  return structure::media_traits<M>::area_all (i);
}

// convertible_to<bool>(traits::has_property (const_i, property_name));
template <typename M>
inline
bool has_property
 (M const& const_i
   , typename structure::media_traits<M>::interface_type property_name)
{
  return structure::media_traits<M>::has_property (const_i, property_name);
}

// traits::start_set_property(i, property_name, property_string);
template <typename M>
inline
void start_set_property
 (M& i
   , typename structure::media_traits<M>::interface_type property_name
   , typename structure::media_traits<M>::string_type property_string)
{
  structure::media_traits<M>::start_set_property (i, property_name, property_string);
}

// traits::start_set_property(i, property_name, property_integer);
template <typename M>
inline
void start_set_property
 (M& i
   , typename structure::media_traits<M>::interface_type property_name
   , typename structure::media_traits<M>::integer_type property_integer)
{
  structure::media_traits<M>::start_set_property (i, property_name, property_integer);
}

// traits::commit_set_property(i, property_name);
template <typename M>
inline
void commit_set_property
 (M& i
   , typename structure::media_traits<M>::interface_type property_name)
{
  structure::media_traits<M>::commit_set_property (i, property_name);
}

// convertible_to<property_type>(traits::get_property(const_i, property_name));
template <typename M>
inline
typename structure::media_traits<M>::property_type
get_property
 (M const& const_i
   , typename structure::media_traits<M>::interface_type property_name)
{
  return structure::media_traits<M>::get_property (const_i, property_name);
}

// convertible_to<property_range>(traits::property_all(const_i));
template <typename M>
inline
typename structure::media_traits<M>::property_range
property_all(M const& const_i)
{
  return structure::media_traits<M>::property_all (const_i);
}

// 
// properties
//

// convertible_to<player_type>(traits::player (i));
template <typename M>
inline
typename structure::media_traits<M>::player_type
player(M& i)
{
  return structure::media_traits<M>::player (i);
}

// convertible_to<bool>(traits::has_explicit_duration (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_explicit_duration(M& i)
{
  return structure::media_traits<M>::has_explicit_duration (i);
}

// convertible_to<explicit_duration_type>(traits::explicit_duration (i));
template <typename M>
inline
typename structure::media_traits<M>::explicit_duration_type
explicit_duration(M& i)
{
  return structure::media_traits<M>::explicit_duration (i);
}

// convertible_to<bool>(traits::has_region (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_region(M& i)
{
  return structure::media_traits<M>::has_region (i);
}

// convertible_to<region_type>(traits::region (i));
template <typename M>
inline
typename structure::media_traits<M>::region_type
region(M& i)
{
  return structure::media_traits<M>::region (i);
}

// convertible_to<bool>(traits::has_freeze (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_freeze(M& i)
{
  return structure::media_traits<M>::has_freeze (i);
}

// convertible_to<freeze_type>(traits::freeze (i));
template <typename M>
inline
typename structure::media_traits<M>::freeze_type
freeze(M& i)
{
  return structure::media_traits<M>::freeze (i);
}

// convertible_to<bool>(traits::has_move_left (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_move_left(M& i)
{
  return structure::media_traits<M>::has_move_left (i);
}

// convertible_to<focus_index_type>(traits::move_left (i));
template <typename M>
inline
typename structure::media_traits<M>::focus_index_type
move_left(M& i)
{
  return structure::media_traits<M>::move_left (i);
}

// convertible_to<bool>(traits::has_move_right (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_move_right(M& i)
{
  return structure::media_traits<M>::has_move_right (i);
}

// convertible_to<focus_index_type>(traits::move_right (i));
template <typename M>
inline
typename structure::media_traits<M>::focus_index_type
move_right(M& i)
{
  return structure::media_traits<M>::move_right (i);
}

// convertible_to<bool>(traits::has_move_up (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_move_up(M& i)
{
  return structure::media_traits<M>::has_move_up (i);
}

// convertible_to<focus_index_type>(traits::move_up (i));
template <typename M>
inline
typename structure::media_traits<M>::focus_index_type
move_up(M& i)
{
  return structure::media_traits<M>::move_up (i);
}

// convertible_to<bool>(traits::has_move_down (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_move_down(M& i)
{
  return structure::media_traits<M>::has_move_down (i);
}

// convertible_to<focus_index_type>(traits::move_down (i));
template <typename M>
inline
typename structure::media_traits<M>::focus_index_type
move_down(M& i)
{
  return structure::media_traits<M>::move_down (i);
}

// convertible_to<bool>(traits::has_focus_index (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_index(M& i)
{
  return structure::media_traits<M>::has_focus_index (i);
}

// convertible_to<focus_index_type>(traits::focus_index (i));
template <typename M>
inline
typename structure::media_traits<M>::focus_index_type
focus_index(M& i)
{
  return structure::media_traits<M>::focus_index (i);
}

// convertible_to<bool>(traits::has_focus_border_color (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_border_color(M& i)
{
  return structure::media_traits<M>::has_focus_border_color (i);
}

// convertible_to<color_type>(traits::focus_border_color (i));
template <typename M>
inline
typename structure::media_traits<M>::color_type
focus_border_color(M& i)
{
  return structure::media_traits<M>::focus_border_color (i);
}

// convertible_to<bool>(traits::has_focus_border_width (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_border_width(M& i)
{
  return structure::media_traits<M>::has_focus_border_width (i);
}

// convertible_to<width_type>(traits::focus_border_width (i));
template <typename M>
inline
typename structure::media_traits<M>::width_type
focus_border_width(M& i)
{
  return structure::media_traits<M>::focus_border_width (i);
}

// convertible_to<bool>(traits::has_focus_border_transparency (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_border_transparency(M& i)
{
  return structure::media_traits<M>::has_focus_border_transparency (i);
}

// convertible_to<transparency_type>(traits::focus_border_transparency (i));
template <typename M>
inline
typename structure::media_traits<M>::transparency_type
focus_border_transparency(M& i)
{
  return structure::media_traits<M>::focus_border_transparency (i);
}

// convertible_to<bool>(traits::has_focus_source (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_source(M& i)
{
  return structure::media_traits<M>::has_focus_source (i);
}

// convertible_to<source_type>(traits::focus_source (i));
template <typename M>
inline
typename structure::media_traits<M>::source_type
focus_source(M& i)
{
  return structure::media_traits<M>::focus_source (i);
}

// convertible_to<bool>(traits::has_focus_selection_source (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_focus_selection_source(M& i)
{
  return structure::media_traits<M>::has_focus_selection_source (i);
}

// convertible_to<source_type>(traits::focus_selection_source (i));
template <typename M>
inline
typename structure::media_traits<M>::source_type
focus_selection_source(M& i)
{
  return structure::media_traits<M>::focus_selection_source (i);
}

// convertible_to<bool>(traits::has_selection_border_color (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_selection_border_color(M& i)
{
  return structure::media_traits<M>::has_selection_border_color (i);
}

// convertible_to<color_type>(traits::selection_border_color (i));
template <typename M>
inline
typename structure::media_traits<M>::color_type
selection_border_color(M& i)
{
  return structure::media_traits<M>::selection_border_color (i);
}

// convertible_to<bool>(traits::has_transition_in (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_transition_in(M& i)
{
  return structure::media_traits<M>::has_transition_in (i);
}

// convertible_to<transition_type>(traits::transition_in (i));
template <typename M>
inline
typename structure::media_traits<M>::transition_type
transition_in(M& i)
{
  return structure::media_traits<M>::transition_in (i);
}

// convertible_to<bool>(traits::has_transition_out (i));
template <typename M>
inline
typename boost::enable_if<typename structure::media_traits<M>::is_media, bool>::type
has_transition_out(M& i)
{
  return structure::media_traits<M>::has_transition_out (i);
}

// convertible_to<transition_type>(traits::transition_out (i));
template <typename M>
inline
typename structure::media_traits<M>::transition_type
transition_out(M& i)
{
  return structure::media_traits<M>::transition_out (i);
}

} } // end of gntl::concept namespace


#include <gntl/detail/pop_options.hpp>

#endif
