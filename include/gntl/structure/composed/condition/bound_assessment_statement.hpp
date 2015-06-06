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

#ifndef GNTL_STRUCTURE_COMPOSED_BOUND_ASSESSMENT_STATEMENT_HPP
#define GNTL_STRUCTURE_COMPOSED_BOUND_ASSESSMENT_STATEMENT_HPP

#include <gntl/concept/parser/connector/connector_attribute_assessment.hpp>
#include <gntl/concept/structure/condition/bound_attribute_assessment.hpp>
#include <gntl/concept/structure/condition/bound_assessment_statement.hpp>
#include <gntl/concept/structure/condition/condition.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Bind, typename AttributeAssessmentParser>
struct bound_attribute_assessment
{
  bound_attribute_assessment(Bind bind
                             , AttributeAssessmentParser attribute_assessment_parser)
    : bind(bind), attribute_assessment_parser(attribute_assessment_parser)
  {}

  Bind bind;
  AttributeAssessmentParser attribute_assessment_parser;
};

template <typename Bind, typename AssessmentStatementParser>
struct bound_assessment_statement
{
  bound_assessment_statement(Bind first_bind, AssessmentStatementParser assessment)
  : first_bind(first_bind), assessment_statement_parser(assessment) {}
  bound_assessment_statement(Bind first_bind
                             , Bind second_bind, AssessmentStatementParser assessment)
  : first_bind(first_bind)
  , second_bind(second_bind)
  , assessment_statement_parser(assessment) {}

  typedef AssessmentStatementParser assessment_statement_parser_type;
  typedef Bind bind_type;

  Bind first_bind;
  boost::optional<Bind> second_bind;
  AssessmentStatementParser assessment_statement_parser;
};

template <typename Bind, typename ValueAssessmentParser>
struct value_assessment
{
  value_assessment(Bind bind, ValueAssessmentParser value_assessment_parser)
    : bind(bind), value_assessment_parser(value_assessment_parser)
  {}

  Bind bind;
  ValueAssessmentParser value_assessment_parser;
};

} }

namespace concept { namespace structure {

template <typename Bind, typename AssessmentStatementParser>
struct bound_assessment_statement_traits<gntl::structure::composed::bound_assessment_statement
                                         <Bind, AssessmentStatementParser> >
{
  typedef boost::mpl::true_ is_bound_assessment_statement;
  typedef gntl::structure::composed::bound_assessment_statement<Bind, AssessmentStatementParser>
    assessment_statement;

  typedef concept::parser::connector_assessment_statement_traits
    <AssessmentStatementParser> parser_assessment_statement_traits;
  typedef typename parser_assessment_statement_traits::comparator_type comparator_type;
  typedef typename parser_assessment_statement_traits::attribute_assessment_type parser_attribute_assessment_type;
  typedef gntl::structure::composed::bound_attribute_assessment
    <Bind, parser_attribute_assessment_type> attribute_assessment_type;
  typedef typename parser_assessment_statement_traits::value_assessment_type value_assessment_parser_type;
  typedef gntl::structure::composed::value_assessment<Bind, value_assessment_parser_type>
    value_assessment_type;

  static comparator_type comparator(assessment_statement s)
  {
    return parser_assessment_statement_traits::comparator(s.assessment_statement_parser);
  }

  static attribute_assessment_type first(assessment_statement s)
  {
    return attribute_assessment_type(s.first_bind
                                     , parser_assessment_statement_traits::first
                                     (s.assessment_statement_parser));
  }

  template <typename T>
  struct tag {};

  static attribute_assessment_type second_aux(assessment_statement s
                                               , tag<attribute_assessment_type>)
  {
    return attribute_assessment_type(s.first_bind
                                     , parser_assessment_statement_traits
                                     ::template second<parser_attribute_assessment_type>
                                     (s.assessment_statement_parser));
  }  

  static value_assessment_type second_aux(assessment_statement s
                                          , tag<value_assessment_type>)
  {
    return 
      value_assessment_type
      (s.first_bind
       , parser_assessment_statement_traits
       ::template second<value_assessment_parser_type>
       (s.assessment_statement_parser));
  }  

  template <typename T>
  static T second(assessment_statement s)
  {
    return second_aux(s, tag<T>());
  }

  static bool is_second_aux(assessment_statement s
                            , tag<attribute_assessment_type>)
  {
    return parser_assessment_statement_traits
      ::template is_second<parser_attribute_assessment_type>
      (s.assessment_statement_parser);
  }

  static bool is_second_aux(assessment_statement s
                            , tag<value_assessment_type>)
  {
    return parser_assessment_statement_traits
      ::template is_second<value_assessment_parser_type>
      (s.assessment_statement_parser);
  }

  template <typename T>
  static bool is_second(assessment_statement s)
  {
    return is_second_aux(s, tag<T>());
  }
};

template <typename Bind, typename AssessmentStatementParser>
struct condition_traits
  <gntl::structure::composed::bound_assessment_statement<Bind, AssessmentStatementParser> >
{
  typedef boost::mpl::true_ is_condition;
  typedef assessment_statement_tag category_tag;
};

template <typename Bind, typename AttributeAssessmentParser>
struct bound_attribute_assessment_traits<gntl::structure::composed
                                         ::bound_attribute_assessment<Bind, AttributeAssessmentParser> >
{
  typedef boost::mpl::true_ is_bound_attribute_assessment;

  typedef gntl::structure::composed::bound_attribute_assessment
    <Bind, AttributeAssessmentParser> bound_attribute_assessment;
  typedef typename boost::unwrap_reference<AttributeAssessmentParser>::type
    parser_attribute_assessment_type;
  typedef concept::parser::connector_attribute_assessment_traits
    <parser_attribute_assessment_type>
    parser_attribute_assessment_traits;
  typedef typename boost::unwrap_reference<Bind>::type bind_type;
  typedef concept::parser::bind_traits<bind_type> bind_traits;
  typedef typename parser_attribute_assessment_traits::role_type role_type;
  typedef typename parser_attribute_assessment_traits::event_type_type event_type_type;
  typedef typename parser_attribute_assessment_traits::key_type key_type;
  typedef typename parser_attribute_assessment_traits::attribute_type_type attribute_type_type;
  typedef typename parser_attribute_assessment_traits::offset_type offset_type;
  typedef typename bind_traits::component_type component_type;
  typedef typename bind_traits::interface_type interface_type;

  static role_type role(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::role(a.attribute_assessment_parser);
  }
  static bool has_event_type(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::has_event_type(a.attribute_assessment_parser);
  }
  static event_type_type event_type(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::event_type(a.attribute_assessment_parser);
  }
  static bool has_key(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::has_key(a.attribute_assessment_parser);
  }
  static key_type key(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::key(a.attribute_assessment_parser);
  }
  static bool has_attribute_type(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::has_attribute_type(a.attribute_assessment_parser);
  }
  static attribute_type_type attribute_type(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::attribute_type(a.attribute_assessment_parser);
  }
  static bool has_offset(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::has_offset(a.attribute_assessment_parser);
  }
  static offset_type offset(bound_attribute_assessment a)
  {
    return parser_attribute_assessment_traits::offset(a.attribute_assessment_parser);
  }
  static component_type component(bound_attribute_assessment a)
  {
    return bind_traits::component(a.bind);
  }
  static interface_type interface_(bound_attribute_assessment a)
  {
    return bind_traits::interface_(a.bind);
  }
  static bool has_interface(bound_attribute_assessment a)
  {
    return bind_traits::has_interface(a.bind);
  }
};

}

namespace parser {

template <typename Bind, typename ValueAssessmentParser>
struct connector_value_assessment_traits<gntl::structure::composed::value_assessment
                                         <Bind, ValueAssessmentParser> >
{
  typedef boost::mpl::true_ is_connector_value_assessment;
  typedef gntl::structure::composed::value_assessment<Bind, ValueAssessmentParser>
    value_assessment;
  typedef typename boost::unwrap_reference<ValueAssessmentParser>::type value_assessment_parser_type;
  typedef connector_value_assessment_traits<value_assessment_parser_type> value_assessment_parser_traits;
  typedef typename value_assessment_parser_traits::value_type value_type;

  static value_type value(value_assessment v)
  {
    typedef typename boost::unwrap_reference<Bind>::type bind_type;
    typedef concept::parser::bind_traits<bind_type> bind_traits;
    typedef typename bind_traits::bind_param_range bind_param_range;

    value_type value = value_assessment_parser_traits::value(v.value_assessment_parser);
    if(value.size() != 0 && *value.begin() == '$')
    {
      typedef typename boost::range_iterator
        <bind_param_range>::type bind_param_iterator;
      typedef typename boost::range_value
        <bind_param_range>::type bind_param_type;
      typedef concept::parser::bind_param_traits
        <bind_param_type> bind_param_traits;
      bind_param_range bind_params = bind_traits::bind_param(v.bind);      
      if(boost::distance(bind_params) != 0)
      {
        typedef typename value_type::const_iterator key_iterator;
        key_iterator key_first = boost::next(boost::begin(value))
          , key_last = boost::end(value);
        for(bind_param_iterator first = boost::begin(bind_params)
              , last = boost::end(bind_params)
              ;first != last
              ;++first)
        {
          typename bind_param_traits::name_type name = bind_param_traits::name (*first);
          if(gntl::range::equal(name
                                , boost::iterator_range<key_iterator>
                                (key_first, key_last)))
            return bind_param_traits::value(*first);
        }
      }      
    }

    return value;
  }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
