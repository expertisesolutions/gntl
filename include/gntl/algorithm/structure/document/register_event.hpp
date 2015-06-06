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

#ifndef GNTL_ALGORITHM_STRUCTURE_DOCUMENT_REGISTER_EVENT_HPP
#define GNTL_ALGORITHM_STRUCTURE_DOCUMENT_REGISTER_EVENT_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/algorithm/structure/component/identifier.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace document {

template <typename Document, typename Component, typename OptionalInterface>
void register_event(Document document, Component c
                    , OptionalInterface interface_, gntl::transition_type t
                    , gntl::event_type e)
{
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::document_traits<document_type> document_traits;
  GNTL_CONCEPT_ASSERT((concept::structure::Document<document_type>));
  document_traits::register_event(document, component::identifier(c), interface_, t, e);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
