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

#ifndef GNTL_STRUCTURE_COMPOSED_COMPONENT_LOCATION_HPP
#define GNTL_STRUCTURE_COMPOSED_COMPONENT_LOCATION_HPP

#include <gntl/concept/structure/component_location.hpp>

#include <vector>

namespace gntl { namespace structure { namespace composed {

template <typename ComponentIdentifier, typename DocumentURI>
struct component_location
{
  typedef ComponentIdentifier identifier_type;
  typedef DocumentURI document_uri_type;
  
  component_location(identifier_type identifier, document_uri_type document_uri)
    : identifier_(identifier), document_uri_(document_uri)
  {
  }

  template <typename PathIterator>
  component_location(identifier_type identifier, PathIterator first
                     , PathIterator last
                     , document_uri_type document_uri)
    : identifier_(identifier), path(first, last), document_uri_(document_uri)
  {
  }

  identifier_type identifier() const
  {
    return identifier_;
  }

  identifier_type identifier_;
  std::vector<identifier_type> path;
  document_uri_type document_uri_;
};

} }

namespace concept { namespace structure {

template <typename ComponentIdentifier, typename DocumentURI>
struct component_location_traits<gntl::structure::composed::component_location
                                 <ComponentIdentifier, DocumentURI> >
{
  typedef boost::mpl::true_ is_component_location;
  typedef gntl::structure::composed::component_location<ComponentIdentifier, DocumentURI>
    component_location;
  typedef DocumentURI document_uri_type;
  typedef ComponentIdentifier identifier_type;

  static identifier_type identifier(component_location const& c)
  {
    return c.identifier();
  }
  static document_uri_type document_uri(component_location const&);
  static component_location compose(component_location context
                                    , identifier_type const& identifier)
  {
    context.path.push_back(context.identifier());
    context.identifier_ = identifier;
    return context;
  }
};

} } }

#endif
