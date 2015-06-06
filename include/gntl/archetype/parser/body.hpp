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

#ifndef GNTL_ARCHETYPE_PARSER_BODY_HPP
#define GNTL_ARCHETYPE_PARSER_BODY_HPP

#include <boost/mpl/bool.hpp>

namespace gntl { namespace archetype { namespace parser {

namespace body_adl {

template <typename Context>
struct body
{
};

template <typename Context>
Context body_context (body<Context>);

}

using body_adl::body;

} }

namespace concept { namespace parser {

template <typename Context>
struct body_traits<archetype::parser::body<Context> >
{
  typedef archetype::parser::body<Context> body_type;
  typedef Context context_type;
  typedef boost::mpl::true_ is_body;

  static context_type context(body_type);
};

} } }

#endif
