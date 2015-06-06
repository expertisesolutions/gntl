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

#ifndef GNTL_ARCHETYPE_SEGMENTED_ITERATOR_HPP
#define GNTL_ARCHETYPE_SEGMENTED_ITERATOR_HPP

#include <boost/concept_archetype.hpp>
#include <gntl/concept/segmentediterator.hpp>

namespace gntl { namespace archetype {

template <typename Value, typename SegmentIterator, typename LocalIterator>
struct segmented_iterator : boost::input_iterator_archetype<Value>
{
};

}

namespace concept {

template <typename Value, typename SegmentIterator, typename LocalIterator>
struct segmented_iterator_traits<archetype::segmented_iterator<Value, SegmentIterator, LocalIterator> >
{
  typedef boost::true_type is_segmented_iterator;
    
  typedef archetype::segmented_iterator<Value, SegmentIterator, LocalIterator> iterator;
  typedef SegmentIterator segment_iterator;
  typedef LocalIterator local_iterator;
    
  static segment_iterator segment(iterator);
  static local_iterator   local(iterator);
    
  static iterator compose(segment_iterator, local_iterator);
    
  static local_iterator begin(segment_iterator);
  static local_iterator end(segment_iterator);
};

}

} }

#endif
