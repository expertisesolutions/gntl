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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_DESCRIPTOR_COMPOSE_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_DESCRIPTOR_COMPOSE_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept/structure/document.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Media, typename Descriptor, typename Document>
   typename boost::unwrap_reference
   <
     typename concept::structure::media_traits
     <
       typename boost::unwrap_reference<Media>::type
     >::descriptor_type
   >::type
descriptor_compose(Media m, Descriptor descriptor, Document document)
{
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef typename media_traits::descriptor_type descriptor_value_type;
  typedef typename boost::unwrap_reference<descriptor_value_type>::type descriptor_type;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
  
  if(concept::has_descriptor_identifier (m))
  {
    typename media_traits::descriptor_identifier_type
      descriptor_id = concept::descriptor_identifier (m);

    typedef typename document_traits::descriptor_lookupable descriptor_lookupable;
    descriptor_lookupable descriptors = document_traits::descriptor_lookup(document);
    typedef concept::lookupable_traits<descriptor_lookupable> lookupable_traits;
    typename lookupable_traits::result_type descriptor_lookup 
      = lookupable_traits::lookup(descriptors, descriptor_id);
    if(descriptor_lookup != lookupable_traits::not_found(descriptors))
      return descriptor_traits::compose(descriptor, *descriptor_lookup);
  }
  return descriptor;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
