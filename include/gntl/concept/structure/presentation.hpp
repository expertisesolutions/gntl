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

#ifndef GNTL_CONCEPT_STRUCTURE_PRESENTATION_HPP
#define GNTL_CONCEPT_STRUCTURE_PRESENTATION_HPP

#include <gntl/concept/structure/unrestricted_tag.hpp>
#include <gntl/concept/structure/presentation_call_start.hpp>
#include <gntl/transition_enum.hpp>

#include <boost/optional.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/pop_front.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T, typename Enable = void>
struct presentation_traits
{
  typedef boost::mpl::true_ is_presentation;
};

template <typename T>
struct presentation_traits<T const> : presentation_traits<T>
{};

template <typename T>
struct presentation_traits<T, typename boost::enable_if<boost::is_reference_wrapper<T> >::type>
  : presentation_traits<typename boost::unwrap_reference<T>::type>
{
};
      
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Presentation
{
  typedef presentation_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_presentation::value, ==, true);
  typedef typename traits::start_function_overloads start_function_overloads;
  typedef typename traits::component_identifier component_identifier;
  typedef typename traits::time_duration time_duration;
  typedef typename traits::color_type color_type;
  typedef typename traits::descriptor_type descriptor_type;
  
  BOOST_CONCEPT_USAGE(Presentation)
  {
    start_check(boost::mpl::identity
                <typename boost::mpl::begin<start_function_overloads>::type>()
                , boost::mpl::identity
                <typename boost::mpl::end<start_function_overloads>::type>());
    convertible_to<bool>(traits::is_occurring(i));
    convertible_to<bool>(traits::is_paused(i));
    convertible_to<bool>(traits::is_sleeping(i));
    convertible_to<bool>(traits::is_focused(i));
    convertible_to<bool>(traits::is_selected(i));
    convertible_to<descriptor_type>(traits::current_descriptor(i));
    convertible_to<bool>(traits::start_set_property(i, property_name, property_value));
    convertible_to<bool>(traits::start_set_property(i, property_name, property_int_value));
    convertible_to<bool>(traits::commit_set_property(i, property_name));
    convertible_to<bool>(traits::wants_keys(i));
    //traits::pause(i);
    //traits::stop(i);
    //traits::natural_end(i);
    //traits::abort(i);
    //traits::resume(i);
    traits::focused(i);
    traits::selected(i);
    traits::reset_focus(i);
    traits::reset_selection(i);
    //traits::add_border(i, border_size, color);
    //traits::remove_border(i);
    traits::area_frame_begin (i, component_id, unsigned_int);
    traits::area_frame_end (i, component_id, unsigned_int);
    traits::area_frame_begin_end (i, component_id, unsigned_int, unsigned_int);
    traits::area_npt_begin (i, component_id, unsigned_int);
    traits::area_npt_end (i, component_id, unsigned_int);
    traits::area_npt_begin_end (i, component_id, unsigned_int, unsigned_int);
    traits::area_time_begin (i, component_id, time);
    traits::area_time_end (i, component_id, time);
    traits::area_time_begin_end (i, component_id, time, time);
    traits::start_area(i, component_id);
    traits::explicit_duration(i, time);
  }

  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  struct archetype_create
  {
    template <typename T>
    struct apply
    {
      typedef T type;
    };
    template <typename T>
    struct apply<unrestricted_tag<T> >
    {
      typedef typename unrestricted_tag<T>::type type;
    };
  };

  template <typename Iter, typename End>
  void start_check(Iter iter, End end)
  {
    start_check_seq(iter, end
                    , boost::mpl::bool_
                    <boost::is_same<Iter, End>::type::value>());
  }

  template <typename Iter, typename End>
  void start_check_seq(Iter, End end, boost::mpl::false_)
  {
    typedef typename Iter::type current_iterator;
    typedef typename boost::mpl::deref<current_iterator>::type overload_type;
    typedef typename boost::function_types::parameter_types
      <overload_type>::type overload_seq;
    typedef typename boost::mpl::transform<overload_seq, archetype_create>::type
      archetypes_overload_seq;
    typedef presentation_call_start<traits> call_start;
    boost::fusion::fused<call_start> fused;

    typedef typename boost::fusion::result_of::as_vector<archetypes_overload_seq>::type
      vector_type;
    vector_type* v = 0; // we must avoid default-constructing the sequence
    fused(*v);

    start_check_seq(boost::mpl::identity
                    <typename boost::mpl::next<current_iterator>::type>()
                    , end
                    , boost::mpl::bool_
                    <boost::is_same
                    <typename boost::mpl::next<current_iterator>::type
                    , typename End::type>::type::value>());
  }

  template <typename Iter, typename End>
  void start_check_seq(Iter iter, End end, boost::mpl::true_)
  {
  }

  gntl::transition_type transition;
  time_duration time;
  unsigned int unsigned_int;
  component_identifier component_id;
  int border_size;
  color_type color;
  std::string property_name, property_value;
  int property_int_value;
  X i;
};
#endif
}
      
template <typename P>
bool is_occurring
  (P const& p, typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::is_ocurring(p);
}

template <typename P>
bool is_paused
  (P const& p, typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::is_paused(p);
}

template <typename P>
bool is_sleeping
  (P const& p, typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::is_sleeping(p);
}

template <typename P>
bool is_focused
  (P const& p, typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::is_focused(p);
}

template <typename P>
bool is_selected
  (P const& p, typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::is_selected(p);
}

template <typename P>
typename structure::presentation_traits<P>::descriptor_type
current_descriptor(P const& p)
{
  return structure::presentation_traits<P>::current_descriptor(p);
}

template <typename P>
bool start_set_property
  (P& p, std::string const& name, std::string const& value
   , typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::start_set_property(p, name, value);
}

template <typename P>
bool start_set_property
  (P& p, std::string const& name, int value
   , typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::start_set_property(p, name, value);
}

template <typename P>
bool commit_set_property
  (P& p, std::string const& name
   , typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::commit_set_property(p, name);
}

template <typename P>
bool wants_keys
  (P const& p
   , typename boost::enable_if<typename structure::presentation_traits<P>::is_presentation>::type* = 0)
{
  return structure::presentation_traits<P>::wants_keys(p);
}
      
} }


#include <gntl/detail/pop_options.hpp>

#endif
