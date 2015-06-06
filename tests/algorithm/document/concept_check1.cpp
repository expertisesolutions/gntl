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

#include <gntl/structure/composed/document.hpp>
#include <gntl/concept_check.hpp>
#include <boost/concept_archetype.hpp>
#include <gntl/archetype/parser/descriptor.hpp>
#include <gntl/archetype/parser/descriptor_param.hpp>
#include <gntl/archetype/parser/region.hpp>
#include <gntl/archetype/parser/coordinate.hpp>
#include <gntl/archetype/parser/link.hpp>
#include <gntl/archetype/parser/media.hpp>
#include <gntl/archetype/parser/port.hpp>
#include <gntl/archetype/parser/context.hpp>
#include <gntl/archetype/parser/area.hpp>
#include <gntl/archetype/parser/property.hpp>
#include <gntl/archetype/parser/link_param.hpp>
#include <gntl/archetype/parser/bind.hpp>
#include <gntl/archetype/parser/bind_param.hpp>
#include <gntl/archetype/parser/causal_connector.hpp>
#include <gntl/archetype/parser/connector_condition_expression.hpp>
#include <gntl/archetype/parser/document.hpp>
#include <gntl/archetype/parser/connector_simple_condition.hpp>
#include <gntl/archetype/parser/connector_simple_action.hpp>
#include <gntl/archetype/parser/connector_compound_action.hpp>
#include <gntl/archetype/parser/connector_action.hpp>
#include <gntl/archetype/parser/connector_parameter.hpp>
#include <gntl/archetype/structure/presentation.hpp>
#include <gntl/archetype/structure/presentation_factory.hpp>
#include <gntl/archetype/rgb_color.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/descriptor.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/descriptor_lookupable.hpp>

void foo ()
{
    namespace archetype = gntl::archetype;
    typedef archetype::parser::descriptor
      <archetype::parser::descriptor_param
      , archetype::rgb_color>
        descriptor_parser_type;
    typedef boost::forward_iterator_archetype<descriptor_parser_type> descriptor_iterator_type;
    typedef boost::iterator_range<descriptor_iterator_type> descriptor_range_type;

    typedef archetype::parser::coordinate coordinate;
    typedef archetype::parser::region<coordinate> region_type;
    typedef boost::iterator_range<boost::input_iterator_archetype<region_type> > region_range_type;
    typedef archetype::parser::link
      <archetype::parser::bind<archetype::parser::bind_param>
      , archetype::parser::link_param> link_parser_type;
    typedef gntl::structure::composed::link
      <link_parser_type
      , archetype::parser::causal_connector
      < archetype::parser::connector_condition_expression
         <boost::mpl::vector<archetype::parser::connector_simple_condition> >
        , archetype::parser::connector_action
          <archetype::parser::connector_simple_action
          , archetype::parser::connector_compound_action
         <archetype::parser::connector_simple_action> >
        , archetype::parser::connector_parameter>
      >
      link_type;
    typedef gntl::structure::composed::descriptor
      <descriptor_parser_type, std::string> descriptor_type;
    typedef archetype::parser::media
      <
        archetype::parser::area
      , archetype::parser::property
      > media_parser_type;
    typedef gntl::structure::composed::media
      <media_parser_type
      , archetype::structure::presentation_factory
      <archetype::structure::presentation>
      > media_type;
    typedef archetype::parser::port port_type;
    typedef gntl::structure::composed::context
      <archetype::parser::context
      <media_parser_type, archetype::parser::property
      , archetype::parser::port, link_parser_type> > context_type;
    typedef gntl::structure::composed::descriptor_lookupable
      <descriptor_range_type> descriptor_lookupable;
    GNTL_CONCEPT_ASSERT
        ((gntl::concept::structure::Document
          <gntl::structure::composed::document
          <descriptor_lookupable
          ,region_range_type, context_type> >));
}
