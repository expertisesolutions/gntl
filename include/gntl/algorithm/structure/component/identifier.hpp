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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_IDENTIFIER_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_IDENTIFIER_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/switch.hpp>
#include <gntl/concept/parser/port/port.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

namespace result_of {

template <typename Component>
struct identifier 
{
  typedef typename unwrap_parameter<Component>::type component_type;
  typedef concept::structure::media_traits<component_type> media_traits;
  typedef concept::structure::context_traits<component_type> context_traits;
  typedef concept::structure::switch_traits<component_type> switch_traits;
  typedef concept::parser::port_traits<component_type> port_traits;

  typedef typename media_traits::is_media is_media;
  typedef typename context_traits::is_context is_context;
  typedef typename switch_traits::is_switch is_switch;
  typedef typename port_traits::is_port is_port;

  template <typename Traits>
  struct identifier_meta
  {
    typedef typename Traits::identifier_type type;
  };

  typedef typename boost::mpl::eval_if
  <is_media
   , identifier_meta<media_traits>
   , boost::mpl::eval_if
     <is_context
      , identifier_meta<context_traits>
      , boost::mpl::eval_if_c
      <switch_traits::is_switch::value
       , identifier_meta<switch_traits>
       , boost::mpl::eval_if
       <is_port
        , identifier_meta<port_traits>
        , boost::mpl::identity<void>
        >
       >
      >
   >::type type;
};

}

namespace component_detail {

template <typename Media>
typename concept::structure::media_traits
<typename unwrap_parameter<Media>::type>::identifier_type identifier(Media m)
{
  return concept::identifier(m);
}

template <typename Context>
typename concept::structure::context_traits
<typename unwrap_parameter<Context>::type>::identifier_type identifier(Context c)
{
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename concept::structure::context_traits<context_type> context_traits;
  return context_traits::identifier(c);
}

template <typename Switch>
typename concept::structure::switch_traits
<typename unwrap_parameter<Switch>::type>::identifier_type identifier(Switch s)
{
  typedef typename unwrap_parameter<Switch>::type switch_type;
  typedef concept::structure::switch_traits<switch_type> switch_traits;
  return switch_traits::identifier(s);
}

template <typename Port>
typename concept::parser::port_traits
<typename unwrap_parameter<Port>::type>::identifier_type identifier(Port p)
{
  typedef typename unwrap_parameter<Port>::type port_type;
  typedef concept::parser::port_traits<port_type> port_traits;
  return port_traits::identifier(p);
}

}

template <typename Component>
typename result_of::identifier<Component>::type identifier(Component component)
{
  return component_detail::identifier(component);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
