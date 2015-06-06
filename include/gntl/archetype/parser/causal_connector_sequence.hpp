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

#ifndef GNTL_ARCHETYPE_PARSER_CAUSAL_CONNECTOR_SEQUENCE_HPP
#define GNTL_ARCHETYPE_PARSER_CAUSAL_CONNECTOR_SEQUENCE_HPP

namespace gntl { namespace archetype { namespace parser {

namespace causal_connector_sequence_adl {

template <typename CausalConnector>
struct causal_connector_sequence
{
    typedef CausalConnector causal_connector_type;
    typedef boost::input_iterator_archetype<causal_connector_type> causal_connector_iterator;
};

template <typename CausalConnector>
typename causal_connector_sequence<CausalConnector>::causal_connector_iterator 
causal_connector_sequence_begin (causal_connector_sequence<CausalConnector>);
template <typename CausalConnector>
typename causal_connector_sequence<CausalConnector>::causal_connector_iterator 
causal_connector_sequence_end (causal_connector_sequence<CausalConnector>);

}

using causal_connector_sequence_adl::causal_connector_sequence;

} } }

#endif
