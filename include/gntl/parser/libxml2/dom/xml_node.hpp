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

#ifndef GNTL_PARSER_LIBXML2_DOM_XML_NODE_HPP
#define GNTL_PARSER_LIBXML2_DOM_XML_NODE_HPP

#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/node_type_enum.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits/is_same.hpp>

#ifndef __SYMBIAN32__
#include <libxml/parser.h>
#else
#include <libxml2/libxml2_parser.h>
#endif

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct xml_node
{
    xml_node ()
        : node (0)
    {
    }
    xml_node (::xmlNodePtr xmlnode)
        : node (xmlnode)
    {

    }

    xml_node begin() const
    {
      xml_node x(node->children);
      return x;
    }

    xml_node end() const
    {
      return xml_node(0);
    }

    xml_node& operator++()
    {
      node = node->next;
      return *this; 
    }

    struct attribute_value
    {
        attribute_value (::xmlAttr* attribute)
            : attribute (attribute) {}

        bool operator!() const
        {
            return !attribute;
        }

        typedef bool (attribute_value::*unspecified_bool)() const;
        
        operator unspecified_bool () const
        {
            return attribute?&attribute_value::operator!
                : static_cast<unspecified_bool>(0);
        }

        xml_string<> value () const
        {
            if(attribute && attribute->children
               && attribute->children->content)
                return xml_string<>(attribute->children->content);
            else
                return xml_string<>();
        }

        ::xmlAttr* attribute;
    };

    attribute_value operator[](const char* name) const
    {
        ::xmlAttr* property = node->properties;
        while(property)
        {
            if(::xmlStrcmp (property->name, static_cast< ::xmlChar const*>(static_cast< void const*>(name))) == 0)
                break;
            property = property->next;
        }
        return attribute_value (property);
    }

    xml_string<> name() const
    {
      return xml_string<>(node->name);
    }
    node_type_enum node_type() const
    {
      BOOST_MPL_ASSERT((boost::is_same<boost::mpl::size_t<sizeof(std::size_t)>
                                       , boost::mpl::size_t<sizeof(node->_private)> >));
      std::size_t s = 0;
      std::memcpy(&s, &node->_private, sizeof(std::size_t));
      return static_cast<node_type_enum>(s);
    }
    void node_type(node_type_enum v) const
    {
      BOOST_MPL_ASSERT((boost::is_same<boost::mpl::size_t<sizeof(std::size_t)>
                                       , boost::mpl::size_t<sizeof(node->_private)> >));
      std::size_t s = static_cast<std::size_t>(v);
      std::memcpy(&node->_private, &s, sizeof(std::size_t));
    }

    ::xmlElementType type () const { return node->type; }

    ::xmlNodePtr node;
};

inline bool operator==(xml_node const& lhs, xml_node const& rhs)
{
  return lhs.node == rhs.node; 
}

inline bool operator!=(xml_node const& lhs, xml_node const& rhs)
{
  return !(lhs == rhs);
}

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
