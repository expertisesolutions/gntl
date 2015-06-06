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

#ifndef GNTL_STRUCTURE_COMPOSED_DESCRIPTOR_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_DESCRIPTOR_LOOKUPABLE_HPP

#include <gntl/concept_check.hpp>
#include <gntl/concept/lookupable.hpp>
#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/structure/composed/descriptor.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename DescriptorBase, typename DocumentURI>
struct descriptor_lookupable
{
  GNTL_CONCEPT_ASSERT((concept::parser::DescriptorBase<DescriptorBase>));
  typedef concept::parser::descriptor_base_traits<DescriptorBase> descriptor_base_traits;
  typedef std::map<std::string, std::pair<DocumentURI, DescriptorBase> > aliased_descriptor_bases_map;

  descriptor_lookupable() {}
  descriptor_lookupable(DescriptorBase descriptor_base
                        , DocumentURI document_uri = DocumentURI()
                        , aliased_descriptor_bases_map aliased_descriptor_bases = aliased_descriptor_bases_map())
    : descriptor_base(descriptor_base)
    , document_uri(document_uri)
    , aliased_descriptor_bases(aliased_descriptor_bases)
  {}
  
  typedef typename descriptor_base_traits::identifier_type alias_type;

  boost::optional<DescriptorBase> descriptor_base;
  DocumentURI document_uri;
  aliased_descriptor_bases_map aliased_descriptor_bases;
};

} }

namespace concept {

template <typename DescriptorBase, typename DocumentURI>
struct lookupable_traits<gntl::structure::composed::descriptor_lookupable
                         <DescriptorBase, DocumentURI> >
{
  typedef boost::mpl::true_ is_lookupable;
  GNTL_CONCEPT_ASSERT((boost::ForwardRangeConcept<DescriptorBase>));
  typedef gntl::structure::composed::descriptor_lookupable<DescriptorBase, DocumentURI>
    descriptor_lookupable;
  typedef typename descriptor_lookupable::aliased_descriptor_bases_map
    aliased_descriptor_bases_map;
  typedef typename boost::range_value<DescriptorBase>::type descriptor_type;
  typedef gntl::structure::composed::descriptor<descriptor_type, DocumentURI>
    structure_descriptor_type;
  typedef structure_descriptor_type value_type;
  typedef boost::optional<value_type> result_type;
  typedef concept::parser::descriptor_traits<descriptor_type> descriptor_traits;
  typedef typename descriptor_traits::identifier_type key_type;

  static result_type lookup(descriptor_lookupable d, key_type const& key)
  {
    GNTL_DEBUG_LOG("looking up descriptor " << key << std::endl)
    typedef typename key_type::const_iterator key_iterator;
    key_iterator sharp = std::find(boost::begin(key), boost::end(key), '#');
    if(sharp != boost::end(key))
    {
      GNTL_DEBUG_LOG("sharp char" << std::endl)
      std::string alias(boost::begin(key), sharp);
      std::string new_key(boost::next(sharp), boost::end(key));

      typedef typename aliased_descriptor_bases_map::const_iterator
        aliases_iterator;
      aliases_iterator descriptor_base = d.aliased_descriptor_bases
        .find(alias);
      if(descriptor_base != d.aliased_descriptor_bases.end())
      {
        GNTL_DEBUG_LOG("found alias" << std::endl)
        DescriptorBase base = descriptor_base->second.second;
        
        for(typename boost::range_iterator<DescriptorBase>::type
              first = boost::begin(base)
              , last = boost::end(base)
              ;first != last;++first)
        {
          GNTL_DEBUG_LOG("comparing " << descriptor_traits::identifier(*first)
                         << " with " << new_key << std::endl)
          if(descriptor_traits::identifier(*first) == new_key)
            return value_type(*first, descriptor_base->second.first);
        }
      }

      return result_type(boost::none);
    }

    if(d.descriptor_base)
    {
      for(typename boost::range_iterator<DescriptorBase>::type
            first = boost::begin(*d.descriptor_base)
            , last = boost::end(*d.descriptor_base)
            ;first != last;++first)
      {
        if(descriptor_traits::identifier(*first) == key)
          return value_type(*first, d.document_uri);
      }
    }
    return boost::none;
  }
  static result_type not_found(descriptor_lookupable const&)
  {
    return boost::none;
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
