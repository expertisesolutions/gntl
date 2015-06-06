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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_STATEMENT_SEQUENCE_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_STATEMENT_SEQUENCE_HPP

namespace gntl { namespace archetype { namespace parser {

namespace connector_statement_sequence_adl {

template <typename Statement>
struct connector_statement_sequence
{
    typedef Statement statement_type;
    typedef boost::input_iterator_archetype<statement_type> statement_iterator;
};

template <typename Statement>
typename connector_statement_sequence<Statement>::statement_iterator
 connector_statement_sequence_begin (connector_statement_sequence<Statement>);
template <typename Statement>
typename connector_statement_sequence<Statement>::statement_iterator
 connector_statement_sequence_end (connector_statement_sequence<Statement>);

}

using connector_statement_sequence_adl::connector_statement_sequence;

} } }

#endif
