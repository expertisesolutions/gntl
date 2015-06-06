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

#ifndef GNTL_PARSER_LIBXML2_DOM_COLOR_PARSER_HPP
#define GNTL_PARSER_LIBXML2_DOM_COLOR_PARSER_HPP

#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <gntl/parser/libxml2/dom/color.hpp>

#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>
#endif
#include <boost/optional.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

namespace spirit {
#if BOOST_VERSION >= 104200
    namespace arg_names = boost::spirit::qi;
#else
    namespace arg_names = boost::spirit::arg_names;
#endif
}

#if BOOST_VERSION >= 104000
inline boost::optional<color> color_parser (xml_string<> string)
{
  namespace qi = boost::spirit::qi;
  namespace spirit = boost::spirit;
  namespace arg_names = dom::spirit::arg_names;
  namespace phoenix = boost::phoenix;
  xml_string<>::const_iterator iterator = string.begin();
  color c;
  if(qi::parse (iterator, string.end()
                , spirit::lit("white")[phoenix::ref(c) = phoenix::construct<color>(255u,255u,255u)]
                | spirit::lit("black")[phoenix::ref(c) = phoenix::construct<color>(0u,0u,0u)]
                | spirit::lit("silver")[phoenix::ref(c) = phoenix::construct<color>(192u,192u,192u)]
                | spirit::lit("gray")[phoenix::ref(c) = phoenix::construct<color>(128u,128u,128u)]
                | spirit::lit("red")[phoenix::ref(c) = phoenix::construct<color>(255u,0u,0u)]
                | spirit::lit("maroon")[phoenix::ref(c) = phoenix::construct<color>(128u,0u,0u)]
                | spirit::lit("fuchsia")[phoenix::ref(c) = phoenix::construct<color>(255u,0u,255u)]
                | spirit::lit("purple")[phoenix::ref(c) = phoenix::construct<color>(128u,0u,128u)]
                | spirit::lit("lime")[phoenix::ref(c) = phoenix::construct<color>(0u,255u,0u)]
                | spirit::lit("green")[phoenix::ref(c) = phoenix::construct<color>(0u,128u,0u)]
                | spirit::lit("yellow")[phoenix::ref(c) = phoenix::construct<color>(255u,255u,0u)]
                | spirit::lit("olive")[phoenix::ref(c) = phoenix::construct<color>(128u,128u,0u)]
                | spirit::lit("blue")[phoenix::ref(c) = phoenix::construct<color>(0u,0u,255u)]
                | spirit::lit("navy")[phoenix::ref(c) = phoenix::construct<color>(0u,0u,128u)]
                | spirit::lit("aqua")[phoenix::ref(c) = phoenix::construct<color>(0u,255u,255u)]
                | spirit::lit("teal")[phoenix::ref(c) = phoenix::construct<color>(0u,128u,128u)])
     && iterator == string.end())
    return c;
  else
    return boost::none;
}
#else
boost::optional<color> color_parser (xml_string<> string);
#endif
} } } }


#include <gntl/detail/pop_options.hpp>

#endif
