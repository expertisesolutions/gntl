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

#ifndef GNTL_STRUCTURE_COMPOSED_DOCUMENT_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_DOCUMENT_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Document, typename DocumentURI>
struct document_lookupable
{
  document_lookupable()
  {}

  void add_document(DocumentURI uri, Document& d)
  {
    documents.insert(std::make_pair(uri, &d));
  }
  void remove_document(Document const& d)
  {
    for(typename std::map<DocumentURI, Document*>::iterator
          first = documents.begin(), last = documents.end()
          ;first != last; ++first)
    {
      if(first->second == &d)
      {
        documents.erase(first);
        break;
      }
    }
  }

  std::map<DocumentURI, Document*> documents;
};

} }

namespace concept {

template <typename Document, typename DocumentURI>
struct lookupable_traits<gntl::structure::composed::document_lookupable
                         <Document, DocumentURI> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::document_lookupable<Document, DocumentURI> lookupable_type;
  typedef DocumentURI key_type;
  typedef typename std::map<DocumentURI, Document*>::iterator iterator_type;
  struct result_type
  {
    iterator_type it;
    result_type(iterator_type it) : it(it) {}
    Document& operator*() const { return *it->second; }
    bool operator==(result_type const& other) { return it == other.it; }
    bool operator!=(result_type const& other) { return !(*this == other); }
  };

  typedef Document value_type;

  static result_type lookup(lookupable_type& l, key_type const& key)
  {
    iterator_type iterator = l.documents.find(key);
    if(iterator != l.documents.end())
    {
      return result_type(iterator);
    }
    else
      return result_type(l.documents.end());
  }
  static result_type not_found(lookupable_type& l)
  {
    return result_type(l.documents.end());
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
