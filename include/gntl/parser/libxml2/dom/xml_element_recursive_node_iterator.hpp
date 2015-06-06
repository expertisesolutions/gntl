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

#ifndef GNTL_PARSER_LIBXML2_DOM_XML_RECURSIVE_NODE_ITERATOR_HPP
#define GNTL_PARSER_LIBXML2_DOM_XML_RECURSIVE_NODE_ITERATOR_HPP

#include <gntl/log/log.hpp>
#include <gntl/concept/tree_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/utility.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/function.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

template <typename T, typename Predicate>
struct xml_element_recursive_node_iterator : boost::iterator_facade
  <xml_element_recursive_node_iterator<T, Predicate>, T, std::forward_iterator_tag, T>
{
    typedef Predicate predicate_type;
    
    template <typename PathIterator, typename SegmentPredicate>
    xml_element_recursive_node_iterator (xml_node segment
                                         , SegmentPredicate segment_predicate
                                         , PathIterator path_first
                                         , PathIterator path_last
                                         , Predicate p = Predicate ())
        : path (path_first, path_last)
        , segment (segment)
        , segment_predicate (segment_predicate), p (p)
    {
      GNTL_DEBUG_LOG("xml_element_recursive_node_iterator "
                     << __FILE__ ":" << __LINE__
                     << " " << path.size())
        if(segment != xml_node ())
          GNTL_DEBUG_LOG(segment.name () << std::endl)
        else
          GNTL_DEBUG_LOG(std::endl)
    }

    template <typename SegmentPredicate>
    xml_element_recursive_node_iterator (xml_node segment
                                         , SegmentPredicate segment_predicate
                                         , Predicate p = Predicate ())
        : segment (segment)
        , segment_predicate (segment_predicate), p (p)
    {
        // GNTL_DEBUG_LOG("xml_element_recursive_node_iterator "
        //           << __FILE__ ":" << __LINE__)
        // if(segment != xml_node ())
        //     GNTL_DEBUG_LOG(" " << segment.name () << std::endl)
        // else
        //     GNTL_DEBUG_LOG(" end iterator" << std::endl)
        path.insert (path.begin (), segment);
    }

    void increment ()
    {
        // GNTL_DEBUG_LOG("xml_element_recursive_node_iterator "
        //           << __FILE__ ":" << __LINE__ 
        //           << " " << current_node().name()
        //           << " " << current_node().xmlnode_holder.xmlnode << std::endl)
        assert(!is_end_iterator());
        xml_node end(0);
        do
        {
          // if is not end iterator, we can always increment
          if(!path.empty () && path.back () == end)
          {
              // GNTL_DEBUG_LOG("path.back() == end "
              //           << path.back().xmlnode_holder.xmlnode
              //           << " " << path.size() << std::endl)
              path.pop_back ();
              // GNTL_DEBUG_LOG("1path.back() == end "
              //           << path.back().xmlnode_holder.xmlnode
              //           << " " << path.size() << std::endl)
              path.back() = next_valid(path.back());
              // GNTL_DEBUG_LOG("2path.back() == end "
              //           << path.back().xmlnode_holder.xmlnode
              //           << " " << path.size() << std::endl)
              if(!is_valid(path.back ()))
                  path.back () = next_valid(path.back ());

              if(path.back () != end)
                  break;
          }
          else
          {
            // GNTL_DEBUG_LOG("depth-first "
            //             << path.back().xmlnode_holder.xmlnode
            //           << " " << path.size() << std::endl)
            // make depth-first try
            xml_node child = current_node ().begin();
            if(!is_valid(child))
              child = next_valid(child);
            path.push_back(child);
            // GNTL_DEBUG_LOG("1depth-first "
            //             << path.back().xmlnode_holder.xmlnode
            //           << " " << path.size() << std::endl)


            if(path.back () != end)
              break;
          }
        }
        while(!is_end_iterator());
        // GNTL_DEBUG_LOG("after" << std::endl)
        // if(!is_end_iterator ())
        //     GNTL_DEBUG_LOG("current node " << current_node ().name ()
        //               << " node ptr: " << current_node ().xmlnode_holder.xmlnode << std::endl)
        // else
        //     GNTL_DEBUG_LOG("end iterator" << std::endl)
    }
    T dereference () const
    {
        // GNTL_DEBUG_LOG("xml_element_recursive_node_iterator "
        //           << std::flush
        //           << __FILE__ ":" << __LINE__
        //           << std::flush
        //           << " name: " << current_node ().name ()
        //           << " ptr: " << current_node ().xmlnode_holder.xmlnode << std::endl)
        return current_node (); 
    }
    bool equal (xml_element_recursive_node_iterator const& other) const
    {
        // An iterator can increment past its segment
        // so we must not assert that they have the same
        // segment
        assert (!other.is_end_iterator () || !is_end_iterator ()
                || (path.size () == other.path.size ()
                    && std::equal(path.begin(), path.end(), other.path.begin())));

        return path.size() == other.path.size()
          && std::equal(path.begin(), path.end(), other.path.begin());
    }

    bool is_valid(xml_node node)
    {
      xml_node end(0);
      return node == end || (node.node->type == XML_ELEMENT_NODE && p (node));
    }

    xml_node next_valid(xml_node node)
    {
      xml_node end(0);
      do
      {
        ++node;
      } while(!is_valid(node));
      return node;
    }

    struct not_equal
    {
      not_equal(xml_node cmp)
        : cmp(cmp) {}
      typedef bool result_type;
      result_type operator()(xml_node node) const
      {
        return cmp != node;
      }
      xml_node cmp;
    };

    bool is_end_iterator() const
    {
      xml_node end;
      return std::find_if(path.begin(), path.end(), not_equal(end)) == path.end();
    }

    xml_node current_node () const
    {
        return path.back ();
    }

    std::vector<xml_node> path;
    xml_node segment;
    boost::function<bool(xml_node)> segment_predicate;
    Predicate p;
};

} } }

namespace concept {

template <typename T, typename Predicate>
struct tree_iterator_traits<gntl::parser::libxml2::dom
                            ::xml_element_recursive_node_iterator<T, Predicate> >
{
  typedef boost::mpl::true_ is_tree_iterator;
  typedef gntl::parser::libxml2::dom
          ::xml_element_recursive_node_iterator<T, Predicate>
    iterator;
  typedef gntl::parser::libxml2::dom
          ::xml_element_node_iterator<T, Predicate>
    node_iterator;

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
    return node_iterator(i.path.back(), i.p);
  }
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
