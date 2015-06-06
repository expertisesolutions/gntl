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

#ifndef GNTL_STRUCTURE_COMPOSED_CAUSAL_CONNECTOR_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_CAUSAL_CONNECTOR_LOOKUPABLE_HPP

#include <gntl/parameter.hpp>
#include <gntl/concept/lookupable.hpp>

#include <map>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ConnectorBase>
struct causal_connector_lookupable
{
  typedef std::map<std::string, ConnectorBase> aliased_connector_bases_map;

  causal_connector_lookupable() {}
  causal_connector_lookupable(ConnectorBase connector_base
                              , aliased_connector_bases_map aliased_connector_bases
                                = aliased_connector_bases_map())
    : connector_base(connector_base)
    , aliased_connector_bases(aliased_connector_bases)
  {}

  boost::optional<ConnectorBase> connector_base;
  aliased_connector_bases_map aliased_connector_bases;
};

} }

namespace concept {

template <typename ConnectorBase>
struct lookupable_traits<gntl::structure::composed::causal_connector_lookupable
                         <ConnectorBase> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::causal_connector_lookupable<ConnectorBase> lookupable_type;
  typedef typename unwrap_parameter<ConnectorBase>::type connector_base_type;
  typedef concept::parser::connector_base_traits<connector_base_type> connector_base_traits;
  typedef typename connector_base_traits::causal_connector_range causal_connector_range_value_type;
  typedef typename unwrap_parameter<causal_connector_range_value_type>::type causal_connector_range;
  typedef typename boost::range_value<causal_connector_range>::type value_type;
  typedef typename unwrap_parameter<value_type>::type causal_connector_type;
  typedef concept::parser::causal_connector_traits<causal_connector_type> causal_connector_traits;
  typedef typename causal_connector_traits::identifier_type key_type;
  typedef typename lookupable_type::aliased_connector_bases_map aliased_connector_bases_map;

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };

  static result_type lookup(lookupable_type const& l, key_type key)
  {
    typedef typename boost::range_iterator<causal_connector_range>::type causal_connector_iterator;
    typedef typename key_type::const_iterator key_iterator;
    key_iterator sharp = std::find(boost::begin(key), boost::end(key), '#');
    if(sharp != boost::end(key))
    {
      GNTL_DEBUG_LOG("sharp char" << std::endl)
      std::string alias(boost::begin(key), sharp);
      std::string new_key(boost::next(sharp), boost::end(key));

      typedef typename aliased_connector_bases_map::const_iterator aliases_iterator;
      aliases_iterator connector_base = l.aliased_connector_bases.find(alias);
      if(connector_base != l.aliased_connector_bases.end())
      {
        GNTL_DEBUG_LOG("found alias" << std::endl)
        ConnectorBase base = connector_base->second;
        causal_connector_range_value_type causal_connectors
          = connector_base_traits::causal_connector_all(base);
        
        for(causal_connector_iterator first = boost::begin(causal_connectors)
              , last = boost::end(causal_connectors);first != last;++first)
        {
          GNTL_DEBUG_LOG("comparing " << causal_connector_traits::identifier(*first)
                         << " with " << new_key << std::endl)
          if(causal_connector_traits::identifier(*first) == new_key)
            return result_type(*first);
        }
      }

      return result_type(boost::none);
    }

    if(l.connector_base)
    {
      causal_connector_range_value_type causal_connectors
        = connector_base_traits::causal_connector_all(*l.connector_base);
      for(causal_connector_iterator first = boost::begin(causal_connectors)
            , last = boost::end(causal_connectors);first != last;++first)
      {
        if(causal_connector_traits::identifier(*first) == key)
          return result_type(*first);
      }
    }
    GNTL_DEBUG_LOG("not found causal_connector " << key << std::endl)
    return result_type(boost::none);
  }
  static result_type not_found(lookupable_type const&)
  {
    return result_type(boost::none);
  }

};

} }


#include <gntl/detail/pop_options.hpp>

#endif
