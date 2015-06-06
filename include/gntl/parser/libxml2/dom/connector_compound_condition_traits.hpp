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

#ifndef GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_CONDITION_TRAITS_HPP
#define GNTL_PARSER_LIBXML2_DOM_CONNECTOR_COMPOUND_CONDITION_TRAITS_HPP

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <>
struct connector_compound_condition_traits<gntl::parser::libxml2::dom
                                           ::connector_compound_condition>
{
  typedef boost::mpl::true_ is_connector_compound_condition;
  typedef gntl::parser::libxml2::dom::connector_compound_condition
    connector_compound_condition;
  typedef connector_compound_condition::operator_type operator_type;
  typedef connector_compound_condition::delay_type delay_type;
  typedef boost::iterator_range<connector_compound_condition
                                ::condition_iterator> 
    condition_expression_range;

  static operator_type operator_ (connector_compound_condition c)
  {
    return c.node["operator"].value ();
  }

  static bool has_delay (connector_compound_condition c)
  {
    return c.node["delay"];
  }

  static delay_type delay (connector_compound_condition c)
  {
    return gntl::parser::libxml2::dom
      ::time_duration_parser (c.node["delay"].value ());
  }
  
  static condition_expression_range
    condition_expression_all(connector_compound_condition c)
  {
    return condition_expression_range(c.node.begin()
                                      , c.node.end());
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
