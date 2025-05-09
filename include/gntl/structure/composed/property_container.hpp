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

#ifndef GNTL_STRUCTURE_COMPOSED_PROPERTY_CONTAINER_HPP
#define GNTL_STRUCTURE_COMPOSED_PROPERTY_CONTAINER_HPP

#include <gntl/structure/composed/property.hpp>
#include <gntl/invalid_ncl_error.hpp>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/void.hpp>
#if BOOST_VERSION >= 104000
#include <boost/spirit/home/qi.hpp>
#include <boost/phoenix/phoenix.hpp>
#endif
#include <boost/optional.hpp>

#include <set>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

namespace property_container_detail {

template <typename Property>
struct property_less
{
  typedef typename Property::string_type string_type;
  typedef bool result_type;

  result_type operator()(Property const& lhs, Property const& rhs) const
  {
    return lhs.name < rhs.name;
  }
  result_type operator()(string_type const& lhs, Property const& rhs) const
  {
    return lhs < rhs.name;
  }
  result_type operator()(Property const& lhs, string_type const& rhs) const
  {
    return lhs.name < rhs;
  }
};

}

template <typename String, typename Integer, typename Decimal
          , typename BuiltinPropertiesTraits = boost::mpl::void_>
struct property_container
{
  typedef property<String, Integer, Decimal> property_type;
  typedef property_container_detail::property_less<property_type> property_less;

  property_container()
  {}

  typedef std::set<property_type, property_less> local_properties_container;
  local_properties_container local_properties;

  typedef typename local_properties_container::iterator local_iterator;
  typedef typename BuiltinPropertiesTraits::iterator builtin_iterator;

  struct iterator : boost::iterator_facade
  <iterator, property_type, boost::forward_traversal_tag, property_type>
  {
    iterator(builtin_iterator builtin_current, builtin_iterator builtin_last
             , local_iterator local_current, local_iterator local_last)
      : builtin_current(builtin_current), builtin_last(builtin_last)
      , local_current(local_current), local_last(local_last)
    {}

    void increment()
    {
      if(builtin_current != builtin_last)
        ++builtin_current;
      else
        ++local_current;
    }

    property_type dereference() const
    {
      if(builtin_current != builtin_last)
        return *builtin_current;
      else
        return *local_current;
    }

    bool equal(iterator const& other) const
    {
      return builtin_current == other.builtin_current
        && local_current == other.local_current;
    }
    
    builtin_iterator builtin_current, builtin_last;
    local_iterator local_current, local_last;
  };

  typedef iterator const_iterator;

  template <typename T>
  iterator begin(T object) const
  {
    return iterator(BuiltinPropertiesTraits::begin(object), BuiltinPropertiesTraits::end(object)
                    , local_properties.begin(), local_properties.end());
  }
  template <typename T>
  iterator end(T object) const
  {
    return iterator(BuiltinPropertiesTraits::end(object), BuiltinPropertiesTraits::end(object)
                    , local_properties.end(), local_properties.end());
  }
  template <typename T>
  iterator find(T object, String name) const
  {
    builtin_iterator builtin_first = BuiltinPropertiesTraits::find(object, name)
      , builtin_last = BuiltinPropertiesTraits::end(object);
    local_iterator local_first = local_properties.begin()
      , local_last = local_properties.end();
    if(builtin_first == builtin_last)
    {
      std::pair<local_iterator, local_iterator>
        equal = std::equal_range(local_properties.begin(), local_properties.end()
                                 , name, property_less());
      if(equal.first != equal.second)
        local_first = equal.first;
    }
    return iterator(builtin_first, builtin_last, local_first, local_last);
  }

  template <typename T, typename V>
  void start_set_generic(T object, String name, V v)
  {
    builtin_iterator builtin = BuiltinPropertiesTraits::find(object, name);
    if(builtin != BuiltinPropertiesTraits::end(object))
      BuiltinPropertiesTraits::start_set(object, name, v);
    else
    {
      local_iterator iterator = std::lower_bound(local_properties.begin(), local_properties.end()
                                                 , name, property_less());
      if(iterator != local_properties.end())
      {
        property_type property = *iterator;
        // if(!!property.new_value)
        //   GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
        //                          , (typename error::reason<const char*>::type
        //                             ("Trying to set a property being set")));
        property.new_value = v;
        local_properties.erase(iterator);
        local_properties.insert(property);
      }
      else
      {
        property_type property(name);
        // if(!!property.new_value)
        //   GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
        //                          , (typename error::reason<const char*>::type
        //                             ("Trying to set a property being set")));
        property.new_value = v;
        local_properties.insert(property);
      }
    }
  }

  boost::optional<Integer> integer_parser(String const& value)
  {
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
#if BOOST_VERSION >= 104200
    namespace arg_names = boost::spirit::qi;
#else
    namespace arg_names = boost::spirit::arg_names;
#endif
    namespace phoenix = boost::phoenix;
    Integer r = 0;
    typedef typename boost::range_iterator<String const>::type iterator_type;
    iterator_type first = boost::begin(value), last = boost::end(value);
    if(qi::parse (first, last, spirit::int_[phoenix::ref (r) = arg_names::_1])
       && first == last)
    {
      return r;
    }
    else
      return boost::none;
  }

  boost::optional<Decimal> decimal_parser(String const& value)
  {
    namespace qi = boost::spirit::qi;
    namespace spirit = boost::spirit;
#if BOOST_VERSION >= 104200
    namespace arg_names = boost::spirit::qi;
#else
    namespace arg_names = boost::spirit::arg_names;
#endif
    namespace phoenix = boost::phoenix;
    Decimal r = 0;
    typedef typename boost::range_iterator<String const>::type iterator_type;
    iterator_type first = boost::begin(value), last = boost::end(value);
    if(qi::parse (first, last, spirit::double_[phoenix::ref (r) = arg_names::_1])
       && first == last)
    {
      return r;
    }
    else
      return boost::none;
  }

  template <typename T>
  void start_set(T object, String name, String string)
  {
    if(boost::optional<Integer> r = integer_parser(string))
    {
      this->start_set_generic(object, name, *r);
    }
    else if(boost::optional<Decimal> r = decimal_parser(string))
    {
      start_set_generic(object, name, *r);
    }
    else
      start_set_generic(object, name, string);
  }

  template <typename T>
  void start_set(T object, property_type p)
  {
    typedef concept::structure::property_traits<property_type> property_traits;
    assert(!!property_traits::has_value(p));
    if(property_traits::is_integer(p))
    {
      this->start_set_generic(object, property_traits::name(p), property_traits::integer_value(p));
    }
    else if(property_traits::is_decimal(p))
    {
      start_set_generic(object, property_traits::name(p), property_traits::decimal_value(p));
    }
    else
      start_set(object, property_traits::name(p), property_traits::value_as_string(p));
  }

  template <typename T>
  void commit_set(T object, String name)
  {
    builtin_iterator builtin = BuiltinPropertiesTraits::find(object, name);
    if(builtin != BuiltinPropertiesTraits::end(object))
      BuiltinPropertiesTraits::commit_set(object, name);
    else
    {
      local_iterator iterator = std::lower_bound(local_properties.begin(), local_properties.end()
                                                 , name, property_less());
      if(iterator != local_properties.end())
      {
        property_type property = *iterator;
        GNTL_DEBUG_LOG("property_container::commit_set setting value " << property.new_value << std::endl;);
        std::swap(property.current_value, property.new_value);
        property.new_value = boost::none;
        local_properties.erase(iterator);
        local_properties.insert(property);
      }
    }    
  }
};

template <typename String, typename Integer, typename Decimal>
struct property_container<String, Integer, Decimal, boost::mpl::void_>
{
  typedef property<String, Integer, Decimal> property_type;
  typedef property_container_detail::property_less<property_type> property_less;
  property_container() {}

  typedef std::set<property_type, property_less> properties_container;
  properties_container properties;

  typedef typename properties_container::iterator iterator;
  typedef iterator const_iterator;

  iterator begin() const { return properties.begin(); }
  iterator end() const { return properties.end(); }
  iterator find(String name) const
  {
    std::pair<iterator, iterator> equal = std::equal_range(properties.begin(), properties.end()
                                                           , name, property_less());
    if(equal.first != equal.second)
      return equal.first;
    else
      return properties.end();
  }
  template <typename Value>
  void start_set(String name, Value v)
  {
    iterator i = find(name);
    if(i != properties.end())
    {
      property_type property = *i;
      property.new_value = v;
      properties.erase(i);
      properties.insert(property);
    }
    else
    {
      property_type property(name);
      property.new_value = v;
      properties.insert(property);
    }
  }
  void commit_set(String name)
  {
    iterator i = find(name);
    if(i != properties.end())
    {
      property_type property = *i;
      property.current_value = property.new_value;
      properties.erase(i);
      properties.insert(property);
    }
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
