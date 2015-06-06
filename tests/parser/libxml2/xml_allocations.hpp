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

#ifndef GNCL_TESTS_LIBXML2_XML_ALLOCATIONS_HPP
#define GNCL_TESTS_LIBXML2_XML_ALLOCATIONS_HPP

extern std::size_t xml_total_allocated;
extern bool xml_stable_assert;

inline void xml_stabilized_allocations ()
{
    std::cout << "stabilized XML allocations at " << xml_total_allocated << std::endl;
    xml_stable_assert = true;
}

void* xml_malloc(size_t s);
void xml_free(void* p);
void* xml_realloc(void* p, size_t size);
char* xml_strdup(const char* src);

#endif
