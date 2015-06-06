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

#ifndef GNTL_PARSER_LIBXML2_DOM_REGION_BASE_HPP
#define GNTL_PARSER_LIBXML2_DOM_REGION_BASE_HPP

#include <gntl/parser/libxml2/dom/region.hpp>
#include <gntl/parser/libxml2/dom/import_base.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_recursive_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_region_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_region_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_import_base_predicate.hpp>

#include <gntl/concept/parser/region/region_base.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct region_base
{
    region_base ()
        : node (0) {}
    region_base (xml_node node)
        : node (node) {}

    typedef region region_type;
    typedef xml_element_recursive_node_iterator<region, xml_region_predicate> region_iterator;
    typedef xml_string<> identifier_type;

    typedef import_base import_base_type;
    typedef xml_element_node_iterator<import_base, xml_import_base_predicate> import_base_iterator;

    typedef region_iterator iterator;
    typedef region_iterator const_iterator;

    iterator begin () const
    {
        xml_node end_;
        if(node != end_ && node.begin () != end_)
        {
            xml_element_node_iterator<region, xml_region_predicate> 
                region_iterator (node.begin ());
            return iterator (region_iterator.node
                             , xml_region_base_predicate ()
                             , &region_iterator.node, &region_iterator.node+1);
        }
        else
            return end ();
    }

    iterator end () const
    {
        xml_node end_;
        return iterator (end_
                         , xml_region_base_predicate ());
    }

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct region_base_traits<gntl::parser::libxml2::dom
                          ::region_base>
{
  typedef gntl::parser::libxml2::dom::region_base region_base;
  typedef boost::mpl::true_ is_region_base;
  typedef region_base::identifier_type identifier_type;
  typedef region_base::import_base_iterator import_base_iterator;
  typedef boost::iterator_range<import_base_iterator> import_base_range;
  typedef region_base::region_iterator region_iterator;
  typedef boost::iterator_range<region_iterator> region_range;

  static identifier_type identifier (region_base r)
  {
    using namespace gntl::parser::libxml2::dom;
    assert (r.node != xml_node (0));
    return r.node["id"].value ();
  }

  static bool has_identifier (region_base r)
  {
    using namespace gntl::parser::libxml2::dom;
    if(r.node != xml_node (0))
        return r.node["id"];
    else
        return false;
  }

  static import_base_range import_base_all(region_base d)
  {
    return import_base_range(d.node.begin(), d.node.end());
  }

  static region_range region_all (region_base b)
  {
    return region_range (b.begin(), b.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
