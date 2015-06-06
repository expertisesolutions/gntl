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

#ifndef GNTL_PARSER_LIBXML2_DOM_DOCUMENT_HPP
#define GNTL_PARSER_LIBXML2_DOM_DOCUMENT_HPP

#include <gntl/parser/libxml2/dom/head.hpp>
#include <gntl/parser/libxml2/dom/body.hpp>
#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/xml_head_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_body_predicate.hpp>

#include <gntl/concept/parser/document/document.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

namespace document_detail {
struct true_predicate
{
    typedef bool result_type;
    result_type operator()(xml_node n) const
    {
        return true; 
    }
};
}

struct document
{
    typedef dom::head head_type;
    typedef dom::body<dom::xml_string<> > body_type;
    typedef xml_string<> identifier_type;
    
    document (xml_node node = xml_node())
        : node (node)
    {
    }

    xml_node node;

    head_type head () const
    {
      xml_element_node_iterator<xml_node, document_detail::true_predicate>
        first (node.begin ())
        , last (node.end ());
      if(first != last && xml_head_predicate ()(*first))
        return head_type (*first);
      else
        GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                               , (error::reason<const char*>::type
                                  ("Document without a head node")));
    }

    identifier_type identifier () const
    {
      return node["id"].value ();
    }

    body_type body () const
    {
      xml_element_node_iterator<xml_node, document_detail::true_predicate>
        first (node.begin ())
        , last (node.end ());
      if(first == last || ++first == last
         || !xml_body_predicate ()(*first))
        return body_type (xml_node(), identifier());
      return body_type (*first, identifier ());
    }
};

} } }

namespace concept { namespace parser {

template <>
struct document_traits<gntl::parser::libxml2::dom
                       ::document>
{
  typedef gntl::parser::libxml2::dom::document document;
  typedef boost::mpl::true_ is_document;
  typedef document::head_type head_type;
  typedef document::body_type body_type;
  typedef document::identifier_type identifier_type;

  static head_type head(document d)
  {
    return d.head();
  }

  static body_type body(document d)
  {
    return d.body();
  }

  static identifier_type identifier(document d)
  {
    return d.identifier();
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
