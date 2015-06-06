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

#ifndef GNTL_CONCEPT_SEGMENTEDITERATOR_HPP
#define GNTL_CONCEPT_SEGMENTEDITERATOR_HPP

#include <gntl/concept/segmented_iterator.hpp>
#include <gntl/concept_check.hpp>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept {
#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct SegmentedIterator
{
    typedef segmented_iterator_traits<X> traits_type;
    typedef typename traits_type::is_segmented_iterator is_segmented_iterator;
    typedef typename traits_type::iterator iterator;
    typedef typename traits_type::segment_iterator segment_iterator;
    typedef typename traits_type::local_iterator local_iterator;

    BOOST_STATIC_ASSERT ((is_segmented_iterator::type::value));
    BOOST_CONCEPT_ASSERT ((boost::InputIterator<iterator>));
    BOOST_CONCEPT_ASSERT ((boost::InputIterator<segment_iterator>));
    BOOST_CONCEPT_ASSERT ((boost::InputIterator<local_iterator>));

    BOOST_CONCEPT_USAGE (SegmentedIterator)
    {
        is_same<segment_iterator>(traits_type::segment (i));
        is_same<local_iterator>(traits_type::local (i));
        is_same<iterator>(traits_type::compose (seg_i, local_i));
        is_same<local_iterator>(traits_type::begin (seg_i));
        is_same<local_iterator>(traits_type::end (seg_i));
    }

    template <typename T0, typename T1>
    void is_same (T1 const&)
    {
      BOOST_STATIC_ASSERT((boost::is_same<T0,T1>::type::value));
    }
    
    X i;
    segment_iterator seg_i;
    local_iterator   local_i;
};
#endif
} }


#include <gntl/detail/pop_options.hpp>

#endif
