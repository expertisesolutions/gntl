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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_EVALUATE_LINKS_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_EVALUATE_LINKS_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/algorithm/structure/switch/evaluate_links.hpp>
#include <gntl/algorithm/structure/context/evaluate_links.ipp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

template <typename Context, typename ContextLocation, typename Document, typename Event, typename Dimensions
          , typename...Args>
void evaluate_links(Context context, ContextLocation context_location, Document document, Event event, Dimensions screen_dimensions, Args...);

template <typename Context, typename ContextLocation, typename Document, typename Key, typename Dimensions
          , typename...Args>
void evaluate_select_links(Context context, ContextLocation context_location, Document document, Key key, Dimensions screen_dimensions, Args...);

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
