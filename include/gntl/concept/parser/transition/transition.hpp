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

#ifndef GNTL_CONCEPT_PARSER_TRANSITION_HPP
#define GNTL_CONCEPT_PARSER_TRANSITION_HPP

#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct transition_traits
{
  typedef boost::mpl::false_ is_transition;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Transition : boost::CopyConstructible<X>
{
    typedef transition_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_transition::value, ==, true);
    typedef typename traits::identifier_type identifier_type;
    typedef typename traits::type_type type_type;
    typedef typename traits::duration_type duration_type;
    typedef typename traits::start_progress_type start_progress_type;
    typedef typename traits::end_progress_type end_progress_type;
    typedef typename traits::direction_type direction_type;
    typedef typename traits::fade_color_type fade_color_type;
    typedef typename traits::horizontal_repeat_type horizontal_repeat_type;
    typedef typename traits::vertical_repeat_type vertical_repeat_type;
    typedef typename traits::border_width_type border_width_type;
    typedef typename traits::border_color_type border_color_type;

    BOOST_CONCEPT_USAGE (Transition)
    {
      convertible_to<identifier_type>(traits::identifier (i));
      convertible_to<type_type>(traits::type (i));
      convertible_to<duration_type>(traits::duration (i));
      convertible_to<bool>(traits::has_duration (i));
      convertible_to<start_progress_type>(traits::start_progress (i));
      convertible_to<bool>(traits::has_start_progress (i));
      convertible_to<end_progress_type>(traits::end_progress (i));
      convertible_to<bool>(traits::has_end_progress (i));
      convertible_to<direction_type>(traits::direction (i));
      convertible_to<bool>(traits::has_direction (i));
      convertible_to<fade_color_type>(traits::fade_color (i));
      convertible_to<bool>(traits::has_fade_color (i));
      convertible_to<horizontal_repeat_type>(traits::horizontal_repeat (i));
      convertible_to<bool>(traits::has_horizontal_repeat (i));
      convertible_to<vertical_repeat_type>(traits::vertical_repeat (i));
      convertible_to<bool>(traits::has_vertical_repeat (i));
      convertible_to<border_width_type>(traits::border_width (i));
      convertible_to<bool>(traits::has_border_width (i));
      convertible_to<border_color_type>(traits::border_color (i));
      convertible_to<bool>(traits::has_border_color (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1, T0>));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
