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

#ifndef GNCL_TESTS_PARSER_LIBXML2_GLOBAL_ALLOCATIONS_HPP
#define GNCL_TESTS_PARSER_LIBXML2_GLOBAL_ALLOCATIONS_HPP

void global_stabilized_allocations ();
void global_destabilized_allocations ();

#define GNTL_GLOBAL_ALLOC_GUARD_EXPR ? true : (::global_destabilized_allocations (),false)
#define GNTL_GLOBAL_ALLOC_CHECK(x) BOOST_CHECK ((x) GNTL_GLOBAL_ALLOC_GUARD_EXPR)
#define GNTL_GLOBAL_ALLOC_REQUIRE(x) BOOST_REQUIRE ((x) GNTL_GLOBAL_ALLOC_GUARD_EXPR)
#define GNTL_GLOBAL_ALLOC_GUARD(x,y,op)                                 \
    if(!((x) op (y))) { ::global_destabilized_allocations (); }
#define GNTL_GLOBAL_ALLOC_CHECK_EQUAL(x,y) {GNTL_GLOBAL_ALLOC_GUARD (x,y,==) BOOST_CHECK_EQUAL (x,y);}while(false)
#define GNTL_GLOBAL_ALLOC_REQUIRE_EQUAL(x,y) {GNTL_GLOBAL_ALLOC_GUARD (x,y,==) BOOST_REQUIRE_EQUAL (x,y);}while(false)
#define GNTL_GLOBAL_ALLOC_FAIL(x) do {::global_destabilized_allocations (); BOOST_FAIL (x);}while(false)

#endif

