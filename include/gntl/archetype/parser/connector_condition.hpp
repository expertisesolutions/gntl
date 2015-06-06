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

// #ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_HPP
// #define GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_HPP

// #include <gntl/archetype/parser/connector_statement.hpp>
// #include <gntl/archetype/parser/connector_compound_condition.hpp>

// #include <boost/concept_archetype.hpp>

// namespace gntl { namespace archetype { namespace parser {

// template <typename SimpleCondition, typename CompoundCondition>
// struct connector_condition
// {
// };

// } }

// namespace concept { namespace parser {

// template <typename SimpleCondition, typename CompoundCondition>
// struct connector_condition_traits<archetype::parser
//                                   ::connector_condition<SimpleCondition, CompoundCondition> >
// {
//   typedef archetype::parser::connector_condition<SimpleCondition, CompoundCondition>
//     connector_condition;
//   typedef boost::mpl::true_ is_connector_condition;
//   typedef SimpleCondition simple_condition_type;
//   typedef CompoundCondition compound_condition_type;

//   static simple_condition_type simple_condition(connector_condition c);
//   static compound_condition_type compound_condition(connector_condition c);
//   static bool is_compound(connector_condition c);
// };

// } } }

// #endif
