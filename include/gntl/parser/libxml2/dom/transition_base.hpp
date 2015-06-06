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

#ifndef GNTL_PARSER_LIBXML2_DOM_TRANSITION_BASE_HPP
#define GNTL_PARSER_LIBXML2_DOM_TRANSITION_BASE_HPP

#include <gntl/concept/parser/transition/transition_base.hpp>
#include <gntl/parser/libxml2/dom/transition.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_transition_predicate.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct transition_base
{
    transition_base (xml_node node)
        : node (node) {}

    typedef transition transition_type;
    typedef dom::xml_element_node_iterator<transition, xml_transition_predicate> transition_iterator;

    typedef xml_string<> identifier_type;

    xml_node node;
};

} } }

namespace concept { namespace parser {

template <>
struct transition_base_traits<gntl::parser::libxml2::dom::transition_base>
{
  typedef boost::mpl::true_ is_transition_base;
  typedef gntl::parser::libxml2::dom::transition_base transition_base;
  typedef transition_base::identifier_type identifier_type;
  typedef transition_base::transition_iterator transition_iterator;
  typedef boost::iterator_range<transition_iterator> transition_range;

  static bool has_identifier (transition_base t)
  {
    return t.node["id"];
  }

  static identifier_type identifier (transition_base t)
  {
    return t.node["id"].value ();
  }

  static transition_range transition_all (transition_base t)
  {
    return transition_range (t.node.begin (), t.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
