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

#ifndef GNTL_PARSER_LIBXML2_DOM_XML_STRING_HPP
#define GNTL_PARSER_LIBXML2_DOM_XML_STRING_HPP

#include <string>
#include <algorithm>
#include <iosfwd>
#include <cassert>
#include <cstring>

#ifdef __SYMBIAN32__
#include <libxml2/libxml2_parser.h>
#else
#include <libxml/parser.h>
#endif

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace parser { namespace libxml2 { namespace dom {

template <typename CharTraits
#if defined(__GNUC__) && (__GNUC__ < 3 || (__GNUC__ == 3 && __GNUC_MINOR__ < 4))
 = std::char_traits<char>
#else
 = std::char_traits< ::xmlChar>
#endif
  >
struct xml_string
{
    typedef CharTraits char_traits;

    xml_string () : string (0) {}
    xml_string (::xmlChar const* string)
        : string (string) {}

    bool equal (::xmlChar const* other) const
    {
#if defined(__GNUC__) && (__GNUC__ < 3 || (__GNUC__ == 3 && __GNUC_MINOR__ < 4))
        if(!string || !other)
            return !string ? !other || *other == 0 : *string == 0;

        const char* casted_string
          = static_cast<const char*>(static_cast<const void*>(string));
        const char* casted_other
          = static_cast<const char*>(static_cast<const void*>(other));

        std::size_t size = char_traits::length (casted_string);
        if(size != char_traits::length (casted_other))
          return false;

        return char_traits::compare (casted_string, casted_other, size) == 0;
#else
        if(!string || !other)
            return !string ? !other || *other == 0 : *string == 0;

        std::size_t size = char_traits::length (string);
        if(size != char_traits::length (other))
          return false;

        return char_traits::compare (string, other, size) == 0;
#endif
    }

    bool less (::xmlChar const* other) const
    {
#if defined(__GNUC__) && (__GNUC__ < 3 || (__GNUC__ == 3 && __GNUC_MINOR__ < 4))
        if(!string || !other)
            return !string ? other && *other != 0 : *string == 0;

        const char* casted_string
          = static_cast<const char*>(static_cast<const void*>(string));
        const char* casted_other
          = static_cast<const char*>(static_cast<const void*>(other));

        std::size_t this_size = char_traits::length (casted_string);
        std::size_t other_size = char_traits::length (casted_other);
        std::size_t smaller_size = (std::min)(this_size, other_size);

        int c = char_traits::compare (casted_string, casted_other, smaller_size);
        return c < 0 || (c == 0 && this_size < other_size);
#else
        if(!string || !other)
            return !string ? other && *other != 0 : *string == 0;

        std::size_t this_size = char_traits::length (string);
        std::size_t other_size = char_traits::length (other);
        std::size_t smaller_size = (std::min)(this_size, other_size);

        int c = char_traits::compare (string, other, smaller_size);
        return c < 0 || (c == 0 && this_size < other_size);
#endif
    }

    typedef ::xmlChar const* iterator;
    typedef ::xmlChar const* const_iterator;

    ::xmlChar const* begin () const
    {
        return string;
    }

    ::xmlChar const* end () const
    {
        return string? string + ::xmlStrlen (string) : string;
    }

    friend inline bool operator==(xml_string<CharTraits> const& lhs, const char* rhs)
    {
        assert (rhs != 0);
        return lhs.equal (static_cast< ::xmlChar const*>(static_cast<void const*>(rhs)));
    }

    friend inline bool operator==(xml_string<CharTraits> const& lhs, xml_string<CharTraits> const& rhs)
    {
        return lhs.equal (rhs.string);
    }

    friend inline bool operator==(const char* lhs, xml_string<CharTraits> const& rhs)
    {
        assert (lhs != 0);
        return rhs.equal (static_cast< ::xmlChar const*>(static_cast<void const*>(lhs)));
    }

    friend inline bool operator==(xml_string<CharTraits> const& lhs, std::string const& rhs)
    {
        return lhs.equal (static_cast< ::xmlChar const*>(static_cast<void const*>(rhs.c_str ())));
    }

    friend inline bool operator==(std::string const& lhs, xml_string<CharTraits> const& rhs)
    {
        return rhs.equal (static_cast< ::xmlChar const*>(static_cast<void const*>(lhs.c_str ())));
    }

    friend inline bool operator<(xml_string<CharTraits> const& lhs, xml_string<CharTraits> const& rhs)
    {
      return rhs.less (lhs.string);
    }

    friend inline std::ostream& operator<<(std::ostream& s, xml_string<CharTraits> const& rhs)
    {
      if(rhs.string)
        return s << rhs.string;
      else
        return s;
    }

    char const* c_str () const
    {
        if(string)
            return static_cast<char const*>(static_cast<void const*>(string));
        else 
            return "";
    }

    operator std::string() const
    {
      if(string)
        return std::string(static_cast<char const*>(static_cast<void const*>(string)));
      else
        return std::string();
    }

    bool empty() const
    {
      return !string || std::strlen(static_cast<char const*>(static_cast<void const*>(string))) == 0;
    }

    std::size_t size() const
    {
      return string?std::strlen(static_cast<char const*>(static_cast<void const*>(string))):0u;
    }
private:
    ::xmlChar const* string;
};


inline bool operator!=(xml_string<> const& lhs, const char* rhs)
{
    return !(lhs == rhs); 
}

inline bool operator!=(const char* lhs, xml_string<>const& rhs)
{
    return !(lhs == rhs); 
}

inline bool operator!=(xml_string<> const& lhs, xml_string<> const& rhs)
{
    return !(lhs == rhs); 
}

inline bool operator!=(xml_string<> const& lhs, std::string const& rhs)
{
    return !(lhs == rhs); 
}

inline bool operator!=(std::string const& lhs, xml_string<> const& rhs)
{
    return !(lhs == rhs); 
}

} } } }


#include <gntl/detail/pop_options.hpp>

#endif
