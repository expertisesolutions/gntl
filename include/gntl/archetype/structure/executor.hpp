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

#ifndef GNTL_ARCHETYPE_STRUCTURE_EXECUTOR_HPP
#define GNTL_ARCHETYPE_STRUCTURE_EXECUTOR_HPP

#include <gntl/concept/structure/executor.hpp>
#include <gntl/parser/libxml2/dom/color.hpp>
#include <gntl/algorithm/structure/media/dimensions.hpp>
#include <boost/mpl/vector.hpp>

namespace gntl { namespace archetype { namespace structure {

struct executor {};

} }

namespace concept { namespace structure {

template <>
struct executor_traits<archetype::structure::executor>
{
  typedef boost::mpl::true_ is_executor;
  typedef archetype::structure::executor executor_type;
  typedef boost::mpl::vector1
  <void(executor_type/*, gntl::concept::structure::unrestricted_tag<std::string>
        , gntl::concept::structure::unrestricted_tag<boost::optional<int> >
        , gntl::algorithm::structure::media::dimensions
        , int, gntl::concept::structure::unrestricted_tag
        <gntl::parser::libxml2::dom::color>*/)> start_function_overloads;
  typedef boost::mpl::vector1
  <void(executor_type)> stop_function_overloads;
  typedef boost::mpl::vector1
  <void(executor_type)> resume_function_overloads;
  typedef boost::mpl::vector1
  <void(executor_type)> pause_function_overloads;
  typedef boost::mpl::vector1
  <void(executor_type)> abort_function_overloads;
  struct interface_type {};
  struct time_type {};
  struct color_type {};

  static void add_border (executor_type, int, color_type);
  static void remove_border (executor_type);
  //template <typename Source, typename Descriptor, typename Color>
  static void start ( executor_type e/*, Source source, boost::optional<Descriptor> descriptor
                      , gntl::algorithm::structure::media::dimensions dimensions
                      , int, Color*/);
  static void stop (executor_type e);
  static void pause (executor_type e);
  static void resume (executor_type e);
  static void abort (executor_type e);

  static bool time_area_active_after(executor_type, time_type);
  static bool time_area_active_between(executor_type, time_type, time_type);
  static bool time_area_active_before(executor_type, time_type);
};

} } }

#endif
