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

#ifndef GNTL_PARSER_LIBXML2_DOM_NODE_TYPE_ENUM_HPP
#define GNTL_PARSER_LIBXML2_DOM_NODE_TYPE_ENUM_HPP

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

namespace node_type {

enum node_type_enum
{
  unknown_node = 0
  , area_node
  , bind_node
  , bind_param_node
  , bind_rule_node
  , body_node
  , causal_connector_node
  , compound_action_node
  , compound_condition_node
  , compound_statement_node
  , simple_action_node
  , simple_condition_node
  , assessment_statement_node
  , value_assessment_node
  , context_node
  , descriptor_base_node
  , descriptor_node
  , descriptor_param_node
  , head_node
  , import_base_node
  , imported_document_base_node
  , import_ncl_node
  , link_node
  , link_param_node
  , media_node
  , port_node
  , property_node
  , region_base_node
  , region_node
  , rule_base_node
  , rule_node
  , composite_rule_node
  , switch_node
  , switch_port_node
  , transition_base_node
  , transition_node
  , default_component_node
  , connector_param_node
  , connector_base_node
};

}

using node_type::node_type_enum;

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
