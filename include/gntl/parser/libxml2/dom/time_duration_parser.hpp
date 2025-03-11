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

#ifndef GNTL_PARSER_LIBXML2_DOM_TIME_DURATION_PARSER_HPP
#define GNTL_PARSER_LIBXML2_DOM_TIME_DURATION_PARSER_HPP

#include <gntl/parser/libxml2/dom/xml_string.hpp>

#include <boost/version.hpp>
#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#include <boost/spirit/home/qi/numeric/uint.hpp>
#endif

#ifndef __SYMBIAN32__
#include <boost/date_time/posix_time/posix_time.hpp>
#endif
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

namespace spirit {
#if BOOST_VERSION >= 104200
    namespace arg_names = boost::spirit::qi;
#else
    namespace arg_names = boost::spirit::arg_names;
#endif
}

#if !defined(__SYMBIAN32__) && BOOST_VERSION >= 104000
inline boost::posix_time::time_duration time_duration_parser (xml_string<> string)
{
    namespace spirit = boost::spirit;
    namespace qi = boost::spirit::qi;
    namespace arg_names = dom::spirit::arg_names;
    namespace tag = boost::spirit::tag;
    namespace phoenix = boost::phoenix;
    xml_string<>::const_iterator iterator = string.begin ();
    float time = 0.0f;
    unsigned int hours = 0, minutes = 0, seconds = 0, fraction = 0;
    if(qi::parse (iterator, string.end(), spirit::uint_[phoenix::ref(hours) = arg_names::_1]
                  >> ':' >> spirit::uint_[phoenix::ref(minutes) = arg_names::_1]
                  >> ':' >> spirit::uint_[phoenix::ref(seconds) = arg_names::_1]
                  >> '.' >> spirit::uint_[phoenix::ref(fraction) = arg_names::_1]))
    {
      return boost::posix_time::time_duration(hours, minutes, seconds);
    }
    else
    {
      iterator = string.begin();
      if(qi::parse (iterator, string.end (), spirit::float_[phoenix::ref (time) = arg_names::_1]))
      {
        std::size_t integer_part = std::floor (time);
        if(iterator == string.end () || *iterator == 's')
            return boost::posix_time::seconds (integer_part);
        else if(*iterator == 'm')
            return boost::posix_time::minutes (integer_part);
        else if(*iterator == 'h')
            return boost::posix_time::hours (integer_part);
      }
    }
    return boost::posix_time::time_duration ();
}
#else
boost::posix_time::time_duration time_duration_parser (xml_string<> string); // not implemented yet
#endif

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
