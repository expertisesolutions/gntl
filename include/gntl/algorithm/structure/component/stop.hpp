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

#ifndef GNTL_ALGORITHM_STRUCTURE_COMPONENT_STOP_HPP
#define GNTL_ALGORITHM_STRUCTURE_COMPONENT_STOP_HPP

#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/parameter.hpp>

#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace component {

template <typename Component, typename Descriptor, typename Document, typename...Args>
void stop(Component c, Descriptor descriptor, Document d, Args...args);

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
