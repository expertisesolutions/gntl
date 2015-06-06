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

#ifndef GNTL_RANGE_HPP
#define GNTL_RANGE_HPP

#include <boost/range.hpp>
#include <boost/version.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#if BOOST_VERSION >= 104300
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/range/numeric.hpp>
#endif

#include <algorithm>
#include <numeric>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace range {
#if BOOST_VERSION >= 104300
using boost::range::find_if;
using boost::range::equal;
using boost::accumulate;
using boost::distance;
using boost::empty;
using boost::range::for_each;
#else
template <typename Range, typename Predicate>
typename boost::range_iterator<Range>::type
find_if(Range range, Predicate p)
{
  return std::find_if(boost::begin(range), boost::end(range), p);
}
template <typename Range1, typename Range2>
bool equal(Range1 range1, Range2 range2)
{
  return boost::distance(range1) == boost::distance(range2)
    && std::equal(boost::begin(range1), boost::end(range1)
                  , boost::begin(range2));
}
template <typename Range, typename BinaryFunction, typename Value>
Value accumulate(Range range, BinaryFunction f, Value v)
{
  return std::accumulate(boost::begin(range), boost::end(range), f, v);
}
template <typename Range, typename Function>
void for_each(Range range, Function f)
{
  std::for_each(boost::begin(range), boost::end(range), f);
}
#endif
} }

#include <gntl/detail/pop_options.hpp>

#endif
