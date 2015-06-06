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

#ifndef GNTL_ARCHETYPE_PARSER_CONNECTOR_VALUE_ASSESSMENT_HPP
#define GNTL_ARCHETYPE_PARSER_CONNECTOR_VALUE_ASSESSMENT_HPP

#include <gntl/concept/parser/connector/connector_value_assessment.hpp>

namespace gntl { namespace archetype { namespace parser {

struct connector_value_assessment
{
};

} }

namespace concept { namespace parser {

template <>
struct connector_value_assessment_traits<archetype::parser::connector_value_assessment>
{
  typedef archetype::parser::connector_value_assessment connector_value_assessment;
  typedef boost::mpl::true_ is_connector_value_assessment;
  struct value_type {};
  static value_type value (connector_value_assessment);
};

} } }

#endif
