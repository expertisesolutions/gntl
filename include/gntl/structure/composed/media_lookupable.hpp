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

#ifndef GNTL_STRUCTURE_COMPOSED_MEDIA_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_MEDIA_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/ref.hpp>
#include <gntl/log/log.hpp>

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

template <typename MediaRange>
struct media_lookupable
{
  media_lookupable() {}
  media_lookupable(MediaRange medias)
    :  medias(medias)
  {
    GNTL_DEBUG_LOG("media_lookupable::media_lookupable range size: "
                   << boost::distance(medias) << std::endl)
  }

  MediaRange medias;
};

} }

namespace concept {

template <typename MediaRange>
struct lookupable_traits<gntl::structure::composed::media_lookupable<MediaRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::media_lookupable<MediaRange> media_lookupable;
  typedef std::string key_type;

  typedef gntl::reference_wrapper<typename boost::range_value<MediaRange>::type> value_type;

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };

  static result_type lookup(media_lookupable& l, key_type key)
  {
    typedef typename boost::range_iterator<MediaRange>::type iterator_type;
    typedef typename unwrap_parameter<value_type>::type media_type;

    for(iterator_type first = boost::begin(l.medias)
          , last = boost::end(l.medias)
          ;first != last;++first)
    {
      typedef concept::structure::media_traits<media_type> traits;
      if(traits::identifier(*first) == key)
        return result_type(gntl::ref(*first));
    }
    return result_type(boost::none);
  }

  static result_type not_found(media_lookupable& l)
  {
    return result_type(boost::none);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
