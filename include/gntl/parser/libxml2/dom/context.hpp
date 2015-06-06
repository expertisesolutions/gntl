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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONTEXT_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONTEXT_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/port.hpp>
#include <gntl/parser/libxml2/dom/property.hpp>
#include <gntl/parser/libxml2/dom/media.hpp>
#include <gntl/parser/libxml2/dom/link.hpp>
#include <gntl/parser/libxml2/dom/switch.hpp>
#include <gntl/parser/libxml2/dom/xml_property_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_media_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_link_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_port_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_switch_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_context_predicate.hpp>
#include <gntl/concept/parser/property/property.hpp>
#include <gntl/concept/parser/context/context.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct context
{
    context() {}
    context (xml_node node)
        : node (node) {}

    typedef context context_type;
    typedef xml_element_node_iterator<context, xml_context_predicate> context_iterator;
    typedef xml_string<> identifier_type;
    typedef xml_string<> refer_type;

    typedef xml_element_node_iterator<dom::link, xml_link_predicate> link_iterator;

    typedef property property_type;
    typedef xml_element_node_iterator<property_type, xml_property_predicate> property_iterator;

    typedef media media_type;
    typedef xml_element_node_iterator<media_type, xml_media_predicate> media_iterator;

    typedef port port_type;
    typedef xml_element_node_iterator<port_type, xml_port_predicate> port_iterator;

    typedef switch_ switch_type;
    typedef xml_element_node_iterator<switch_type, xml_switch_predicate> switch_iterator;

    xml_node node;
};

inline context::property_iterator property_sequence_begin (context c)
{
  xml_node end;
  if(c.node != end)
    return c.node.begin ();
  else
    return end;
}

inline context::property_iterator property_sequence_end (context c)
{
  xml_node end;
  if(c.node != end)
    return c.node.end ();
  else
    return end;
}

} } }

namespace concept { namespace parser {

template <>
struct context_traits<gntl::parser::libxml2::dom::context>
{
  typedef gntl::parser::libxml2::dom::context context_type;
  typedef context_type::identifier_type identifier_type;
  typedef context_type::refer_type refer_type;
  typedef context_type::context_iterator context_iterator;
  typedef boost::iterator_range<context_iterator> context_range;
  typedef context_type::media_iterator media_iterator;
  typedef boost::iterator_range<media_iterator> media_range;
  typedef context_type::port_iterator port_iterator;
  typedef boost::iterator_range<port_iterator> port_range;
  typedef context_type::link_iterator link_iterator;
  typedef boost::iterator_range<link_iterator> link_range;
  typedef context_type::switch_iterator switch_iterator;
  typedef boost::iterator_range<switch_iterator> switch_range;
  typedef context_type::property_iterator property_iterator;
  typedef boost::iterator_range<property_iterator> property_range;

  static identifier_type identifier(context_type const& c)
  {
    return c.node["id"].value ();
  }

  static bool has_refer (context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    return c.node != end && c.node["refer"];
  }

  static context_type::refer_type refer (context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return c.node["refer"].value();
    else
      return refer_type();
  }

  static context_range context_all (context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return context_range(context_iterator(c.node.begin ()), context_iterator(c.node.end()));
    else
      return context_range(context_iterator(end), context_iterator(end));
  }
  static media_range media_all(context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return media_range(c.node.begin(), c.node.end());
    else
      return media_range(end, end);
  }
  static port_range port_all(context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return port_range(c.node.begin(), c.node.end());
    else
      return port_range(end, end);
  }
  static link_range link_all(context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return link_range(c.node.begin(), c.node.end());
    else
      return link_range(end, end);
  }
  static switch_range switch_all(context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return switch_range(c.node.begin(), c.node.end());
    else
      return switch_range(end, end);
  }
  static property_range property_all(context_type const& c)
  {
    gntl::parser::libxml2::dom::xml_node end;
    if(c.node != end)
      return property_range(c.node.begin(), c.node.end());
    else
      return property_range(end, end);
  }
};

inline switch_traits<gntl::parser::libxml2::dom::switch_>::context_range
switch_traits<gntl::parser::libxml2::dom::switch_>::context_all(switch_type s)
{
  gntl::parser::libxml2::dom::xml_node end;
  if(s.node != end)
    return context_range(context_iterator(s.node.begin ()), context_iterator(s.node.end()));
  else
    return context_range(context_iterator(end), context_iterator(end));
}

} } }


#include <gntl/detail/pop_options.hpp>

#endif
