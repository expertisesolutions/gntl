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

#if !defined(BOOST_PP_IS_ITERATING) || !BOOST_PP_IS_ITERATING

#ifndef GNTL_STRUCTURE_COMPOSED_PRESENTATION_HPP
#define GNTL_STRUCTURE_COMPOSED_PRESENTATION_HPP

#include <gntl/log/log.hpp>
#include <gntl/concept/structure/executor.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/detail/max_args.hpp>

#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_type.hpp>

#include <boost/optional.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Executor, typename StructureDescriptor>
struct presentation
{
  presentation(Executor&& e, StructureDescriptor descriptor)
    : shared_state_(new shared_state(std::forward<Executor>(e), descriptor)) {}

  typedef Executor executor_type;

  enum state_type
  {
    occurring
    , paused
    , sleeping
  };

  struct shared_state
  {
    Executor executor;
    StructureDescriptor descriptor;
    state_type state;
    std::size_t occurrences;
    bool focused;
    bool selected;

    shared_state(Executor&& e, StructureDescriptor descriptor)
      : executor(std::forward<Executor>(e)), descriptor(descriptor)
      , state(sleeping), occurrences(0)
      , focused(false), selected(false)
    {
      GNTL_DEBUG_LOG("New unique abstract entity for presentation " << this << std::endl)
    }

    ~shared_state()
    {
      GNTL_DEBUG_LOG("destroyed unique abstract entity for presentation " << this << std::endl)
    }
  };

  boost::shared_ptr<shared_state> shared_state_;

  Executor& executor() { return shared_state_->executor; }
  Executor const& executor() const { return shared_state_->executor; }
};

namespace presentation_detail {

template <typename State, typename Presentation, typename Executor
          , typename Function>
struct replace_executor
{
  typedef typename boost::function_types::parameter_types
    <Function>::type parameter_sequence;
  typedef typename boost::function_types::result_type
    <Function>::type result_type;
  BOOST_MPL_ASSERT((boost::is_same<void, result_type>));
  BOOST_MPL_ASSERT((boost::is_same<Executor
                                   , typename boost::mpl::deref
                                   <typename boost::mpl::begin<parameter_sequence>::type>::type>));

  typedef typename boost::mpl::push_front
  <
    typename boost::mpl::pop_front
    <
      parameter_sequence
    >::type
    , Presentation
  >::type new_parameter_sequence;

  typedef typename boost::mpl::push_back
  <
    State
    , typename boost::function_types::function_type
    <typename boost::mpl::push_front
     <new_parameter_sequence
      , result_type>::type
     >::type
  >::type type;
};

template <typename Presentation, typename Executor, typename Overloads>
struct replace_executors
{
  typedef typename boost::mpl::fold
  <Overloads
   , boost::mpl::vector0<>
   , replace_executor<boost::mpl::_, Presentation, Executor
                      , boost::mpl::_> >::type
  type;
};

}

} }

namespace concept { namespace structure {

template <typename Executor, typename Descriptor>
struct presentation_traits<gntl::structure::composed::presentation<Executor, Descriptor> >
{
  typedef boost::mpl::true_ is_presentation;
  typedef gntl::structure::composed::presentation<Executor, Descriptor> presentation_type;
  typedef typename boost::unwrap_reference<Executor>::type executor_type;
  typedef concept::structure::executor_traits<executor_type> executor_traits;
  typedef typename gntl::structure::composed::presentation_detail::replace_executors
  <presentation_type, Executor
   , typename executor_traits::start_function_overloads>::type
    start_function_overloads;
  typedef typename executor_traits::component_identifier component_identifier;
  typedef typename executor_traits::time_duration time_duration;
  typedef typename executor_traits::color_type color_type;
  typedef Descriptor descriptor_type;

  GNTL_CONCEPT_ASSERT((concept::structure::Executor<Executor>));

  static bool is_occurring(presentation_type const& p)
  {
    return p.shared_state_->state == presentation_type::occurring;
  }

  static bool is_paused(presentation_type const& p)
  {
    return p.shared_state_->state == presentation_type::paused;
  }

  static bool is_sleeping(presentation_type const& p)
  {
    return p.shared_state_->state == presentation_type::sleeping;
  }

  static bool is_focused(presentation_type const& p)
  {
    return p.shared_state_->focused;
  }

  static bool is_selected(presentation_type const& p)
  {
    return p.shared_state_->selected;
  }

  static void focused(presentation_type& p)
  {
    p.shared_state_->focused = true;
  }
  static void selected(presentation_type& p)
  {
    p.shared_state_->focused = true;
  }
  static void reset_focus(presentation_type& p)
  {
    p.shared_state_->focused = false;
  }
  static void reset_selection(presentation_type& p)
  {
    p.shared_state_->focused = false;
  }
  static bool wants_keys(presentation_type const& p)
  {
    return executor_traits::wants_keys(p.shared_state_->executor);
  }

  static Descriptor current_descriptor(presentation_type const& p)
  {
    return p.shared_state_->descriptor;
  }

  static void add_border(presentation_type& p, int border, color_type color)
  {
    executor_traits::add_border(p.shared_state_->executor, border, color);
  }
  static void remove_border(presentation_type& p)
  {
    executor_traits::remove_border(p.shared_state_->executor);
  }

  static void area_frame_begin(presentation_type& p, component_identifier i, unsigned int frame)
  {
    executor_traits::area_frame_begin(p.shared_state_->executor, i, frame);
  }

  static void area_frame_end(presentation_type& p, component_identifier i, unsigned int frame)
  {
    executor_traits::area_frame_begin(p.shared_state_->executor, i, frame);
  }

  static void area_frame_begin_end(presentation_type& p, component_identifier i, unsigned int begin_frame
                                   , unsigned int end_frame)
  {
    executor_traits::area_frame_begin_end(p.shared_state_->executor, i, begin_frame, end_frame);
  }

  static void area_npt_begin(presentation_type& p, component_identifier i, unsigned int npt)
  {
    executor_traits::area_npt_begin(p.shared_state_->executor, i, npt);
  }

  static void area_npt_end(presentation_type& p, component_identifier i, unsigned int npt)
  {
    executor_traits::area_npt_end(p.shared_state_->executor, i, npt);
  }

  static void area_npt_begin_end(presentation_type& p, component_identifier i, unsigned int begin_npt
                                 , unsigned int end_npt)
  {
    executor_traits::area_npt_begin_end(p.shared_state_->executor, i, begin_npt, end_npt);
  }

  static void area_time_begin(presentation_type& p, component_identifier i, time_duration time)
  {
    executor_traits::area_time_begin(p.shared_state_->executor, i, time);
  }

  static void area_time_end(presentation_type& p, component_identifier i, time_duration time)
  {
    executor_traits::area_time_end(p.shared_state_->executor, i, time);
  }

  static void area_time_begin_end(presentation_type& p, component_identifier i, time_duration begin_time
                                  , time_duration end_time)
  {
    executor_traits::area_time_begin_end(p.shared_state_->executor, i, begin_time, end_time);
  }

  static void explicit_duration(presentation_type& p, time_duration explicit_duration)
  {
    executor_traits::explicit_duration(p.shared_state_->executor, explicit_duration);
  }

  static void start_area(presentation_type& p, component_identifier area)
  {
    executor_traits::start_area(p.shared_state_->executor, area);
  }

  static bool start_set_property(presentation_type& p, std::string property_name, std::string property_value)
  {
    return executor_traits::start_set_property(p.shared_state_->executor, property_name, property_value);
  }

  static bool start_set_property(presentation_type& p, std::string property_name, int value)
  {
    return executor_traits::start_set_property(p.shared_state_->executor, property_name, value);
  }
  
  static bool commit_set_property(presentation_type& p, std::string property_name)
  {
    return executor_traits::commit_set_property(p.shared_state_->executor, property_name);
  }

#define BOOST_PP_ITERATION_PARAMS_1 (3, (1, GNTL_MAX_ARGS, "gntl/structure/composed/presentation.hpp"))
#include BOOST_PP_ITERATE ()

  static void start(presentation_type& p)
  {
    // If you have an error here, then you probably forgot to to
    // implement the correct static start function in your
    // presentation_traits.
    executor_traits::start(p.shared_state_->executor);
    p.shared_state_->state = presentation_type::occurring;
  }
  static void pause(presentation_type& p)
  {
    // If you have an error here, then you probably forgot to to
    // implement the correct static start function in your
    // presentation_traits.
    executor_traits::pause(p.shared_state_->executor);
    p.shared_state_->state = presentation_type::paused;
  }
  static void stop(presentation_type& p)
  {
    executor_traits::stop(p.shared_state_->executor);
    ++p.shared_state_->occurrences;
    p.shared_state_->state = presentation_type::sleeping;
  }
  static void natural_end(presentation_type& p)
  {
    ++p.shared_state_->occurrences;
    p.shared_state_->state = presentation_type::sleeping;
  }
  static void abort(presentation_type& p)
  {
    executor_traits::abort(p.shared_state_->executor);
    p.shared_state_->state = presentation_type::sleeping;
  }
  static void resume(presentation_type& p)
  {
    executor_traits::resume(p.shared_state_->executor);
    p.shared_state_->state = presentation_type::occurring;
  }
};

} } }

#include <gntl/detail/pop_options.hpp>

#endif
#else
template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename A)>
static void start(presentation_type& p BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PP_ITERATION(), A, a))
{
  // If you have an error here, then you probably forgot to to
  // implement the correct static start function in your
  // presentation_traits.
  executor_traits::start
    (p.shared_state_->executor BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_ITERATION(), a));
  p.shared_state_->state = presentation_type::occurring;
}
#endif
