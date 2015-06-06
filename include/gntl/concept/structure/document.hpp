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

#ifndef GNTL_CONCEPT_STRUCTURE_DOCUMENT_HPP
#define GNTL_CONCEPT_STRUCTURE_DOCUMENT_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/concept/structure/descriptor.hpp>
#include <gntl/concept/structure/property.hpp>
#include <gntl/concept/parser/region/region.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/transition_enum.hpp>
#include <gntl/event_enum.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/ref.hpp>
#include <gntl/range.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/optional.hpp>

#include <boost/none.hpp>

#include <vector>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace structure {

template <typename T>
struct document_traits
{
    typedef boost::false_type is_document;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Document
{
    typedef document_traits<X> traits_type;
    BOOST_MPL_ASSERT_RELATION (traits_type::is_document::value, ==, true);
    typedef typename traits_type::descriptor_lookupable descriptor_lookupable;
    typedef typename traits_type::descriptor_type descriptor_type;
    typedef typename traits_type::region_lookupable region_lookupable;
    typedef typename traits_type::region_type region_type;
    typedef typename traits_type::event_type event_type;
    typedef typename traits_type::component_identifier component_identifier;
    typedef typename traits_type::property_name property_name;
    typedef typename traits_type::property_type property_type;
    typedef typename traits_type::body_type body_type;
    typedef typename traits_type::document_lookupable document_lookupable;
    typedef typename traits_type::causal_connector_lookupable causal_connector_lookupable;
    typedef typename traits_type::context_lookupable context_lookupable;
    typedef typename traits_type::media_lookupable media_lookupable;
    typedef typename traits_type::switch_lookupable switch_lookupable;
    typedef typename traits_type::focus_index_presentation_lookupable focus_index_presentation_lookupable;
    typedef typename traits_type::rule_lookupable rule_lookupable;
    typedef typename traits_type::document_uri_type document_uri_type;
    typedef typename traits_type::descriptor_base_type descriptor_base_type;
    typedef typename traits_type::connector_base_type connector_base_type;
    typedef typename traits_type::region_base_range region_base_range;

    BOOST_CONCEPT_ASSERT ((concept::Lookupable<descriptor_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<document_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<region_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<context_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<media_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<switch_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<causal_connector_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<focus_index_presentation_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::Lookupable<rule_lookupable>));
    BOOST_CONCEPT_ASSERT ((concept::structure::Property<property_type>));
    typedef typename boost::unwrap_reference<descriptor_type>::type descriptor_value_type;
    BOOST_CONCEPT_ASSERT ((concept::structure::Descriptor<descriptor_value_type>));
    typedef typename boost::unwrap_reference<region_type>::type region_value_type;
    BOOST_CONCEPT_ASSERT ((concept::parser::Region<region_value_type>));
    typedef typename boost::unwrap_reference<body_type>::type body_value_type;
    BOOST_CONCEPT_ASSERT ((concept::structure::Context<body_value_type>));

    typedef concept::structure::property_traits<property_type> property_traits;
    typedef typename property_traits::string_type property_string_type;
    typedef typename property_traits::integer_type property_integer_type;
    typedef typename property_traits::decimal_type property_decimal_type;

    BOOST_CONCEPT_USAGE (Document)
    {
        convertible_to<descriptor_lookupable>(traits_type::descriptor_lookup (i));
        convertible_to<region_lookupable>(traits_type::region_lookup (i));
        traits_type::register_event (i, identifier, optional_interface
                                     , transition , event);
        traits_type::register_event (i, identifier, boost::none
                                     , transition, event);
        convertible_to<std::size_t>(traits_type::pending_events (i));
        convertible_to<event_type>(traits_type::top_event (i));
        traits_type::pop_event (i);
        convertible_to<body_type>(traits_type::body(i));
        convertible_to<document_lookupable>(traits_type::document_lookup(i));
        convertible_to<bool>(traits_type::has_descriptor_base(i));
        convertible_to<bool>(traits_type::has_connector_base(i));
        convertible_to<descriptor_base_type>(traits_type::descriptor_base(i));
        convertible_to<connector_base_type>(traits_type::connector_base(i));
        convertible_to<region_base_range>(traits_type::region_base_all(i));
        convertible_to<context_lookupable>(traits_type::context_lookup(i));
        convertible_to<media_lookupable>(traits_type::media_lookup(i));
        convertible_to<rule_lookupable>(traits_type::rule_lookup(i));
        convertible_to<switch_lookupable>(traits_type::switch_lookup(i));
        convertible_to<causal_connector_lookupable>(traits_type::causal_connector_lookup(i));
        convertible_to<focus_index_presentation_lookupable>(traits_type::focus_index_presentation_lookup(i));
        // properties
        convertible_to<bool>(traits_type::has_property(i, property_name_));
        traits_type::start_set_property(i, property_name_, property_integer);
        traits_type::start_set_property(i, property_name_, property_string);
        traits_type::commit_set_property(i, property_name_);
        convertible_to<property_type>(traits_type::get_property(i, property_name_));
        convertible_to<bool>(traits_type::has_current_key_master(i));
        convertible_to<component_identifier>(traits_type::current_key_master(i));
        traits_type::set_current_key_master_from_focused_media(i);
        convertible_to<property_integer_type>(traits_type::focus_index(i));
        convertible_to<bool>(traits_type::has_focus(i));
        convertible_to<bool>(traits_type::is_focus_bound(i));
        convertible_to<component_identifier>(traits_type::focused_media(i));
        traits_type::set_focused_media(i, identifier);
        traits_type::reset_focus (i);
        convertible_to<bool>(traits_type::has_global_properties_media(i));
        convertible_to<component_identifier>(traits_type::global_properties_media(i));
        traits_type::global_properties_media(i, identifier);
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }

    gntl::transition_type transition;
    gntl::event_type event;
    X i;
    component_identifier identifier;
    property_name property_name_;
    property_type property_;
    property_string_type property_string;
    property_integer_type property_integer;
    property_decimal_type property_decimal;
    boost::optional<component_identifier> optional_interface;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
