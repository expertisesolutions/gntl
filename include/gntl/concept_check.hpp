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

#ifndef GNTL_CONCEPT_CHECK_HPP
#define GNTL_CONCEPT_CHECK_HPP

#ifndef GNTL_DISABLE_CONCEPTS
#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>
#include <boost/range/concepts.hpp>
#include <boost/concept_archetype.hpp>
#endif

#include <gntl/detail/push_options.hpp>

#ifndef GNTL_DISABLE_CONCEPTS
#define GNTL_CONCEPT_ASSERT(x) BOOST_CONCEPT_ASSERT (x)
#else
#define GNTL_CONCEPT_ASSERT(x)
#endif

#include <gntl/detail/pop_options.hpp>

#endif
