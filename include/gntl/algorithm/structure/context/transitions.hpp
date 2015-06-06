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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_TRANSITIONS_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_TRANSITIONS_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/document.hpp>

#include <gntl/parameter.hpp>
#include <gntl/log/log.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

template <typename Context, typename Document>
void stop_transition (Context c, Document d)
{
  typedef typename gntl::unwrap_parameter<Context>::type context_type;
  typedef typename gntl::unwrap_parameter<Document>::type document_type;
  typedef gntl::concept::structure::context_traits<context_type> context_traits;
  typedef gntl::concept::structure::document_traits<document_type> document_traits;

  GNTL_DEBUG_LOG ("stop_transition " << context_traits::identifier(c) << std::endl);

  if(context_traits::is_presentation_sleeping(c))
  {
    GNTL_DEBUG_LOG ("is_presentation_sleeping " << context_traits::identifier(c) << std::endl);
    boost::optional<typename document_traits::component_identifier> interface_;
    algorithm::structure::document::register_event (d, c
                                                    , interface_
                                                    , gntl::transition_enum::stops
                                                    , gntl::event_enum::presentation);
  }
  else
    GNTL_DEBUG_LOG ("is_presentation_occurring " << context_traits::identifier(c) << std::endl);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
