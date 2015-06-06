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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_SET_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_SET_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/algorithm/structure/media/set_normal_action.hpp>

#include <boost/optional.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

template <typename Media, typename Interface, typename Descriptor, typename Value, typename Document>
void set_aux(Media m, boost::optional<Interface> i, Descriptor descriptor
             , boost::optional<Value> value
             , Document d, media::dimensions full_screen, media_tag)
{
  if(i && value)
    algorithm::structure::media::set(m, *i, descriptor, *value, d, full_screen);
}

template <typename Context, typename Interface, typename Descriptor, typename Value, typename Document>
void set_aux(Context /*c*/, boost::optional<Interface> /*i*/, Descriptor /*descriptor*/
             , boost::optional<Value> /*v*/, Document /*d*/, media::dimensions /*full_screen*/
             , structure::component::context_tag)
{
  GNTL_DEBUG_LOG("set command for context" << std::endl)
}

template <typename Switch, typename Interface, typename Descriptor, typename Value, typename Document>
void set_aux(Switch /*s*/, boost::optional<Interface> /*i*/, Descriptor /*descriptor*/
             , boost::optional<Value> /*v*/, Document /*d*/
             , media::dimensions /*full_screen*/
             , structure::component::switch_tag)
{
  GNTL_DEBUG_LOG("set command for switch" << std::endl)
}

template <typename Port, typename Interface, typename Descriptor, typename Value, typename Document>
void set_aux(Port s, boost::optional<Interface> i, Descriptor /*descriptor*/
             , boost::optional<Value> /*v*/, Document /*d*/
             , media::dimensions /*full_screen*/
             , structure::component::port_tag)
{
  GNTL_DEBUG_LOG("set command for port" << std::endl)
}

template <typename Component, typename Interface, typename Descriptor, typename Value
          , typename Document>
void set(Component c, boost::optional<Interface> i, Descriptor descriptor, boost::optional<Value> v
           , Document d, media::dimensions full_screen)
{
  typedef typename boost::unwrap_reference<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  component::set_aux(c, i, descriptor, v, d, full_screen, tag_type());
}

struct set_start_functor
{
  typedef void result_type;
  template <typename Component, typename Location, typename Interface, typename Descriptor
            , typename Value, typename Document>
  result_type operator()(Component c, Location l, boost::optional<Interface> i, Descriptor descriptor
                         , boost::optional<Value> value
                         , Document d, media::dimensions full_screen) const
  {
    component::set(c, i, descriptor, value, d, full_screen);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
