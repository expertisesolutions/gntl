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

#ifndef GNTL_PARSER_LIBXML2_DOM_IMPORT_NCL_HPP
#define GNTL_PARSER_LIBXML2_DOM_IMPORT_NCL_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>

#include <gntl/concept/parser/import/import_ncl.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 {
namespace dom {

struct import_ncl
{
  import_ncl(xml_node node)
    : node(node)
  {
      assert (::xmlStrcmp (this->node.node->name
                           , static_cast< ::xmlChar const*>(static_cast< void const*>("importNCL"))) == 0);
  }

  typedef xml_string<> document_uri_type;
  typedef xml_string<> alias_type;

  xml_string<> document_uri() const
  {
    return node["documentURI"].value ();
  }

  xml_string<> alias() const
  {
    return node["alias"].value ();
  }

  xml_node node;
};

inline bool operator==(import_ncl const& lhs, import_ncl const& rhs)
{
    return lhs.node == rhs.node;
}

} } }

namespace concept { namespace parser {

template <>
struct import_ncl_traits<gntl::parser::libxml2::dom::import_ncl>
{
  typedef gntl::parser::libxml2::dom::import_ncl import_ncl;
  typedef boost::mpl::true_ is_import_ncl;
  typedef import_ncl::document_uri_type document_uri_type;
  typedef import_ncl::alias_type alias_type;

  static document_uri_type document_uri(import_ncl n)
  {
    return n.document_uri();
  }

  static alias_type alias(import_ncl n)
  {
    return n.alias();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
