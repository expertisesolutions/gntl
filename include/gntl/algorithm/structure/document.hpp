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

#ifndef GNTL_ALGORITHM_STRUCTURE_DOCUMENT_HPP
#define GNTL_ALGORITHM_STRUCTURE_DOCUMENT_HPP

#include <gntl/log/log.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept/parser/region/region.hpp>
#include <gntl/concept/parser/region/region_base.hpp>
#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/concept/parser/import/import_base.hpp>
#include <gntl/algorithm/structure/wrap_if.hpp>
#include <gntl/ref.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/parameter.hpp>
#include <gntl/range.hpp>

#include <boost/optional.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace document {

template <typename Document, typename Media, typename Descriptor>
void set_focus(Document document, Media media, Descriptor descriptor)
{
  typedef typename boost::unwrap_reference<Media>::type media_type;
  typedef typename boost::unwrap_reference<Descriptor>::type descriptor_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;

  typedef concept::structure::media_traits<media_type> media_traits;
  typedef concept::structure::document_traits<document_type> document_traits;
  typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;

  GNTL_DEBUG_LOG("setting focus for media " << concept::identifier(media)
                 << " on document " << std::endl)
  document_traits::start_set_property(document, "service.currentFocus"
                                      , descriptor_traits::focus_index(descriptor));
  document_traits::set_focused_media(document, concept::identifier(media));
  if(document_traits::has_global_properties_media(document))
  {
    typename document_traits::component_identifier interface_("service.currentFocus");
    document_traits::register_event(document
                                    , document_traits::global_properties_media(document)
                                    , interface_, gntl::transition_enum::starts
                                    , gntl::event_enum::attribution);
  }
  else
  {
    document_traits::commit_set_property(document, "service.currentFocus");
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
