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

#ifndef GNTL_ALGORITHM_REGION_HPP
#define GNTL_ALGORITHM_REGION_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/concept_check.hpp>
#include <gntl/concept/tree_iterator.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace parser { namespace region {

template <typename RegionTreeIterator, typename Predicate, typename OutputIterator>
bool region_path (RegionTreeIterator first, RegionTreeIterator last
                  , Predicate predicate
                  , OutputIterator output)
{
    GNTL_CONCEPT_ASSERT ((concept::TreeIterator<RegionTreeIterator>));

    typedef concept::tree_iterator_traits<RegionTreeIterator> tree_traits;
    typedef typename tree_traits::node_iterator node_iterator;

    node_iterator node_first = tree_traits::node(first)
      , node_last = tree_traits::node(last);

    for(;node_first != node_last;++node_first)
      if(predicate(*node_first))
      {
        *output = *node_first;
        ++output;
        return true;
      }
      else if(region_path(tree_traits::begin(node_first), tree_traits::end(node_first)
                     , predicate, output))
      {
        *output = *node_first;
        ++output;
        return true;
      }

    return false;
}


} } } }

#include <gntl/detail/pop_options.hpp>

#endif
