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

#ifndef GNTL_PARSER_LIBXML2_DOM_XML_NODE_ITERATOR_HPP
#define GNTL_PARSER_LIBXML2_DOM_XML_NODE_ITERATOR_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/concept/tree_iterator.hpp>

#include <boost/iterator/iterator_facade.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

template <typename T, typename Predicate>
struct xml_element_node_iterator : boost::iterator_facade
  <xml_element_node_iterator<T, Predicate>, T, std::forward_iterator_tag, T>
{
    xml_element_node_iterator (xml_node node, Predicate p = Predicate ())
        : node (node), p (p)
    {
        xml_node end(0);
        if(node != end
           && (node.node->type != XML_ELEMENT_NODE
               || !p (node)))
            increment();
    }

    xml_element_node_iterator ()
        : node (0)
    {}

    void increment ()
    {
        xml_node end(0);
        do
        {
            ++node;
        } 
        while(node != end
              && (node.node->type != XML_ELEMENT_NODE
                  || !p (node)));
    }
    T dereference () const
    {
      xml_node end;
      assert(node != end);
      return node; 
    }
    bool equal (xml_element_node_iterator const& other) const
    {
        return node == other.node;
    }

    xml_node node;
    Predicate p;
};

} } }

namespace concept {

template <typename T, typename Predicate>
struct tree_iterator_traits<gntl::parser::libxml2::dom
                            ::xml_element_node_iterator<T, Predicate> >
{
  typedef boost::mpl::true_ is_tree_iterator;
  typedef gntl::parser::libxml2::dom
          ::xml_element_node_iterator<T, Predicate>
    iterator;
  typedef iterator node_iterator;

  static node_iterator begin(node_iterator i)
  {
    return node_iterator(i.node.begin(), i.p);
  }

  static node_iterator end(node_iterator i)
  {
    return node_iterator(i.node.end(), i.p);
  }

  static node_iterator node(iterator i)
  {
    return i;
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
