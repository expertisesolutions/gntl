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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_ACTION_TRAITS_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_ACTION_TRAITS_HPP

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

struct natural_end_action_traits
{
    template <typename Media, typename Presentation, typename Document, typename...Args>
    static void natural_end(Media m, Presentation presentation, Document document, Args&&...args);
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
