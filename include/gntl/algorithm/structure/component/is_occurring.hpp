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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_IS_OCCURRING_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_IS_OCCURRING_HPP

#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/switch.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

namespace component_detail {

template <typename Media>
bool is_occurring_aux (Media m, media_tag)
{
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef concept::structure::media_traits<media_type> media_traits;

  typedef typename media_traits::presentation_range presentation_value_range;
  presentation_value_range presentations = concept::presentation_all(m);
  typedef typename unwrap_parameter<presentation_value_range>::type presentation_range;
  typedef typename boost::range_iterator<presentation_range>::type presentation_iterator;
  for(presentation_iterator first = boost::begin(presentations)
        , last = boost::end(presentations); first != last; ++first)
  {
    typedef typename boost::range_value<presentation_range>::type presentation_value_type;
    typedef typename unwrap_parameter<presentation_value_type>::type presentation_type;
    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
    if(presentation_traits::is_occurring(*first))
      return true;
  }

  return false;
}

template <typename Context>
bool is_occurring_aux (Context c, context_tag)
{
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef concept::structure::context_traits<context_type> context_traits;

  return context_traits::is_presentation_occurring(c);
}

template <typename Switch>
bool is_occurring_aux (Switch s, switch_tag)
{
  return false;
}

}

template <typename Component>
bool is_occurring (Component component)
{
  typedef typename unwrap_parameter<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  return component_detail::is_occurring_aux(component, tag_type());
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
