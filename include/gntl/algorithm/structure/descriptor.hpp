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

#ifndef GNTL_ALGORITHM_STRUCTURE_DESCRIPTOR_HPP
#define GNTL_ALGORITHM_STRUCTURE_DESCRIPTOR_HPP

#include <gntl/concept_check.hpp>
#include <gntl/parameter.hpp>
#include <gntl/concept/structure/property.hpp>
#include <gntl/concept/structure/descriptor.hpp>

#include <iostream>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace descriptor {

template <typename Descriptor, typename Media>
Descriptor compose_with_properties(Descriptor descriptor, Media media)
{
  typedef typename gntl::unwrap_parameter<Descriptor>::type descriptor_type;
  typedef typename gntl::unwrap_parameter<Media>::type media_type;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  typedef concept::structure::media_traits<media_type> media_traits;

  GNTL_CONCEPT_ASSERT((concept::structure::Descriptor<descriptor_type>));
  GNTL_CONCEPT_ASSERT((concept::structure::Media<media_type>));

  if(concept::has_explicit_duration(media))
  {
    descriptor_traits::set_explicit_duration
      (descriptor, concept::explicit_duration(media));
  }
  return descriptor;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
