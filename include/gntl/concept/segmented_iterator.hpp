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

#ifndef GNTL_CONCEPT_SEGMENTED_ITERATOR_HPP
#define GNTL_CONCEPT_SEGMENTED_ITERATOR_HPP

#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept {

// See http://lafstern.org/matt/segmented.pdf

template <typename Iterator>
struct segmented_iterator_traits
{
  typedef boost::mpl::false_ is_segmented_iterator;
};

/*
  template <typename T>
  struct segmented_iterator_traits<seg_array_iter<T> >
  {
    typedef boost::true_type is_segmented_iterator;
    
    typedef seg_array_iter<T> iterator;
    typedef std::vector<std::vector<T> >::iterator segment_iterator;
    typedef std::vector<T>::iterator local_iterator;
    
    static segment_iterator segment(iterator);
    static local_iterator   local(iterator);
    
    static iterator compose(segment_iterator, local_iterator);
    
    static local_iterator begin(segment_iterator);
    static local_iterator end(segment_iterator);
  };
 */

} }


#include <gntl/detail/pop_options.hpp>

#endif
