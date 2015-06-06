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

#ifndef GNTL_PARSER_LIBXML2_DOM_BODY_HPP
#define GNTL_PARSER_LIBXML2_DOM_BODY_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/context.hpp>
#include <gntl/concept/parser/body/body.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

template <typename DocumentIdentifier>
struct body_context_type : context
{
    body_context_type (xml_node node, DocumentIdentifier identifier)
        : context (node), identifier (identifier) {}
    body_context_type () {}

    DocumentIdentifier identifier;
};

template <typename DocumentIdentifier>
struct body
{
    body (xml_node node, DocumentIdentifier document_id)
        : node (node), document_id (document_id) {}

    typedef body_context_type<DocumentIdentifier> context_type;

    xml_node node;
    DocumentIdentifier document_id;
};

} } }

namespace concept { namespace parser {

template <typename DocumentIdentifier>
struct body_traits
  <gntl::parser::libxml2::dom::body<DocumentIdentifier> >
{
  typedef gntl::parser::libxml2::dom::body<DocumentIdentifier>
    body_type;
  typedef boost::mpl::true_ is_body;
  typedef typename body_type::context_type context_type;

  static context_type context (body_type const& b)
  {
    return context_type(b.node, b.document_id);
  }
};

template <typename DocumentIdentifier>
struct context_traits
  <gntl::parser::libxml2::dom::body_context_type
   <DocumentIdentifier> >
  : context_traits<gntl::parser::libxml2::dom::context>
{
  typedef gntl::parser::libxml2::dom::body_context_type<DocumentIdentifier> context_type;
  typedef boost::mpl::true_ is_context;
  typedef DocumentIdentifier identifier_type;

  static identifier_type identifier (context_type const& c)
  {
    if(!c.node["id"])
      return c.identifier;
    else
      return c.node["id"].value();
  }

  static bool has_identifier (context_type const& c)
  {
    return true;
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
