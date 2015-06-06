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

#ifndef GNTL_STRUCTURE_COMPOSED_CONDITION_CONDITION_EXPRESSION_HPP
#define GNTL_STRUCTURE_COMPOSED_CONDITION_CONDITION_EXPRESSION_HPP

#include <gntl/concept_check.hpp>
#include <gntl/detail/void.hpp>
#include <gntl/unwind_error.hpp>
#include <gntl/invalid_ncl_error.hpp>
#include <gntl/structure/composed/condition/bounded_simple_condition.hpp>
#include <gntl/structure/composed/condition/compound_condition.hpp>
#include <gntl/structure/composed/condition/detail/predicate.hpp>
#include <gntl/algorithm/parser/link.hpp>

#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>

#include <boost/version.hpp>
#include <gntl/range.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename LinkParser, typename CausalConnectorParser>
struct condition_expression
{
  typedef concept::parser::link_traits<LinkParser>
    link_parser_traits;
  typedef typename link_parser_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_value_type;
  typedef typename boost::unwrap_reference<bind_value_type>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename bind_traits::role_type role_type;

  condition_expression (LinkParser link
                        , CausalConnectorParser causal_connector
                        , std::map<role_type, bool>* role_conditions)
    : link (link)
    , causal_connector (causal_connector)
    , role_conditions(role_conditions) {}


  LinkParser link;
  CausalConnectorParser causal_connector;
  std::map<role_type, bool>* role_conditions;
};

namespace condition_expression_detail {

template <typename T, typename BindRange>
struct transform_to_simple_condition
{
  typedef concept::parser::connector_simple_condition_traits
    <T> simple_condition_traits;
  typedef typename simple_condition_traits::role_type role_type;
  typedef typename boost::range_value<BindRange>::type bind_type;
  typedef std::vector<bind_type> bind_range;

  typedef bounded_simple_condition<bind_range, T, role_type> type;
};

template <typename T, typename BindRange, typename LinkParser>
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
          , gntl::detail::void_
        >
    >::type
  type;
};

}

} }

namespace concept { namespace structure {

template <typename LinkParser, typename CausalConnectorParser>
struct condition_expression_traits<gntl::structure::composed
                                   ::condition_expression<LinkParser, CausalConnectorParser> >
{
  typedef boost::mpl::true_ is_condition_expression;
  typedef gntl::structure::composed
    ::condition_expression<LinkParser, CausalConnectorParser>
      condition_expression;
  typedef typename concept::parser::link_traits<LinkParser> link_traits;
  typedef typename link_traits::bind_range bind_range;
  typedef typename boost::range_value<bind_range>::type bind_type;
  typedef typename boost::range_iterator<bind_range>::type bind_iterator;
  typedef concept::parser::causal_connector_traits
    <CausalConnectorParser> causal_connector_traits;
  typedef typename causal_connector_traits::condition_type parser_condition_expression_type;
  typedef concept::parser::connector_condition_expression_traits
    <parser_condition_expression_type>
    parser_condition_expression_traits;
  typedef typename parser_condition_expression_traits
    ::condition_list_type parser_condition_list_type;
  typedef typename boost::mpl::transform
  <parser_condition_list_type, gntl::structure::composed::condition_expression_detail
   ::transform_to_structure_condition
    <boost::mpl::_1
     , bind_range
     , LinkParser> >::type condition_list_type;

  template <typename T>
  static bool is_type(condition_expression c)
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
    return parser_condition_expression_traits
      ::template is_type<parser_type>
      (causal_connector_traits::condition(c.causal_connector));
  }

  template <typename T>
  struct tag {};

  template <typename T>
  static T get_aux
    (condition_expression c, tag<gntl::concept::structure::simple_condition_tag>)
  {
    typedef typename T::simple_condition_type parser_type;

    typedef concept::parser::connector_simple_condition_traits
      <parser_type> simple_condition_traits;
    typedef typename simple_condition_traits::role_type
      role_type;
    typedef gntl::structure::composed::composed_detail::role_predicate
      <role_type> role_predicate;
    typedef typename boost::range_iterator<bind_range>::type bind_iterator;
    typedef boost::filter_iterator<role_predicate, bind_iterator>
      role_filtered_iterator;
    typedef boost::iterator_range<role_filtered_iterator>
      role_filtered_range;

    GNTL_CONCEPT_ASSERT((BoundedSimpleCondition<T>));

    // find correspondent bind
    parser_type simple_c = parser_condition_expression_traits
      ::template get<parser_type>
      (causal_connector_traits::condition(c.causal_connector));

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
      GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                             , (typename error::reason<const char*>::type
                                ("Can't find the respective role in the bound link for this simple condition"))
                               (typename error::role<typename simple_condition_traits::role_type>::type
                                (simple_condition_traits::role(simple_c))));
    else
    {
      typedef typename T::bind_container_type bind_container;
      bind_container binds_ (first, last);
      return T(binds_, simple_c, c.role_conditions);
    }
  }

  template <typename T>
  static T get_aux
    (condition_expression c, tag<gntl::concept::structure::compound_condition_tag>)
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
       (causal_connector_traits::condition(c.causal_connector))
       , c.role_conditions);
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
