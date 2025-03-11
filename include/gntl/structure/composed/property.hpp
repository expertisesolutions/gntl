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

#ifndef GNTL_STRUCTURE_COMPOSED_PROPERTY_HPP
#define GNTL_STRUCTURE_COMPOSED_PROPERTY_HPP

#include <gntl/concept/parser/property/property.hpp>

#include <boost/optional.hpp>
#include <boost/variant.hpp>

#include <sstream>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename String, typename Integer, typename Decimal>
struct property
{
  typedef boost::variant<String, Integer, Decimal> unique_variant_type;
  typedef boost::variant<unique_variant_type, std::vector<unique_variant_type> > composite_variant_type;

  property(String const& name, unique_variant_type const& value)
    : name(name), current_value(value) {}
  property(String const& name)
    : name(name) {}

  typedef String string_type;
  typedef Integer integer_type;
  typedef Decimal decimal_type;

  String name;
  boost::optional<unique_variant_type> current_value, new_value;
};

} }

namespace concept { namespace structure {


template <typename String, typename Integer, typename Decimal>
struct property_traits<gntl::structure::composed::property<String, Integer, Decimal> >
{
  typedef boost::mpl::true_ is_property;
  typedef typename gntl::structure::composed::property<String, Integer, Decimal> property_type;
  typedef String name_type;
  typedef String string_type;
  typedef Integer integer_type;
  typedef Decimal decimal_type;

  static name_type name(property_type const& p)
  {
    return p.name;
  }

  static bool has_value(property_type const& p)
  {
    return !!p.current_value;
  }

  struct get_stringified
  {
    typedef String result_type;
    result_type operator()(String const& s) const
    {
      return s;
    }
    result_type operator()(Integer i) const
    {
      std::stringstream s;
      s << i;
      return s.str();
    }
    result_type operator()(Decimal d) const
    {
      std::stringstream s;
      s << d;
      return s.str();
    }
  };

  static string_type value_as_string(property_type const& p)
  {
    if(p.current_value)
      return boost::apply_visitor(get_stringified(), *p.current_value);
    else
      return String();
  }

  static integer_type integer_value(property_type const& p)
  {
    return boost::get<integer_type>(*p.current_value);
  }
  static decimal_type decimal_value(property_type const& p)
  {
    return boost::get<decimal_type>(*p.current_value);
  }

  static bool is_integer(property_type const& p)
  {
    return p.current_value && boost::get<integer_type>(&*p.current_value);
  }
  static bool is_string(property_type const& p)
  {
    return !p.current_value || boost::get<string_type>(&*p.current_value);
  }
  static bool is_decimal(property_type const& p)
  {
    return p.current_value && boost::get<decimal_type>(&*p.current_value);
  }
  static bool is_composite(property_type const& p)
  {
    return false;
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
