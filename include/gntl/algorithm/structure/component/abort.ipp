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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_ABORT_IPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_ABORT_IPP

#include <gntl/algorithm/structure/media/abort_normal_action.hpp>
#include <gntl/algorithm/structure/context/abort_normal_action.hpp>
#include <gntl/algorithm/structure/port/abort_normal_action.hpp>
#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/parser/port/port.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/switch.hpp>

#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

template <typename Media, typename Descriptor, typename Document>
void abort_aux(Media c, Descriptor descriptor
               , Document d, media_tag)
{
  typedef typename boost::unwrap_reference<Media>::type component_type;
  typedef concept::structure::media_traits<component_type> media_traits;
  typedef typename boost::unwrap_reference<Document>::type document_type;

  typedef typename media_traits::descriptor_type descriptor_type;
  gntl::algorithm::structure::media::abort (c, descriptor, d);
}

template <typename Context, typename Descriptor, typename Document>
void abort_aux(Context c, Descriptor descriptor
               , Document d, context_tag)
{
  gntl::algorithm::structure::context::abort (c, descriptor, d);
}

template <typename Switch, typename Descriptor, typename Document>
void abort_aux(Switch s, Descriptor descriptor, Document d, switch_tag)
{
}

template <typename Port, typename Descriptor, typename Document>
void abort_aux(Port p, Descriptor descriptor, Document d, port_tag)
{
  //algorithm::structure::port::abort(p, d);
}

template <typename Component, typename Descriptor, typename Document>
void abort(Component c, Descriptor descriptor, Document d)
{
  typedef typename boost::unwrap_reference<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  component::abort_aux(c, descriptor, d, tag_type());
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
