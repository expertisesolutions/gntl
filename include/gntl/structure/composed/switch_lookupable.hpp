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

#ifndef GNTL_STRUCTURE_COMPOSED_SWITCH_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_SWITCH_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/ref.hpp>

#include <boost/mpl/contains.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/variant.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename SwitchRange>
struct switch_lookupable
{
  switch_lookupable() {}
  switch_lookupable(SwitchRange switches)
    :  switches(switches) {}

  SwitchRange switches;
};

} }

namespace concept {

template <typename SwitchRange>
struct lookupable_traits<gntl::structure::composed::switch_lookupable<SwitchRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::switch_lookupable<SwitchRange> switch_lookupable;
  typedef std::string key_type;

  typedef gntl::reference_wrapper<typename boost::range_value<SwitchRange>::type> value_type;

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };

  static result_type lookup(switch_lookupable& l, key_type key)
  {
    typedef typename boost::range_iterator<SwitchRange>::type iterator_type;
    typedef typename unwrap_parameter<value_type>::type switch_type;

    for(iterator_type first = boost::begin(l.switches)
          , last = boost::end(l.switches)
          ;first != last;++first)
    {
      typedef concept::structure::switch_traits<switch_type> traits;
      if(traits::identifier(*first) == key)
        return result_type(gntl::ref(*first));
    }
    return result_type(boost::none);
  }

  static result_type not_found(switch_lookupable& l)
  {
    return result_type(boost::none);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
