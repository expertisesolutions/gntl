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

#ifndef GNTL_ALGORITHM_STRUCTURE_DOCUMENT_SEARCH_HPP
#define GNTL_ALGORITHM_STRUCTURE_DOCUMENT_SEARCH_HPP

#include <gntl/concept/structure/document.hpp>
#include <gntl/concept/structure/component_location.hpp>
#include <gntl/parameter.hpp>

#include <functional>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace document {

template <typename Document, typename ComponentLocation, typename F>
typename F::result_type search(Document document, ComponentLocation location, F f)
{
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef typename unwrap_parameter<ComponentLocation>::type location_type;
  GNTL_CONCEPT_ASSERT((concept::structure::Document<document_type>));
  GNTL_CONCEPT_ASSERT((concept::structure::ComponentLocation<location_type>));
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif

