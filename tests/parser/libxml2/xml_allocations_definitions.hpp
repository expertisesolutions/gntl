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

std::size_t xml_total_allocated = 0;
bool xml_stable_assert = false;

void* xml_malloc(size_t s)
{
  BOOST_CHECK (!xml_stable_assert);
  void* p = std::malloc(s+sizeof(size_t));
  size_t* q = static_cast<size_t*>(p);
  *q = s;
  xml_total_allocated += s;
  return q+1;
}

void xml_free(void* p)
{
  size_t* q = static_cast<size_t*>(p);
  --q;
  assert (xml_total_allocated >= *q);
  xml_total_allocated -= *q;
  std::free(q);
}

void* xml_realloc(void* p, size_t size)
{
  BOOST_CHECK (!xml_stable_assert);
  if(p)
  {
    size_t* q = static_cast<size_t*>(p);
    size_t old_size = *--q;
    assert (xml_total_allocated >= old_size);
    xml_total_allocated -= old_size;
    void* new_p = std::realloc(q, size+sizeof(size_t));
    size_t* new_q = static_cast<size_t*>(new_p);
    *new_q = size;
    xml_total_allocated += *new_q;
    return new_q+1;
  }
  else
    return xml_malloc(size);
}

char* xml_strdup(const char* src)
{
  char* d = static_cast<char*>(xml_malloc(std::strlen(src)+1));
  std::strcpy(d, src);
  return d;
}
