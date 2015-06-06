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

#ifndef GNTL_ALGORITHM_PARSER_DOCUMENT_HPP
#define GNTL_ALGORITHM_PARSER_DOCUMENT_HPP

#include <gntl/concept/parser/document/document.hpp>
#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/concept/parser/connector/connector_base.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace parser { namespace document {

template <typename Document, typename UnaryFunction>
void for_each_import_document_uri(Document document, UnaryFunction f)
{
  // Ordering
  // importedDocumentBase?, ruleBase?, transitionBase?, regionBase*, descriptorBase?
  // , connectorBase?, meta*, metadata*.
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef concept::parser::document_traits<document_type> document_traits;
  typedef typename document_traits::head_type head_value_type;
  typedef typename unwrap_parameter<head_value_type>::type head_type;
  typedef concept::parser::head_traits<head_type> head_traits;

  typedef typename head_traits::import_document_base_type import_document_base_value_type;
  typedef typename head_traits::region_base_range region_base_range_value_type;
  typedef typename head_traits::descriptor_base_type descriptor_base_value_type;
  typedef typename head_traits::connector_base_type connector_base_value_type;

  head_value_type head = document_traits::head(document);

  if(head_traits::has_import_document_base(head))
  {
    import_document_base_value_type import_document_base = head_traits::import_document_base(head);
    typedef typename unwrap_parameter<import_document_base_value_type>::type import_document_base_type;
    typedef concept::parser::import_document_base_traits<import_document_base_type> import_document_base_traits;
    typedef typename import_document_base_traits::import_ncl_range import_ncl_value_range;
    import_ncl_value_range import_ncls = import_document_base_traits::import_ncl_all(import_document_base);
    typedef typename unwrap_parameter<import_ncl_value_range>::type import_ncl_range;
    typedef typename boost::range_iterator<import_ncl_range>::type import_ncl_iterator;
    for(import_ncl_iterator first = boost::begin(import_ncls)
          , last = boost::end(import_ncls); first != last; ++first)
    {
      typedef typename boost::range_value<import_ncl_range>::type import_ncl_value_type;
      typedef typename unwrap_parameter<import_ncl_value_type>::type import_ncl_type;
      typedef concept::parser::import_ncl_traits<import_ncl_type> import_ncl_traits;
      f(import_ncl_traits::document_uri(*first));
    }
  }

  region_base_range_value_type region_bases = head_traits::region_base_all(head);
  typedef typename unwrap_parameter<region_base_range_value_type>::type region_base_range;
  typedef typename boost::range_iterator<region_base_range>::type region_base_iterator;
  for(region_base_iterator first = boost::begin(region_bases), last = boost::end(region_bases)
        ;first != last;++first)
  {
    typedef typename boost::range_value<region_base_range>::type region_base_value_type;
    typedef typename unwrap_parameter<region_base_value_type>::type region_base_type;

    typedef concept::parser::region_base_traits<region_base_type> region_base_traits;
    typedef typename region_base_traits::import_base_range import_base_range_value_type;
    import_base_range_value_type import_bases = region_base_traits::import_base_all(*first);
    typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
    typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
    for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
          ;first != last;++first)
    {
      typedef typename boost::range_value<import_base_range>::type import_base_value_type;
      typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;
      typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
      f(import_base_traits::document_uri(*first));
    }
  }
  
  if(head_traits::has_descriptor_base(head))
  {
    descriptor_base_value_type descriptor_base = head_traits::descriptor_base(head);

    typedef typename unwrap_parameter<descriptor_base_value_type>::type descriptor_base_type;
    typedef concept::parser::descriptor_base_traits<descriptor_base_type> descriptor_base_traits;

    typedef typename descriptor_base_traits::import_base_range import_base_range_value_type;
    import_base_range_value_type import_bases = descriptor_base_traits::import_base_all(descriptor_base);

    typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
    typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
    for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
          ;first != last;++first)
    {
      typedef typename boost::range_value<import_base_range>::type import_base_value_type;
      typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;

      typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
      f(import_base_traits::document_uri(*first));
    }
  }

  if(head_traits::has_connector_base(head))
  {
    connector_base_value_type connector_base = head_traits::connector_base(head);

    typedef typename unwrap_parameter<connector_base_value_type>::type connector_base_type;
    typedef concept::parser::connector_base_traits<connector_base_type> connector_base_traits;

    typedef typename connector_base_traits::import_base_range import_base_range_value_type;
    import_base_range_value_type import_bases = connector_base_traits::import_base_all(connector_base);

    typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
    typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
    for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
          ;first != last;++first)
    {
      typedef typename boost::range_value<import_base_range>::type import_base_value_type;
      typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;

      typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
      f(import_base_traits::document_uri(*first));
    }
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
