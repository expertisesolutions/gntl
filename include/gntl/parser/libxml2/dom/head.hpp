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

#ifndef GNTL_PARSER_LIBXML2_DOM_HEAD_HPP
#define GNTL_PARSER_LIBXML2_DOM_HEAD_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/import_document_base.hpp>
#include <gntl/parser/libxml2/dom/rule_base.hpp>
#include <gntl/parser/libxml2/dom/transition_base.hpp>
#include <gntl/parser/libxml2/dom/region_base.hpp>
#include <gntl/parser/libxml2/dom/descriptor_base.hpp>
#include <gntl/parser/libxml2/dom/connector_base.hpp>
#include <gntl/parser/libxml2/dom/xml_region_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_imported_document_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_rule_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_transition_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_descriptor_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_connector_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_algorithm.hpp>

#include <gntl/concept/parser/head/head.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct head
{
    head (xml_node node)
        : node (node) {}

    typedef dom::import_document_base import_document_base_type;
    typedef dom::rule_base rule_base_type;
    typedef dom::transition_base transition_base_type;
    typedef dom::region_base region_base_type;
    typedef dom::descriptor_base descriptor_base_type;
    typedef dom::connector_base connector_base_type;
    typedef xml_element_node_iterator<region_base, xml_region_base_predicate> region_base_iterator;

    bool has_import_document_base () const
    {
      xml_node end;
      xml_node r = find (node.begin ()
                         , end, xml_imported_document_base_predicate ());
      return r != end;
    }

    import_document_base_type import_document_base () const
    {
      xml_node end;
      return find (node.begin (), end, xml_imported_document_base_predicate ());
    }

    bool has_rule_base () const
    {
      xml_node end;
      xml_node r = find (node.begin (), end, xml_rule_base_predicate ());
      return r != end;
    }

    rule_base_type rule_base () const
    {
      xml_node end;
      return find (node.begin (), end, xml_rule_base_predicate ());
    }

    bool has_descriptor_base () const
    {
      xml_node end;
      xml_node r = find (node.begin (), end
                            , xml_descriptor_base_predicate ());
      return r != end;
    }

    descriptor_base_type descriptor_base () const
    {
      xml_node end;
      return find (node.begin (), end, xml_descriptor_base_predicate ());
    }

    bool has_transition_base () const
    {
      xml_node end;
      xml_node r = find (node.begin (), end, xml_transition_base_predicate ());
      return r != end;
    }

    transition_base_type transition_base () const
    {
      xml_node end;
      return find (node.begin (), end, xml_transition_base_predicate ());
    }

    bool has_connector_base () const
    {
      xml_node end;
      xml_node r = find (node.begin (), end, xml_connector_base_predicate ());
      return r != end;
    }

    connector_base_type connector_base () const
    {
      xml_node end;
      return find (node.begin (), end, xml_connector_base_predicate ());
    }

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct head_traits<gntl::parser::libxml2::dom::head>
{
  typedef gntl::parser::libxml2::dom::head head;
  typedef boost::mpl::true_ is_head;

  typedef head::import_document_base_type import_document_base_type;
  typedef head::rule_base_type rule_base_type;
  typedef head::transition_base_type transition_base_type;
  typedef head::descriptor_base_type descriptor_base_type;
  typedef head::connector_base_type connector_base_type;
  typedef head::region_base_iterator region_base_iterator;
  typedef boost::iterator_range<region_base_iterator> region_base_range;

  static bool has_import_document_base (head h)
  {
    return h.has_import_document_base();
  }

  static import_document_base_type import_document_base (head h)
  {
    return h.import_document_base();
  }

  static bool has_rule_base (head h)
  {
    return h.has_rule_base();
  }

  static rule_base_type rule_base (head h)
  {
    return h.rule_base();
  }

  static bool has_descriptor_base (head h)
  {
    return h.has_descriptor_base();
  }

  static descriptor_base_type descriptor_base (head h)
  {
    return h.descriptor_base();
  }

  static bool has_transition_base (head h)
  {
    return h.has_transition_base();
  }

  static transition_base_type transition_base (head h)
  {
    return h.transition_base();
  }

  static bool has_connector_base (head h)
  {
    return h.has_connector_base();
  }

  static connector_base_type connector_base (head h)
  {
    return h.connector_base();
  }

  static region_base_range region_base_all (head h)
  {
    return region_base_range (h.node.begin(), h.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
