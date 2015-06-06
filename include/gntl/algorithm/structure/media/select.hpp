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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_SELECT_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_SELECT_HPP

#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/algorithm/structure/document.hpp>
#include <gntl/algorithm/structure/media/calculate_focused_border.hpp>
#include <gntl/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Media, typename Presentation, typename Document
          , typename Key, typename Descriptor>
void focus_select_with_descriptor(Media m, Presentation p, Document d
                                  , Key key, Descriptor descriptor);

template <typename Media, typename Document, typename Key>
void focus_select(Media m, Document d, Key key);

struct focus_select_functor
{
  typedef void result_type;
  template <typename Media, typename Document, typename Key>
  result_type operator()(Media m, Document d, Key key) const;
};

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
