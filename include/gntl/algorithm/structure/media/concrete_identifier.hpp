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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_CONCRETE_IDENTIFIER_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_CONCRETE_IDENTIFIER_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Media>
typename gntl::concept::structure::media_traits
<typename gntl::unwrap_parameter<Media>::type>::identifier_type
concrete_identifier(Media m)
{
  return concept::is_same_instance_refer(m)
    ? concept::same_instance_referred(m) : concept::identifier(m);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
