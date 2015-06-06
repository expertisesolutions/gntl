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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_REGISTER_INTERFACE_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_REGISTER_INTERFACE_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/parser/port/port.hpp>
#include <gntl/algorithm/structure/component/identifier.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

template <typename Context, typename Component, typename Document>
void register_interface_for_component (Context context, Component c, Document d
                                       , gntl::transition_type transition
                                       , gntl::event_type event)
{
  GNTL_DEBUG_LOG("register_interface_for_component" << std::endl)
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::context_traits<context_type> context_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  
  typedef typename structure::component::result_of
    ::identifier<Component>::type identifier_type;

  identifier_type identifier = structure::component::identifier(c);
  
  typedef typename context_traits::port_range port_value_range;
  typedef typename unwrap_parameter<port_value_range>::type port_range;
  port_value_range ports = context_traits::port_all(context);
  typedef typename boost::range_iterator<port_range>::type port_iterator;
  typedef typename boost::range_value<port_range>::type port_type;
  for(port_iterator first = boost::begin(ports)
        , last = boost::end(ports); first != last; ++first)
  {
    typedef concept::parser::port_traits<port_type> port_traits;

    if(port_traits::component(*first) == identifier)
    {
      GNTL_DEBUG_LOG("Found port " << port_traits::identifier(*first) << std::endl)
      typename document_traits::component_identifier interface_
        = port_traits::identifier(*first);
      structure::document::register_event
        (d, context, interface_, transition, event);
      break;
    }
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
