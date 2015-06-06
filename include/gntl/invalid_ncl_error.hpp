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

#ifndef GNTL_INVALID_NCL_ERROR_HPP
#define GNTL_INVALID_NCL_ERROR_HPP

#include <gntl/unwind_error.hpp>
#include <gntl/detail/push_options.hpp>

namespace gntl {

struct invalid_ncl_error : gntl_error
{
  const char* what() const throw() { return "invalid_ncl_error"; }
};

}

#include <gntl/detail/pop_options.hpp>

#endif