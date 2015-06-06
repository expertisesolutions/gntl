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

#ifndef GNTL_ALGORITHM_STRUCTURE_ITERATION_HPP
#define GNTL_ALGORITHM_STRUCTURE_ITERATION_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/media.hpp>

#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

template <typename F>
struct any_predicate
{
  any_predicate(F f) : f(f) {}

  typedef bool result_type;
  template <typename C>
  result_type operator()(C c) const
  {
    return any(c, f);
  }

  F f;
};

template <typename Context, typename F>
bool any(Context c, F f
         , typename boost::enable_if
         <typename concept::structure::context_traits
          <Context>::is_context>::type* = 0)
{
  if(f(c))
    return true;
  typedef concept::structure::context_traits
    <Context> context_traits;
  typedef typename context_traits::media_range_type 
    media_range_type;
  media_range_type
    media_range = context_traits::media_range(c);
  typename boost::range_iterator<media_range_type>
    ::type media_iterator = boost::find_if
    (media_range, any_predicate<F>(f));
  return media_iterator != boost::end(media_range);
}

template <typename Media, typename F>
bool any(Media m, F f
         , typename boost::enable_if
         <typename concept::structure::media_traits
          <Media>::is_media>::type* = 0)
{
  return f(m);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
