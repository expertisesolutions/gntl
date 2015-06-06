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

#include <new>
#include <stdlib.h>
#include <cstdlib>

namespace {

std::new_handler get_new_handler()
{
    std::new_handler p = std::set_new_handler(0);
    std::set_new_handler(p);
    return p;
}

void * allocate(size_t n)
{
    void * pm;

    for(;;)
    {
        pm = malloc(n);

        if(pm != 0) break;

        if(std::new_handler pnh = get_new_handler())
        {
            pnh();
        }
        else
        {
            return 0;
        }
    }

    return pm;
}

}

bool global_stable_allocations = false;
bool global_fail_allocations = false;
namespace {
bool test_allocations = true;
}

void* operator new(size_t n)
#ifndef _MSC_VER
  throw(std::bad_alloc)
#endif
{
    if(test_allocations)
    {
        test_allocations = !global_fail_allocations;
        assert (!global_stable_allocations); // can't use boost.test macros in here
        if(global_fail_allocations)
            throw std::bad_alloc ();
    }
    void * p = allocate(n);
    if(p == 0) throw std::bad_alloc();
    return p;
}

void* operator new[](size_t n)
#ifndef _MSC_VER
  throw(std::bad_alloc)
#endif
{
    if(test_allocations)
    {
        test_allocations = !global_fail_allocations;
        assert (!global_stable_allocations); // can't use boost.test macros in here
        if(global_fail_allocations)
            throw std::bad_alloc ();
    }
    void * p = allocate(n);
    if(p == 0) throw std::bad_alloc();
    return p;
}

void operator delete (void* p) throw()
{
    if(p == 0) return;
    free (p);
}

void operator delete[] (void* p) throw()
{
    if(p == 0) return;
    free (p);
}

void global_stabilized_allocations ()
{
    global_stable_allocations = true;
}

void global_destabilized_allocations ()
{
    global_stable_allocations = false;
}

void global_inject_failure_allocations ()
{
    global_stable_allocations = true;
}

void global_remove_failure_allocations ()
{
    global_stable_allocations = false;
}
