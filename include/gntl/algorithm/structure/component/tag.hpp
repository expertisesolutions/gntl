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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_TAGS_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_TAGS_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/switch.hpp>
#include <gntl/concept/parser/port/port.hpp>

#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

struct context_tag {};
struct media_tag {};
struct port_tag {};
struct switch_tag {};

template <typename T, typename Enable = void>
struct tag;

template <typename T>
struct tag<T, typename boost::enable_if<typename concept::structure::context_traits<T>::is_context, void>::type>
{
  typedef context_tag type;
};

template <typename T>
struct tag<T, typename boost::enable_if<typename concept::structure::media_traits<T>::is_media, void>::type>
{
  typedef media_tag type;
};

template <typename T>
struct tag<T, typename boost::enable_if<typename concept::parser::port_traits<T>::is_port, void>::type>
{
  typedef port_tag type;
};

template <typename T>
struct tag<T, typename boost::enable_if<typename concept::structure::switch_traits<T>::is_switch, void>::type>
{
  typedef switch_tag type;
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
