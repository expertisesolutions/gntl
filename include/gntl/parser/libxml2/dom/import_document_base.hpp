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

#ifndef GNTL_PARSER_LIBXML2_DOM_IMPORT_DOCUMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_IMPORT_DOCUMENT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/import_ncl.hpp>
#include <gntl/parser/libxml2/dom/xml_import_ncl_predicate.hpp>
#include <gntl/concept/parser/import/import_document_base.hpp>
#include <gntl/range.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct import_document_base
{
  import_document_base(xml_node node)
    : node(node) {}

  typedef import_ncl import_ncl_type;
  typedef xml_element_node_iterator<import_ncl, xml_import_ncl_predicate> import_ncl_iterator;

  xml_node node;
};

inline bool operator==(import_document_base const& lhs, import_document_base const& rhs)
{
    return lhs.node == rhs.node;
}

} } }

namespace concept { namespace parser {

template <>
struct import_document_base_traits<gntl::parser::libxml2::dom
                                   ::import_document_base>
{
  typedef boost::mpl::true_ is_import_document_base;
  typedef gntl::parser::libxml2::dom::import_document_base
    import_document_base;
  typedef import_document_base::import_ncl_iterator import_ncl_iterator;
  typedef boost::iterator_range<import_ncl_iterator> import_ncl_range;

  static import_ncl_range import_ncl_all(import_document_base b)
  {
    return import_ncl_range(b.node.begin (), b.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
