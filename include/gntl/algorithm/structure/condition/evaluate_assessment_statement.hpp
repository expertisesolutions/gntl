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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONDITION_EVALUATE_ASSESSMENT_STATEMENT_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONDITION_EVALUATE_ASSESSMENT_STATEMENT_HPP

#include <gntl/concept/structure/condition/bound_attribute_assessment.hpp>
#include <gntl/concept/structure/condition/bound_assessment_statement.hpp>
#include <gntl/algorithm/structure/component/tag.hpp>
#include <gntl/ref.hpp>
#include <gntl/parameter.hpp>

#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace condition {

namespace assessment_detail {

struct evaluate_attribute
{
  typedef void result_type;
  template <typename Media, typename AttributeAssessment, typename Value>
  result_type operator()(Media m, AttributeAssessment attribute
                         , Value& value
                         , typename boost::enable_if
                           <boost::is_convertible
                            <
                              typename structure::component::tag
                              <typename unwrap_parameter<Media>::type>::type
                              , structure::component::media_tag
                            >
                           , void*>::type = 0) const
  {
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef typename boost::unwrap_reference<AttributeAssessment>::type
      attribute_assessment_type;
    typedef concept::structure::media_traits<media_type>
      media_traits;
    typedef gntl::concept::structure::bound_attribute_assessment_traits
      <attribute_assessment_type> attribute_assessment_traits;
    GNTL_DEBUG_LOG("Found assessment media " << concept::identifier(m)
                   << std::endl)
    if(attribute_assessment_traits::has_interface (attribute))
    {
      typedef typename attribute_assessment_traits::interface_type interface_type;
      interface_type interface_ = attribute_assessment_traits::interface_ (attribute);
      GNTL_DEBUG_LOG("has interface " << interface_ << std::endl)

      if(concept::has_property(m, interface_))
      {
        value = media_traits::property(m, interface_);
      }      
      else
        GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                               , (typename error::reason<const char*>::type
                                  ("Trying to assess a property that doesn't exist"))
                                 (typename error::property_name<interface_type>::type(interface_))
                                 (typename error::component_identifier
                                  <typename media_traits::identifier_type>::type
                                  (concept::identifier(m))));
    }
    else
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Attribute assessment bound to a bind without an interface")
                                (typename error::component_identifier
                                 <typename media_traits::identifier_type>::type
                                 (concept::identifier(m)))));
  }
  template <typename Component, typename AttributeAssessment, typename Value>
  result_type operator()(Component c, AttributeAssessment attribute
                         , Value& value
                         , typename boost::disable_if
                         <boost::is_convertible
                         <typename structure::component::tag
                             <typename unwrap_parameter<Component>::type
                             >::type
                            , structure::component::media_tag
                           >
                         , void*>::type = 0) const
  {
    // TODO:
  }
};

}

template <typename AssessmentStatement, typename Document, typename Body>
bool evaluate_assessment_statement (AssessmentStatement assessment
                                    , Document document, Body body)
{
  typedef typename unwrap_parameter<AssessmentStatement>::type assessment_statement_type;
  typedef typename unwrap_parameter<Document>::type document_type;
  typedef typename unwrap_parameter<Body>::type body_type;
  typedef gntl::concept::structure::document_traits
    <document_type> structure_document_traits;
  GNTL_CONCEPT_ASSERT((gntl::concept::structure::BoundAssessmentStatement<assessment_statement_type>));
  typedef gntl::concept::structure::bound_assessment_statement_traits
    <assessment_statement_type> assessment_statement_traits;

  typedef typename assessment_statement_traits::attribute_assessment_type
    attribute_assessment_type;
  attribute_assessment_type first = assessment_statement_traits::first(assessment);
  typedef gntl::concept::structure::bound_attribute_assessment_traits
    <attribute_assessment_type> attribute_assessment_traits;
  typedef typename attribute_assessment_traits::component_type component_type;

  component_type first_component = attribute_assessment_traits::component(first);

  typedef typename assessment_statement_traits::value_assessment_type
    value_assessment_type;
  typedef concept::parser::connector_value_assessment_traits
    <value_assessment_type> value_assessment_traits;

  typedef concept::structure::context_traits<body_type> context_traits;
  typedef typename context_traits::media_const_range media_range;
  typedef typename boost::range_value<media_range>::type media_value_type;
  typedef typename unwrap_parameter<media_value_type>::type media_type;
  typedef concept::structure::media_traits<media_type> media_traits;
  typedef typename media_traits::string_type string_type;
  
  string_type first_value;

  typedef typename structure_document_traits::media_lookupable media_lookupable;
  media_lookupable lookupable = structure_document_traits::media_lookup(document);
  typedef concept::lookupable_traits<media_lookupable> lookupable_traits;
  typedef typename lookupable_traits::result_type lookupable_result;

  lookupable_result r = lookupable_traits::lookup(lookupable, first_component);

  typedef typename structure_document_traits::property_type property_type;
  typedef concept::structure::property_traits<property_type> property_traits;

  if(r != lookupable_traits::not_found(lookupable))
  {
    typedef gntl::concept::structure::bound_attribute_assessment_traits
      <attribute_assessment_type> attribute_assessment_traits;
    GNTL_DEBUG_LOG("Found assessment media " << concept::identifier(*r)
                   << std::endl)
    if(attribute_assessment_traits::has_interface (first))
    {
      typedef typename attribute_assessment_traits::interface_type interface_type;
      interface_type interface_ = attribute_assessment_traits::interface_ (first);
      GNTL_DEBUG_LOG("has interface " << interface_ << std::endl)

        if(concept::type(*r) == "application/x-ginga-settings")
        {
          if(structure_document_traits::has_property(document, interface_))
          {
            first_value = 
              property_traits::value_as_string
              (structure_document_traits::get_property(document, interface_));
          }
          else
            GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                   , (typename error::reason<const char*>::type
                                      ("Trying to assess a property in application/x-ginga-settings"
                                       " that doesn't exist"))
                                     (typename error::property_name<interface_type>::type
                                      (interface_))
                                     (typename error::component_identifier
                                      <typename media_traits::identifier_type>::type
                                      (concept::identifier(*r))));
        }
        else if(concept::has_property(*r, interface_))
        {
          first_value = property_traits::value_as_string
            (concept::get_property(*r, interface_));
        }      
        else
          GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                 , (typename error::reason<const char*>::type
                                    ("Trying to assess a property that doesn't exist"))
                                   (typename error::property_name<interface_type>::type(interface_))
                                   (typename error::component_identifier
                                    <typename media_traits::identifier_type>::type
                                    (concept::identifier(*r))));
    }
    else
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Attribute assessment bound to a bind without an interface"))
                               (typename error::component_identifier
                                <typename media_traits::identifier_type>::type
                                (concept::identifier(*r))));
  }  
  else
    GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                           , (typename error::reason<const char*>::type
                              ("Couldn't find component when trying to execute a assessmentStatement"))
                             (typename error::component_identifier<component_type>::type
                              (first_component)));

  GNTL_DEBUG_LOG("Value of first assessment " << first_value << std::endl)

  if(assessment_statement_traits::template is_second<value_assessment_type>(assessment))
  {
    GNTL_DEBUG_LOG("second is value assessment" << std::endl)
    value_assessment_type value_assessment
      = assessment_statement_traits::template second<value_assessment_type>(assessment);
    GNTL_DEBUG_LOG("first: " << first_value
              << " second: "  << value_assessment_traits::value(value_assessment)
                   << std::endl)
    return first_value == value_assessment_traits::value(value_assessment);
  }
  else
  {
    GNTL_DEBUG_LOG("other attribute" << std::endl)
    attribute_assessment_type second = assessment_statement_traits::template second
      <attribute_assessment_type>(assessment);

    component_type second_component = attribute_assessment_traits::component(second);
    string_type second_value;

    lookupable_result r = lookupable_traits::lookup(lookupable, second_component);

    if(r != lookupable_traits::not_found(lookupable))
    {
      typedef gntl::concept::structure::bound_attribute_assessment_traits
        <attribute_assessment_type> attribute_assessment_traits;
      GNTL_DEBUG_LOG("Found assessment media " << concept::identifier(*r)
                     << std::endl)
      if(attribute_assessment_traits::has_interface (second))
      {
        typedef typename attribute_assessment_traits::interface_type interface_type;
        interface_type interface_ = attribute_assessment_traits::interface_ (second);
        GNTL_DEBUG_LOG("has interface " << interface_ << std::endl)
        
        if(concept::type(*r) == "application/x-ginga-settings")
        {
          if(structure_document_traits::has_property(document, interface_))
          {
            second_value = 
              property_traits::value_as_string(structure_document_traits::get_property(document, interface_));
          }
          else
            GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                   , (typename error::reason<const char*>::type
                                      ("Trying to assess a property in application/x-ginga-settings"
                                       " that doesn't exist"))
                                     (typename error::property_name<interface_type>::type
                                      (interface_))
                                     (typename error::component_identifier
                                      <typename media_traits::identifier_type>::type
                                      (concept::identifier(*r))));
        }
        else if(concept::has_property(*r, interface_))
        {
          second_value = property_traits::value_as_string(concept::get_property(*r, interface_));
        }      
        else
          GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                 , (typename error::reason<const char*>::type
                                    ("Trying to assess a property that doesn't exist"))
                                   (typename error::property_name<interface_type>::type(interface_))
                                   (typename error::component_identifier
                                    <typename media_traits::identifier_type>::type
                                    (concept::identifier(*r))));
      }
      else
        GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                               , (typename error::reason<const char*>::type
                                  ("Attribute assessment bound to a bind without an interface"))
                                 (typename error::component_identifier
                                  <typename media_traits::identifier_type>::type
                                  (concept::identifier(*r))));
    }  
    else
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Couldn't find component when trying to execute a assessmentStatement"))
                               (typename error::component_identifier<component_type>::type
                                (second_component)));

    return first_value == second_value;
  }
}

struct evaluate_assessment_statement_functor
{
  typedef bool result_type;
  template <typename AssessmentStatement, typename Document, typename Body>
  result_type operator()(AssessmentStatement a, Document d, Body b) const
  {
    return condition::evaluate_assessment_statement(a,d,b);
  }
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
