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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_CALCULATE_DIMENSIONS_HPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_CALCULATE_DIMENSIONS_HPP

#include <gntl/concept/parser/property/property.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/range.hpp>
#include <gntl/parser/libxml2/dom/region.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Name>
struct property_name_predicate_struct
{
    property_name_predicate_struct (Name id)
        : id (id) {}

    typedef bool result_type;

    template <typename Property>
    result_type operator()(Property d) const
    {
        typedef typename boost::unwrap_reference<Property>::type property_type;
        typedef concept::parser::property_traits<property_type> traits;
        return traits::name (d) == id;
    }

    Name id;
};

struct property_coordinates
{
  typedef boost::optional<gntl::parser::libxml2::dom::coordinate> coordinate;
  typedef std::map<std::string, coordinate> coordinate_map;

  property_coordinates() {}

  coordinate_map coordinates;
};

inline
void set_coordenate(std::size_t& out_var, std::string const& coord_name, property_coordinates const& properties, std::size_t parent_size, std::size_t result_increment = 0, boost::optional<std::size_t> oposite_coord_relative = boost::none)
{
  property_coordinates::coordinate_map::const_iterator it = properties.coordinates.find(coord_name);
  if(it == properties.coordinates.end() || !it->second) {
    return;
  }

  std::size_t coord_abs = calculate_dimensions_detail::absolute(*(it->second), parent_size);
  if(!oposite_coord_relative)
  {
    out_var = coord_abs + result_increment;
  }
  else
  {
    out_var = parent_size - coord_abs - *oposite_coord_relative + result_increment;
  }
}

template <typename Name>
property_name_predicate_struct<Name> 
property_name_predicate (Name id)
{
    return property_name_predicate_struct<Name>(id);
}

template <typename Media, typename Document, typename Descriptor>
media::dimensions calculate_dimensions_from_media_descriptor(Media media
                                                             , Document document
                                                             , Descriptor descriptor
                                                             , media::dimensions full)
{
    typedef typename unwrap_parameter<Media>::type media_type;
    typedef typename unwrap_parameter<Document>::type document_type;
    typedef concept::structure::document_traits<document_type> document_traits;
    typedef typename unwrap_parameter<Descriptor>::type descriptor_type;
    typedef typename document_traits::region_type region_type;

    GNTL_CONCEPT_ASSERT((concept::structure::Descriptor<descriptor_type>));

    bool has_property_dim = false;
    property_coordinates c;
    {
      typedef concept::structure::media_traits<media_type> media_traits;
      typedef typename media_traits::property_range property_range;
      property_range properties = concept::property_all(media);
      for(typename boost::range_iterator<property_range>::type
            first = boost::begin(properties)
            , last = boost::end(properties); first != last; ++first)
      {
        typedef typename boost::range_value<property_range>::type property_type;
        typedef concept::structure::property_traits<property_type> property_traits;
        std::string name = property_traits::name(*first);

        using gntl::parser::libxml2::dom::coordinate_parser;

        if(name == "left"  || name == "top"    ||
           name == "width" || name == "height" ||
           name == "right" || name == "bottom" )
        {
          std::string value = property_traits::value_as_string(*first);
          c.coordinates[name] = coordinate_parser((::xmlChar const*)(value.c_str()));
          has_property_dim = true;
        }
      }

      if(has_property_dim)
      {
        if(c.coordinates["width"] && c.coordinates["right"])
        {
          c.coordinates["right"] = boost::none;
        }

        if(c.coordinates["height"] && c.coordinates["bottom"])
        {
          c.coordinates["bottom"] = boost::none;
        }
      }
    }

//     {
//       // property has precedence over everything
//       typedef concept::parser::has_property_traits<media_type>
//         has_property_traits;
//       typedef typename has_property_traits::property_range
//         property_range_type;
//       property_range_type
//         property_range = has_property_traits::property (media);
//       typedef typename boost::range_iterator<property_range_type>::type
//         property_iterator_type;
//       property_iterator_type
//         property_iterator =
// #if BOOST_VERSION > 104200
//         boost::range::find_if (property_range
//                                , property_name_predicate ("region"));
// #else
//         std::find_if(boost::begin(property_range), boost::end(property_range)
//                      , property_name_predicate("region"));
// #endif

//       typedef typename boost::range_value<property_range_type>::type
//         property_type;
//       if(property_iterator != boost::end (property_range))
//       {
//         typedef concept::parser::property_traits
//           <property_type> property_traits;
//         typename property_traits::value_type region_name
//           = property_traits::value (*property_iterator);
//         GNTL_DEBUG_LOG("region name: " << region_name << std::endl)
        
//         typedef typename document_traits::region_lookupable
//           region_lookupable;
//         region_range_type
//           region_range = document_traits::region_range (document);
        
//         boost::optional<dimensions>
//           d = calculate_dimensions_from_region_name(region_range, region_name
//                                                     , full);
//         if(d)
//           return *d;
//       }
//     }
            
    // descriptorparam has precedence over descriptor attributes
    // if(descriptor)
    // {
//       {
//         typedef concept::parser::has_descriptor_param_traits
//           <descriptor_type>
//           has_descriptor_param_traits;
//         typedef typename has_descriptor_param_traits
//           ::descriptor_param_range
//           descriptor_param_range_type;
//         descriptor_param_range_type
//           descriptor_param_range = has_descriptor_param_traits::descriptor_param
//           (*descriptor);
//         typedef typename boost::range_iterator<descriptor_param_range_type>::type
//           descriptor_param_iterator_type;
//         descriptor_param_iterator_type
//           descriptor_param_iterator =
// #if BOOST_VERSION > 104200
//           boost::range::find_if (descriptor_param_range
//                                  , descriptor_param_name_predicate ("region"));
// #else
//           std::find_if (boost::begin(descriptor_param_range), boost::end(descriptor_param_range)
//                         , descriptor_param_name_predicate ("region"));
// #endif
//         typedef typename boost::range_value<descriptor_param_range_type>::type
//           descriptor_param_type;
//         if(descriptor_param_iterator != boost::end (descriptor_param_range))
//         {
//           typedef concept::parser::descriptor_param_traits
//             <descriptor_param_type> descriptor_param_traits;
//           typename descriptor_param_traits::value_type region_name
//             = descriptor_param_traits::value (*descriptor_param_iterator);
//           GTNL_DEBUG_LOG("region name: " << region_name << std::endl)
        
//           typedef typename document_traits::region_range_type
//             region_range_type;
//           region_range_type
//             region_range = document_traits::region_range (document);
        
//           boost::optional<dimensions>
//             d = calculate_dimensions_from_region_name(region_range, region_name
//                                                       , full);
//           if(d) return *d;
//         }
//       }

      boost::optional<dimensions> d_out;
      dimensions parent = full;

      typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
      // descriptor attributes has the least precedence
      if(descriptor_traits::has_region(descriptor))
      {
        typedef typename descriptor_traits::document_uri_type document_uri;

        document_uri region_document_uri = descriptor_traits::region_document_uri(descriptor);

        // find document
        typedef typename document_traits::document_lookupable document_lookupable;
        document_lookupable documents = document_traits::document_lookup(document);
        typedef concept::lookupable_traits<document_lookupable> lookupable_traits;
        typedef typename lookupable_traits::result_type result_type;

        GNTL_DEBUG_LOG("searching document " << region_document_uri << std::endl)
        result_type lookup_result = lookupable_traits::lookup(documents, region_document_uri);
        if(lookup_result != lookupable_traits::not_found(documents))
        {
          GNTL_DEBUG_LOG("found document" << std::endl)

          typedef typename document_traits::region_lookupable region_lookupable;
          region_lookupable regions = document_traits::region_lookup (*lookup_result);
      
          typename descriptor_traits::region_type region_name = descriptor_traits::region(descriptor);
          d_out = calculate_dimensions_from_region_name(regions, region_name, full, has_property_dim ? &parent : 0);
        }
      }
    // }

    // TODO: Relaxed dimension calculation (a bit more than lifia).
    //       Is it too much important to mantain the dimension inside the parent region?
    // TODO: "property right" overrides "region width". Is it OK? (lifia is different)
    if(has_property_dim)
    {
      if(!d_out)
        d_out = parent;

      // Top and Left (if present) should be set first
      set_coordenate(d_out->x, "left", c, parent.width, parent.x);
      set_coordenate(d_out->y, "top", c, parent.height, parent.y);

      // Now we can set the others (if present)
      set_coordenate(d_out->width, "right", c, parent.width, 0, d_out->x - parent.x);
      set_coordenate(d_out->height, "bottom", c, parent.height, 0, d_out->y - parent.y);

      set_coordenate(d_out->width, "width", c, parent.width);
      set_coordenate(d_out->height, "height", c, parent.height);
    }

    if(d_out)
      return *d_out;

    return full;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
