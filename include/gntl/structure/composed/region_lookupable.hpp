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

#ifndef GNTL_STRUCTURE_COMPOSED_REGION_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_REGION_LOOKUPABLE_HPP

#include <gntl/algorithm/parser/region.hpp>
#include <gntl/algorithm/structure/document.hpp>
#include <gntl/concept/parser/region/region_base.hpp>
#include <gntl/concept/lookupable.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename RegionBaseRange/*, typename DocumentURI*/>
struct region_lookupable
{
  typedef std::map<std::string, RegionBaseRange> aliased_region_bases_map;
  typedef typename boost::range_value<RegionBaseRange>::type region_base;
  typedef concept::parser::region_base_traits<region_base> region_base_traits;

  region_lookupable(RegionBaseRange region_bases
                    , aliased_region_bases_map aliased_region_bases)
    : region_bases(region_bases)
    , aliased_region_bases(aliased_region_bases)
  {}

  typedef typename region_base_traits::identifier_type alias_type;

  RegionBaseRange region_bases;
  aliased_region_bases_map aliased_region_bases;
};

} }

namespace concept {

template <typename RegionBaseRange>
struct lookupable_traits<gntl::structure::composed::region_lookupable<RegionBaseRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  GNTL_CONCEPT_ASSERT((boost::ForwardRangeConcept<RegionBaseRange>));
  typedef gntl::structure::composed::region_lookupable<RegionBaseRange> region_lookupable;
  typedef typename region_lookupable::aliased_region_bases_map
    aliased_region_bases_map;
  typedef typename boost::range_value<RegionBaseRange>::type region_base;
  typedef concept::parser::region_base_traits<region_base> region_base_traits;
  typedef typename region_base_traits::region_range region_range;
  typedef typename boost::range_value<region_range>::type region_type;
  typedef std::vector<region_type> value_type;
  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };
  typedef typename region_base_traits::identifier_type key_type;
  
  struct identifier_predicate
  {
    typedef bool result_type;
    identifier_predicate (std::string identifier)
        : identifier (identifier) {}

    template <typename Region>
    result_type operator()(Region const& region) const
    {
      typedef typename unwrap_parameter<Region>::type region_type;
      typedef concept::parser::region_traits<region_type> region_traits;
      return region_traits::identifier (region) == identifier;
    }

    std::string identifier;
  };
  
  static result_type lookup(region_lookupable l, key_type key)
  {
    GNTL_DEBUG_LOG("looking up region " << key << std::endl)
    std::string new_key = key;
    boost::optional<RegionBaseRange> region_base_range;

    typedef typename key_type::const_iterator key_iterator;
    key_iterator sharp = std::find(boost::begin(key), boost::end(key), '#');
    if(sharp != boost::end(key))
    {
      GNTL_DEBUG_LOG("sharp char" << std::endl)
      std::string alias(boost::begin(key), sharp);
      GNTL_DEBUG_LOG("searching alias " << alias << ' '
                     << l.aliased_region_bases.size() << std::endl)
      new_key.clear();
      new_key.insert(new_key.end(), boost::next(sharp), boost::end(key));
      typedef typename aliased_region_bases_map::const_iterator
        aliases_iterator;
      aliases_iterator iterator = l.aliased_region_bases
        .find(alias);
      if(iterator != l.aliased_region_bases.end())
      {
        GNTL_DEBUG_LOG("found alias" << std::endl)
        region_base_range = iterator->second;
      }
      else
        return result_type(boost::none);
    }
    else
    {
      region_base_range = l.region_bases;
    }

    GNTL_DEBUG_LOG("searching region " << new_key << std::endl)

    for(typename boost::range_iterator<RegionBaseRange>::type
          base_first = boost::begin(*region_base_range)
          , base_last = boost::end(*region_base_range)
          ;base_first != base_last;++base_first)
    {
      value_type region_path;
      algorithm::parser::region::region_path (boost::begin (*base_first), boost::end (*base_first)
                                              , identifier_predicate(new_key)
                                              , std::back_inserter (region_path));
      if(!region_path.empty())
      {
        GNTL_DEBUG_LOG("Found region!" << std::endl)
        for(typename std::vector<region_type>::reverse_iterator
              Iter = region_path.rbegin()
              , EndIter = region_path.rend()
              ;Iter != EndIter
              ;++Iter)
        {
          typedef gntl::concept::parser::region_traits
            <region_type> region_traits;
          GNTL_DEBUG_LOG("/" << region_traits::identifier(*Iter))
        }
        GNTL_DEBUG_LOG(std::endl)
        std::reverse(region_path.begin(), region_path.end());
        return result_type(region_path);
      }
    }
    return result_type(boost::none);
  }
  static result_type not_found(region_lookupable)
  {
    return result_type(boost::none);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
