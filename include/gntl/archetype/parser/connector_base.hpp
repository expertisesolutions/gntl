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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_BASE_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_BASE_HPP

#include <gntl/concept/parser/connector/connector_base.hpp>
#include <gntl/archetype/parser/causal_connector_sequence.hpp>

#include <boost/concept_archetype.hpp>

namespace gntl { namespace archetype { namespace parser {

template <typename CausalConnector, typename ImportBase>
struct connector_base : causal_connector_sequence<CausalConnector>
{
};

} }

namespace concept { namespace parser {

template <typename CausalConnector, typename ImportBase>
struct connector_base_traits<archetype::parser::connector_base<CausalConnector, ImportBase> >
{
  typedef boost::mpl::true_ is_connector_base;
  typedef archetype::parser::connector_base<CausalConnector, ImportBase> connector_base;
  struct identifier_type {};
  typedef boost::input_iterator_archetype<ImportBase> import_base_iterator;
  typedef boost::iterator_range<import_base_iterator> import_base_range;
  typedef boost::iterator_range<boost::input_iterator_archetype<CausalConnector> >
    causal_connector_range;

  static identifier_type identifier(connector_base);
  static bool has_identifier(connector_base);
  static causal_connector_range causal_connector_all(connector_base);
  static import_base_range import_base_all(connector_base);
};

} } }

#endif
