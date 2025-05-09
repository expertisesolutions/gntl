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

#ifndef GNTL_CONCEPT_STRUCTURE_EXECUTOR_HPP
#define GNTL_CONCEPT_STRUCTURE_EXECUTOR_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/structure/unrestricted_tag.hpp>
#include <gntl/concept/structure/executor_call_xxx.hpp>
#include <gntl/transition_enum.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/functional/adapter/fused.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/function_types/parameter_types.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct executor_traits
{
  typedef boost::mpl::false_ is_executor;
};

template <typename T>
struct asynchronous_executor_traits
{
    typedef boost::false_type is_asynchronous_executor;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Executor : boost::CopyConstructible<X>
{
  typedef executor_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_executor::value, ==, true);
  typedef typename traits::start_function_overloads start_function_overloads;
  typedef typename traits::stop_function_overloads stop_function_overloads;
  typedef typename traits::pause_function_overloads pause_function_overloads;
  typedef typename traits::resume_function_overloads resume_function_overloads;
  typedef typename traits::abort_function_overloads abort_function_overloads;
  typedef typename traits::component_identifier component_identifier;
  typedef typename traits::time_duration time_duration;
  typedef typename traits::color_type color_type;

  BOOST_CONCEPT_USAGE(Executor)
  {
    check_overloads<executor_detail::call_start<traits> >
      (boost::mpl::identity
       <typename boost::mpl::begin<start_function_overloads>::type>()
       , boost::mpl::identity
       <typename boost::mpl::end<start_function_overloads>::type>());
    check_overloads<executor_detail::call_stop<traits> >
      (boost::mpl::identity
       <typename boost::mpl::begin<stop_function_overloads>::type>()
       , boost::mpl::identity
       <typename boost::mpl::end<stop_function_overloads>::type>());
    check_overloads<executor_detail::call_pause<traits> >
      (boost::mpl::identity
       <typename boost::mpl::begin<pause_function_overloads>::type>()
       , boost::mpl::identity
       <typename boost::mpl::end<pause_function_overloads>::type>());
    check_overloads<executor_detail::call_resume<traits> >
      (boost::mpl::identity
       <typename boost::mpl::begin<resume_function_overloads>::type>()
       , boost::mpl::identity
       <typename boost::mpl::end<resume_function_overloads>::type>());
    check_overloads<executor_detail::call_abort<traits> >
      (boost::mpl::identity
       <typename boost::mpl::begin<abort_function_overloads>::type>()
       , boost::mpl::identity
       <typename boost::mpl::end<abort_function_overloads>::type>());
    //traits::remove_border(e);
    //traits::add_border(e, 1u, color);
    traits::area_time_begin(e, component_id, time);
    traits::area_time_end(e, component_id, time);
    traits::area_time_begin_end(e, component_id, time, time);
    traits::area_frame_begin(e, component_id, frame);
    traits::area_frame_end(e, component_id, frame);
    traits::area_frame_begin_end(e, component_id, frame, frame);
    traits::area_npt_begin(e, component_id, npt);
    traits::area_npt_end(e, component_id, npt);
    traits::area_npt_begin_end(e, component_id, npt, npt);
    traits::start_area(e, component_id);
    traits::explicit_duration(e, time);
    convertible_to<bool>(traits::start_set_property(e, property_name, property_value));
    convertible_to<bool>(traits::commit_set_property(e, property_name));
    convertible_to<bool>(traits::wants_keys(e));
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

  template <typename F, typename Iter, typename End>
  void check_overloads(Iter iter, End end)
  {
    check_overloads_seq<F>(iter, end
                           , boost::mpl::bool_
                           <boost::is_same<Iter, End>::type::value>());
  }

  template <typename F, typename Iter, typename End>
  void check_overloads_seq(Iter, End end, boost::mpl::false_)
  {
    typedef typename Iter::type current_iterator;
    typedef typename boost::mpl::deref<current_iterator>::type overload_type;
    typedef typename boost::function_types::parameter_types
      <overload_type>::type overload_seq;
    typedef typename boost::mpl::transform<overload_seq, archetype_create>::type
      archetypes_overload_seq;
    boost::fusion::fused<F> fused;

    typedef typename boost::fusion::result_of::as_vector<archetypes_overload_seq>::type
      vector_type;
    vector_type* v = 0; // we must avoid default-constructing the sequence
    fused(*v);

    check_overloads<F>(boost::mpl::identity
                       <typename boost::mpl::next<current_iterator>::type>()
                       , end);
  }

  template <typename F, typename Iter, typename End>
  void check_overloads_seq(Iter iter, End end, boost::mpl::true_)
  {
  }

  X e;
  gntl::transition_type transition;
  int npt;
  unsigned int frame;
  component_identifier component_id;
  time_duration time;
  color_type color;
  std::string property_name, property_value;
};

template <typename X>
struct AsynchronousExecutor : boost::CopyConstructible<X>
{
  typedef asynchronous_executor_traits<X> traits;
  BOOST_MPL_ASSERT_RELATION(traits::is_asynchronous_executor::value, ==, true);

  BOOST_CONCEPT_USAGE(AsynchronousExecutor)
  {
/*
    static void async_start(executor_type, Source
                            , boost::optional<Descriptor>, Dimensions
                            , Handler, ...);
    static void async_pause (executor_type, Handler, ...);
    static void async_stop (executor_type, Handler, ...);
    static void async_resume (executor_type, Handler, ...);
*/
  }
  
  template <typename To, typename From>
  void convertible_to(From const&)
  {
    BOOST_MPL_ASSERT((boost::is_convertible<From, To>));
  }

  X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
