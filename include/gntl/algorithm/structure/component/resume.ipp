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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_RESUME_IPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_RESUME_IPP

#include <gntl/algorithm/structure/media/resume_normal_action.hpp>
#include <gntl/algorithm/structure/context/resume_normal_action.hpp>
//#include <gntl/algorithm/structure/switch/resume_normal_action.hpp>
#include <gntl/algorithm/structure/port/resume_normal_action.hpp>
#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

template <typename Media, typename Descriptor, typename Document
          , typename...Args>
void resume_aux(Media c, Descriptor descriptor, Document d, media_tag, Args...args)
{
  typedef typename boost::unwrap_reference<Media>::type component_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;

  GNTL_DEBUG_LOG("resume media " << concept::identifier(c) << std::endl)
  gntl::algorithm::structure::media::resume (c, descriptor, d, args...);
}

template <typename Context, typename Descriptor, typename Document
          , typename...Args>
void resume_aux(Context c, Descriptor descriptor, Document d, context_tag, Args...args)
{
  typedef typename boost::unwrap_reference<Context>::type component_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;

  gntl::algorithm::structure::context::resume (c, descriptor, d, args...);
}

template <typename Switch, typename Descriptor, typename Document
          , typename...Args>
void resume_aux(Switch s, Descriptor descriptor, Document d, switch_tag, Args...args)
{
  typedef typename boost::unwrap_reference<Switch>::type component_type;
  typedef typename boost::unwrap_reference<Document>::type document_type;
}

template <typename Port, typename Descriptor, typename Document
          , typename...Args>
void resume_aux(Port p, Descriptor descriptor, Document d, port_tag, Args...args)
{
  //algorithm::structure::port::resume(p, d);
}

template <typename Component, typename Descriptor, typename Document
          , typename...Args>
void resume(Component c, Descriptor descriptor, Document d, Args...args)
{
  typedef typename boost::unwrap_reference<Component>::type component_type;
  typedef typename structure::component::tag<component_type>::type tag_type;
  component::resume_aux(c, descriptor, d, tag_type(), args...);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
