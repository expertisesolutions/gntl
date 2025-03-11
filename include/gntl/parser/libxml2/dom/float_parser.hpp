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

#ifndef GNTL_PARSER_LIBXML2_DOM_FLOAT_PARSER_HPP
#define GNTL_PARSER_LIBXML2_DOM_FLOAT_PARSER_HPP

#include <gntl/parser/libxml2/dom/xml_string.hpp>
#include <boost/version.hpp>
#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#endif

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
inline float float_parser (xml_string<> string)
{
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace arg_names = dom::spirit::arg_names;
    namespace phoenix = boost::phoenix;
    xml_string<>::const_iterator iterator = string.begin ();
    float r = 0.0f;
    qi::parse (iterator, string.end (), spirit::float_[phoenix::ref (r) = arg_names::_1]);
    return r;
}
#else
float float_parser (xml_string<> string); // not implemented yet
#endif

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
