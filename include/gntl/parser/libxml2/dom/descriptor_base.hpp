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

#ifndef GNTL_PARSER_LIBXML2_DOM_DESCRIPTOR_BASE_HPP
#define GNTL_PARSER_LIBXML2_DOM_DESCRIPTOR_BASE_HPP

#include <gntl/parser/libxml2/dom/descriptor.hpp>
#include <gntl/parser/libxml2/dom/import_base.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_import_base_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_descriptor_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/concept/parser/descriptor/descriptor_base.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct descriptor_base
{
    descriptor_base ()
        : node (0) {}
    descriptor_base (xml_node node)
        : node (node) {}

    typedef descriptor descriptor_type;
    typedef xml_element_node_iterator<descriptor, xml_descriptor_predicate> descriptor_iterator;

    typedef import_base import_base_type;
    typedef xml_element_node_iterator<import_base, xml_import_base_predicate> import_base_iterator;

    typedef descriptor_iterator iterator;
    typedef descriptor_iterator const_iterator;

    iterator begin () const
    {
        if(node != xml_node (0))
            return node.begin ();
        else
            return node;
    }

    iterator end () const
    {
        if(node != xml_node (0))
            return node.end ();
        else
            return node;
    }

    bool has_identifier() const
    {
      if(node != xml_node (0))
        return node["id"];
      else
        return false;
    }

    xml_string<> identifier() const
    {
      assert (node != xml_node (0));
      return node["id"].value ();
    }

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct descriptor_base_traits<gntl::parser::libxml2::dom::descriptor_base>
{
    typedef gntl::parser::libxml2::dom::descriptor_base descriptor_base;
    typedef gntl::parser::libxml2::dom::xml_string<> identifier_type;
    typedef boost::mpl::true_ is_descriptor_base;
    typedef descriptor_base::import_base_iterator import_base_iterator;
    typedef boost::iterator_range<import_base_iterator> import_base_range;
    typedef descriptor_base::descriptor_iterator descriptor_iterator;
    typedef boost::iterator_range<descriptor_iterator> descriptor_range;

    static bool has_identifier (descriptor_base d)
    {
      return d.has_identifier();
    }

    static identifier_type identifier (descriptor_base d)
    {
      return d.identifier();
    }

    static import_base_range import_base_all(descriptor_base d)
    {
      return import_base_range(d.node.begin(), d.node.end());
    }

    static descriptor_range descriptor_all (descriptor_base d)
    {
      return descriptor_range(d.begin (), d.end());
    }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
