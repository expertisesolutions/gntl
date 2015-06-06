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

#ifndef GNTL_PARSER_LIBXML2_DOM_XML_STATEMENT_PREDICATE_HPP
#define GNTL_PARSER_LIBXML2_DOM_XML_STATEMENT_PREDICATE_HPP

#include <gntl/parser/libxml2/dom/xml_assessment_statement_predicate.hpp>
#include <gntl/parser/libxml2/dom/xml_compound_statement_predicate.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

struct xml_statement_predicate
{
  typedef bool result_type;
  result_type operator()(xml_node& node) const
  {
    return xml_assessment_statement_predicate()(node) || xml_compound_statement_predicate()(node);
  }
};

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
