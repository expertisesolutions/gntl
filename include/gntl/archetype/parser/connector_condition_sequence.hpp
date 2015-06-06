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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_SEQUENCE_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_CONDITION_SEQUENCE_HPP

namespace gntl { namespace archetype { namespace parser {

namespace connector_condition_sequence_adl {

template <typename Condition>
struct connector_condition_sequence
{
  typedef Condition condition_type;
  typedef boost::input_iterator_archetype<condition_type> condition_iterator;
};

template <typename Condition>
typename connector_condition_sequence<Condition>::condition_iterator
 connector_condition_sequence_begin (connector_condition_sequence<Condition>);
template <typename Condition>
typename connector_condition_sequence<Condition>::condition_iterator
 connector_condition_sequence_end (connector_condition_sequence<Condition>);

}

using connector_condition_sequence_adl::connector_condition_sequence;

} } }

#endif
