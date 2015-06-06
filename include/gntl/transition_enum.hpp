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

#ifndef GNTL_TRANSITION_ENUM_HPP
#define GNTL_TRANSITION_ENUM_HPP

#include <gntl/detail/push_options.hpp>

namespace gntl {

namespace transition_enum {
enum transition_type
{
    starts
    , stops
    , aborts
    , pauses
    , resumes
};
}

using transition_enum::transition_type;

}

#include <gntl/detail/pop_options.hpp>

#endif
