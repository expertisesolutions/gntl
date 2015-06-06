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

#ifndef GNTL_ALGORITHM_STRUCTURE_PROPERTY_CONTAINER_HPP
#define GNTL_ALGORITHM_STRUCTURE_PROPERTY_CONTAINER_HPP

#include <gntl/log/log.hpp>

#include <gntl/concept/structure/media.hpp>
#include <gntl/structure/composed/property_container.hpp>
#include <gntl/parameter.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace property_container {

template <typename String, typename Integer, typename Decimal
          , typename BuiltinPropertiesTraits, typename Object, typename Media>
void initialize_from_structure_media(gntl::structure::composed::property_container
                                     <String, Integer, Decimal, BuiltinPropertiesTraits>& container
                                     , Object object, Media media)
{
  GNTL_DEBUG_LOG("initialize_from_structure_media builtin" << std::endl)
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename concept::structure::media_traits<media_type> media_traits;

  typedef typename media_traits::property_range property_range;

  property_range properties = concept::property_all(media);
  for(typename boost::range_iterator<property_range>::type first = boost::begin(properties)
        , last = boost::end(properties); first != last; ++first)
  {
    typedef typename boost::range_value<property_range>::type property_value_type;
    typedef typename unwrap_parameter<property_value_type>::type property_type;
    typedef concept::structure::property_traits<property_type> property_traits;
    GNTL_DEBUG_LOG("Should set property " << property_traits::name(*first) << std::endl)

    if(property_traits::has_value(*first))
    {
      container.start_set(object, *first);
      container.commit_set(object, property_traits::name(*first));
    }
  }
}

template <typename String, typename Integer, typename Decimal, typename Media>
void initialize_from_structure_media(gntl::structure::composed::property_container
                                     <String, Integer, Decimal, boost::mpl::void_>& container, Media media)
{
  GNTL_DEBUG_LOG("initialize_from_structure_media non-builtin" << std::endl)
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename concept::structure::media_traits<media_type> media_traits;

  typedef typename media_traits::property_range property_range;

  property_range properties = concept::property_all(media);
  for(typename boost::range_iterator<property_range>::type first = boost::begin(properties)
        , last = boost::end(properties); first != last; ++first)
  {
    typedef typename boost::range_value<property_range>::type property_value_type;
    typedef typename unwrap_parameter<property_value_type>::type property_type;
    typedef concept::structure::property_traits<property_type> property_traits;
    GNTL_DEBUG_LOG("Should set property (void_) " << property_traits::name(*first) << std::endl)

    if(property_traits::has_value(*first))
    {
      container.start_set(*first);
      container.commit_set(property_traits::name(*first));
    }
  }
}

template <typename String, typename Integer, typename Decimal, typename BuiltinPropertiesTraits
          , typename Object, typename Media>
void initialize_from_parser_media(gntl::structure::composed::property_container
                                     <String, Integer, Decimal, boost::mpl::void_>& container
                                  , Object object, Media media)
{
  GNTL_DEBUG_LOG("initialize_from_parser_media builtin" << std::endl)
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename concept::parser::media_traits<media_type> media_traits;

  typedef typename media_traits::property_range property_range;

  property_range properties = concept::property_all(media);
  for(typename boost::range_iterator<property_range>::type first = boost::begin(properties)
        , last = boost::end(properties); first != last; ++first)
  {
    typedef typename boost::range_value<property_range>::type property_value_type;
    typedef typename unwrap_parameter<property_value_type>::type property_type;
    typedef concept::parser::property_traits<property_type> property_traits;
    GNTL_DEBUG_LOG("Should set property " << property_traits::name(*first) << std::endl)
    String string;
    if(property_traits::has_value(*first))
    {
      string = property_traits::value(*first);
      container.start_set(object, property_traits::name(*first), string);
      container.commit_set(object, property_traits::name(*first));
    }
  }
}

template <typename String, typename Integer, typename Decimal, typename Media>
void initialize_from_parser_media(gntl::structure::composed::property_container
                                     <String, Integer, Decimal, boost::mpl::void_>& container, Media media)
{
  GNTL_DEBUG_LOG("initialize_from_parser_media non-builtin" << std::endl)
  typedef typename unwrap_parameter<Media>::type media_type;
  typedef typename concept::parser::media_traits<media_type> media_traits;

  typedef typename media_traits::property_range property_range;

  property_range properties = media_traits::property_all(media);
  for(typename boost::range_iterator<property_range>::type first = boost::begin(properties)
        , last = boost::end(properties); first != last; ++first)
  {
    typedef typename boost::range_value<property_range>::type property_value_type;
    typedef typename unwrap_parameter<property_value_type>::type property_type;
    typedef concept::parser::property_traits<property_type> property_traits;
    GNTL_DEBUG_LOG("Should set property " << property_traits::name(*first) << std::endl)
    String string;
    if(property_traits::has_value(*first))
    {
      string = property_traits::value(*first);
      container.start_set(property_traits::name(*first), string);
      container.commit_set(property_traits::name(*first));
    }
  }
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
