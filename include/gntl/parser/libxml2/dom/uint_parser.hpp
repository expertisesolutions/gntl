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

#ifndef GNTL_PARSER_LIBXML2_DOM_UINT_PARSER_HPP
#define GNTL_PARSER_LIBXML2_DOM_UINT_PARSER_HPP

#include <gntl/parser/libxml2/dom/xml_string.hpp>

#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
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
inline boost::optional<unsigned int> uint_parser (xml_string<> string)
{
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace arg_names = dom::spirit::arg_names;
    namespace phoenix = boost::phoenix;
    unsigned int r = 0;
    xml_string<>::const_iterator iterator = string.begin ();
    if(qi::parse (iterator, string.end (), spirit::uint_[phoenix::ref (r) = arg_names::_1])
       && iterator == string.end())
      return r;
    else
      return boost::none;
}

inline boost::optional<int> int_parser (xml_string<> string)
{
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace arg_names = dom::spirit::arg_names;
    namespace phoenix = boost::phoenix;
    int r = 0;
    xml_string<>::const_iterator iterator = string.begin ();
    if(qi::parse (iterator, string.end (), spirit::int_[phoenix::ref (r) = arg_names::_1])
       && iterator == string.end())
       return r;
    else
      return boost::none;
}

inline boost::optional<int> focus_index_parser (xml_string<> string)
{
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
    namespace arg_names = dom::spirit::arg_names;
    namespace phoenix = boost::phoenix;
    int r = 0;
    xml_string<>::const_iterator iterator = string.begin ();
    qi::parse (iterator, string.end(), +(spirit::ascii::char_ - spirit::ascii::digit));
    if(iterator == string.end())
    {
      unsigned int r = 0;
      unsigned int signed_max = (std::numeric_limits<int>::max)();
      for(iterator = string.begin();iterator != string.end(); ++iterator)
      {
        r += *iterator;
      }
      if(r > signed_max)
        r -= signed_max;
      int i = r;
      return i;
    }
    else if(qi::parse (iterator, string.end (), spirit::int_[phoenix::ref (r) = arg_names::_1])
       && iterator == string.end())
    {
      return r;
    }
    else
      return boost::none;
}
#else
boost::optional<unsigned int> uint_parser (xml_string<> string); // not implemented yet
boost::optional<int> int_parser (xml_string<> string); // not implemented yet
boost::optional<int> focus_index_parser (xml_string<> string); // not implemented yet
#endif

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
