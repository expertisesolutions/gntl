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

#ifndef GNTL_STRUCTURE_COMPOSED_CONTEXT_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_CONTEXT_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/ref.hpp>

#include <boost/mpl/contains.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/variant.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ContextRange>
struct context_lookupable
{
  context_lookupable(ContextRange contexts)
    : contexts(contexts) {}

  ContextRange contexts;
};

} }

namespace concept {

template <typename ContextRange>
struct lookupable_traits<gntl::structure::composed::context_lookupable<ContextRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::context_lookupable<ContextRange> context_lookupable;
  typedef std::string key_type;

  typedef gntl::reference_wrapper<typename boost::range_value<ContextRange>::type> value_type;

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };

  static result_type lookup(context_lookupable l, key_type key)
  {
    typedef typename boost::range_iterator<ContextRange>::type iterator_type;
    typedef typename unwrap_parameter<value_type>::type context_type;

    for(iterator_type first = boost::begin(l.contexts)
          , last = boost::end(l.contexts)
          ;first != last;++first)
    {
      typedef concept::structure::context_traits<context_type> traits;
      if(traits::identifier(*first) == key)
        return result_type(gntl::ref(*first));
    }
    return result_type(boost::none);
  }

  static result_type not_found(context_lookupable l)
  {
    return result_type(boost::none);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
