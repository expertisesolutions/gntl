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

#ifndef GNTL_STRUCTURE_COMPOSED_CONDITION_COMPOUND_CONDITION_EXPRESSION_HPP
#define GNTL_STRUCTURE_COMPOSED_CONDITION_COMPOUND_CONDITION_EXPRESSION_HPP

#include <gntl/structure/composed/condition/compound_condition_fwd.hpp>
#include <gntl/structure/composed/condition/bounded_simple_condition.hpp>
#include <gntl/structure/composed/condition/bound_assessment_statement.hpp>
#include <gntl/structure/composed/condition/compound_statement.hpp>
#include <gntl/structure/composed/detail/role_predicate.hpp>
#include <gntl/concept/structure/condition/condition_expression.hpp>
#include <gntl/concept/parser/connector/connector_assessment_statement.hpp>

#include <gntl/algorithm/parser/link.hpp>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename LinkParser, typename ConditionExpressionParser>
struct compound_condition_expression
{
  typedef typename boost::unwrap_reference<LinkParser>::type link_type;
  typedef concept::parser::link_traits<link_type> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_value_type;
  typedef typename boost::unwrap_reference<bind_value_type>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;
  compound_condition_expression(LinkParser link
                                , ConditionExpressionParser condition
                                , std::map<role_type, bool>* role_conditions)
    : link(link), condition(condition), role_conditions(role_conditions) {}

  LinkParser link;
  ConditionExpressionParser condition;
  std::map<role_type, bool>* role_conditions;
};

namespace compound_expression_detail {

template <typename T, typename BindRange>
struct transform_to_simple_condition
{
  typedef typename boost::range_iterator<BindRange>::type bind_iterator;
  typedef concept::parser::connector_simple_condition_traits
    <T> simple_condition_traits;
  typedef typename simple_condition_traits::role_type
    role_type;
  typedef gntl::structure::composed::composed_detail::role_predicate
    <role_type> role_predicate;
  typedef boost::filter_iterator<role_predicate
                                 , bind_iterator>
    role_filtered_iterator;
  typedef boost::iterator_range<role_filtered_iterator>
    role_filtered_range;

  typedef bounded_simple_condition<role_filtered_range, T, role_type> type;
};

template <typename T, typename BindRange, typename LinkParser, typename Bind>
struct transform_to_structure_condition
{
  GNTL_CONCEPT_ASSERT((concept::parser::ConnectorCondition<T>));
  typedef concept::parser::connector_condition_traits
  <T> condition_traits;
  typedef typename
    boost::mpl::eval_if
    <
      boost::is_convertible
      <typename condition_traits::category_tag
       , concept::parser::simple_condition_tag>
      , transform_to_simple_condition<T, BindRange>
      , boost::mpl::if_
        <
          boost::is_convertible
          <typename condition_traits::category_tag
           , concept::parser::compound_condition_tag>
          , compound_condition
            <LinkParser, T>
          , typename boost::mpl::if_
          <
            boost::is_convertible
            <typename condition_traits::category_tag
             , concept::parser::assessment_statement_tag>
            , bound_assessment_statement<Bind, T>
            , typename boost::mpl::if_
              <boost::is_convertible
               <typename condition_traits::category_tag
                , concept::parser::compound_statement_tag>
               , compound_statement
               , gntl::detail::void_
              >::type
          >::type
        >
    >::type
  type;
};

}

} }

namespace concept { namespace structure {

template <typename LinkParser, typename ConditionExpressionParser>
struct condition_expression_traits<gntl::structure::composed
                                   ::compound_condition_expression
                                   <LinkParser, ConditionExpressionParser> >
{
  typedef boost::mpl::true_ is_condition_expression;
  typedef gntl::structure::composed
    ::compound_condition_expression
    <LinkParser, ConditionExpressionParser>
    condition_expression;
  typedef typename concept::parser::link_traits<LinkParser>
    link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type
    bind_type;
  typedef typename boost::range_iterator<bind_range>::type
    bind_iterator;
  typedef typename boost::unwrap_reference<ConditionExpressionParser>::type
    parser_condition_expression_type;
  typedef concept::parser::connector_condition_expression_traits
    <parser_condition_expression_type>
    parser_condition_expression_traits;
  typedef typename parser_condition_expression_traits
    ::condition_list_type parser_condition_list_type;
  typedef typename boost::mpl::transform
  <parser_condition_list_type, gntl::structure::composed::compound_expression_detail
   ::transform_to_structure_condition
    <boost::mpl::_1
     , bind_range
     , LinkParser, bind_type> >::type condition_list_type;

  template <typename T>
  struct tag {};

  template <typename T>
  static bool is_type(condition_expression c)
  {
    typedef typename 
      boost::mpl::find
      <condition_list_type
      , T>::type iterator_type;
    BOOST_MPL_ASSERT((boost::mpl::not_
                      <boost::is_same<typename boost::mpl::end
                      <condition_list_type>::type
                      , iterator_type> >));
    typedef typename
      boost::mpl::distance
      <typename boost::mpl::begin
      <condition_list_type>::type
      , iterator_type>::type
      size_type;
    typedef typename
      boost::mpl::advance
      <typename boost::mpl::begin
       <parser_condition_list_type>::type
      , size_type>::type parser_iterator_type;
    typedef typename boost::mpl::deref<parser_iterator_type>
      ::type parser_type;
    return parser_condition_expression_traits
      ::template is_type<parser_type>
      (c.condition);
  }

  template <typename T>
  static T get_aux
    (condition_expression c, tag<concept::structure::simple_condition_tag>)
  {
    typedef typename T::simple_condition_type parser_type;

    typedef concept::parser::connector_simple_condition_traits
      <parser_type> simple_condition_traits;
    typedef typename simple_condition_traits::role_type
      role_type;
    typedef typename T::bind_container_type role_filtered_range;
    typedef typename boost::range_iterator<role_filtered_range>::type
      role_filtered_iterator;

    GNTL_CONCEPT_ASSERT((BoundedSimpleCondition<T>));

    // find correspondent bind
    parser_type simple_c = parser_condition_expression_traits
      ::template get<parser_type>(c.condition);

    bind_range binds = link_traits::bind(c.link);
    typedef gntl::structure::composed::composed_detail::role_predicate
      <role_type> role_predicate;
    role_predicate predicate(simple_condition_traits::role(simple_c));
    role_filtered_iterator
      first (predicate
             , boost::begin(binds), boost::end(binds))
      , last (predicate
              , boost::end(binds), boost::end(binds))
      ;

    if(first == last)
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Can't find the respective role in the bound link for this simple condition"))
                               (typename error::role<typename simple_condition_traits::role_type>::type
                                (simple_condition_traits::role(simple_c))));
    else
      return T
        (role_filtered_range(first, last), simple_c
         , c.role_conditions);
  }

  template <typename T>
  static T get_aux
    (condition_expression c, tag<concept::structure::compound_condition_tag>)
  {
    typedef typename 
      boost::mpl::find
      <condition_list_type
      , T>::type iterator_type;
    typedef typename
      boost::mpl::distance
      <typename boost::mpl::begin
      <condition_list_type>::type
      , iterator_type>::type
      size_type;
    typedef typename
      boost::mpl::advance
      <typename boost::mpl::begin
       <parser_condition_list_type>::type
      , size_type>::type parser_iterator_type;
    typedef typename boost::mpl::deref<parser_iterator_type>
      ::type parser_type;

    GNTL_CONCEPT_ASSERT((CompoundCondition<T>));
    return T
      (c.link, parser_condition_expression_traits::template get<parser_type>
       (c.condition), c.role_conditions);
  }

  template <typename T>
  static T get_aux
    (condition_expression c, tag<concept::structure::assessment_statement_tag>)
  {
    typedef typename T::assessment_statement_parser_type parser_assessment_statement_type;
    GNTL_CONCEPT_ASSERT((concept::parser::ConnectorAssessmentStatement<parser_assessment_statement_type>));
    typedef concept::parser::connector_assessment_statement_traits
      <parser_assessment_statement_type> parser_assessment_statement_traits;
    typedef typename parser_assessment_statement_traits::attribute_assessment_type
      parser_attribute_assessment_type;
    typedef concept::parser::connector_attribute_assessment_traits
      <parser_attribute_assessment_type> parser_attribute_assessment_traits;
    typedef typename parser_attribute_assessment_traits::role_type
      role_type;

    parser_assessment_statement_type
      parser_assessment = parser_condition_expression_traits::
      template get<parser_assessment_statement_type>
      (c.condition);

    parser_attribute_assessment_type first
      = parser_assessment_statement_traits::first(parser_assessment);

    bind_range binds = link_traits::bind(c.link);

    typedef typename boost::range_iterator<bind_range>::type
      bind_iterator;

    typedef gntl::structure::composed::composed_detail::role_predicate
      <role_type> role_predicate;
    role_predicate predicate(parser_attribute_assessment_traits::role(first));
    bind_iterator first_bind = gntl::range::find_if(binds, predicate);

    if(first_bind == boost::end(binds))
      GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Can't find the respective role in the bound link for this attribute assessment"
                                 "(first)"))
                               (typename error::role<typename parser_attribute_assessment_traits::role_type>::type
                                (parser_attribute_assessment_traits::role(first))));

    if(parser_assessment_statement_traits::
       template is_second<parser_attribute_assessment_type>
       (parser_assessment))
    {
      parser_attribute_assessment_type second
        = parser_assessment_statement_traits::template second
        <parser_attribute_assessment_type>
        (parser_assessment);
      
      role_predicate predicate(parser_attribute_assessment_traits::role(second));
      bind_iterator second_bind = gntl::range::find_if(binds, predicate);

      if(second_bind == boost::end(binds))
        GNTL_UNWIND_ERROR_INFO(invalid_ncl_error()
                               , (typename error::reason<const char*>::type
                                  ("Can't find the respective role in the bound link for this attribute assessment"
                                   "(second)"))
                                 (typename error::role<typename parser_attribute_assessment_traits::role_type>::type
                                  (parser_attribute_assessment_traits::role(second))));
      else
        return T(*first_bind, *second_bind, parser_assessment);
    }
    else
      return T(*first_bind, parser_assessment);
  }

  template <typename T>
  static T get_aux
    (condition_expression c, tag<concept::structure::compound_statement_tag>)
  {
    return T();
  }

  template <typename T>
  static T get(condition_expression c)
  {
    typedef gntl::concept::structure::condition_traits
      <T> condition_traits;
    return get_aux<T>(c, tag<typename condition_traits::category_tag>());
  }
  
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
