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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_ACTION_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_ACTION_HPP

#include <gntl/parser/libxml2/dom/xml_node.hpp>
#include <gntl/parser/libxml2/dom/xml_element_node_iterator.hpp>
#include <gntl/parser/libxml2/dom/xml_action_predicate.hpp>
#include <gntl/concept/parser/connector/connector_compound_action.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct connector_action;

struct connector_compound_action
{
  connector_compound_action(xml_node node)
    : node(node) {}

  typedef connector_action action_type;
  typedef xml_element_node_iterator<action_type, xml_action_predicate> action_iterator;

  xml_node node;
};

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
