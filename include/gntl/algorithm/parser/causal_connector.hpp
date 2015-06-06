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

#ifndef GNTL_ALGORITHM_CAUSAL_CONNECTOR_HPP
#define GNTL_ALGORITHM_CAUSAL_CONNECTOR_HPP

#include <gntl/concept/parser/connector/causal_connector.hpp>
#include <gntl/concept/parser/connector/connector_base.hpp>
#include <gntl/concept_check.hpp>

#include <gntl/range.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace parser { namespace causal_connector {

template <typename Identifier>
struct causal_connector_identifier_predicate
{
  causal_connector_identifier_predicate(Identifier identifier)
    : identifier(identifier) {}

  typedef bool result_type;

  template <typename CausalConnector>
  result_type operator()(CausalConnector c) const
  {
    typedef typename boost::unwrap_reference<CausalConnector>::type
      causal_connector_type;
    typedef concept::parser::causal_connector_traits
      <causal_connector_type> causal_connector_traits;
    return identifier == causal_connector_traits::identifier(c);
  }
  
  Identifier identifier;
};

template <typename OptionalBaseIdentifier, typename CausalConnector>
struct causal_connector_id_predicate
{
  typedef concept::parser::causal_connector_traits
    <CausalConnector> causal_connector_traits;
  typedef typename causal_connector_traits::identifier_type
    identifier_type;

  causal_connector_id_predicate(OptionalBaseIdentifier base_identifier
                                , identifier_type identifier)
    : base_identifier(base_identifier), identifier(identifier) {}

  typedef bool result_type;

  result_type operator()(CausalConnector c) const
  {
    identifier_type item_identifier = causal_connector_traits::identifier(c);
    if(item_identifier == identifier)
      return true;
    else if(base_identifier
            && boost::size(identifier) == boost::size(*base_identifier)
            + 1 + boost::size(item_identifier)
            && (!std::lexicographical_compare(boost::begin(identifier)
                                              , boost::next(boost::begin(identifier)
                                                            , boost::size(*base_identifier))
                                              , boost::begin(*base_identifier)
                                              , boost::end(*base_identifier))
                && !std::lexicographical_compare(boost::begin(*base_identifier)
                                                 , boost::end(*base_identifier)
                                                 , boost::begin(identifier)
                                                 , boost::next(boost::begin(identifier)
                                                               , boost::size(*base_identifier)))
                ))
    {
      typename boost::range_iterator<identifier_type>::type
        iterator = boost::next(boost::begin(identifier)
                               , boost::size(*base_identifier));
      if(*iterator == '#')
      {
        ++iterator;
        return (!std::lexicographical_compare(iterator
                                              , boost::end(identifier)
                                              , boost::begin(item_identifier)
                                              , boost::end(item_identifier))
                && !std::lexicographical_compare(boost::begin(item_identifier)
                                                 , boost::end(item_identifier)
                                                 , iterator
                                                 , boost::end(identifier)))
          ;

      }
    }
    return false;
  }
  
  OptionalBaseIdentifier base_identifier;
  identifier_type identifier;
};

template <typename ConnectorBase>
typename boost::range_iterator
<
  typename concept::parser::connector_base_traits
  <
    typename boost::unwrap_reference<ConnectorBase>::type
  >::causal_connector_range
>::type
find_by_identifier(ConnectorBase base
                   , typename concept::parser::causal_connector_traits
                    <
                      typename boost::range_value
                      <
                        typename concept::parser::connector_base_traits
                        <
                          typename boost::unwrap_reference
                          <ConnectorBase>::type
                        >::causal_connector_range
                      >::type
                    >::identifier_type identifier)
{
  typedef typename boost::unwrap_reference<ConnectorBase>::type connector_base;
  GNTL_CONCEPT_ASSERT((concept::parser::ConnectorBase<connector_base>));
  typedef concept::parser::connector_base_traits
    <connector_base> connector_base_traits;
  typedef typename connector_base_traits::causal_connector_range
    causal_connector_range;
  typedef typename connector_base_traits::identifier_type
    identifier_type;
  typedef boost::optional<identifier_type> base_identifier_type;
  base_identifier_type base_identifier;
  if(connector_base_traits::has_identifier(base))
    base_identifier = connector_base_traits::identifier(base);
  typedef typename connector_base_traits::causal_connector_range
    causal_connector_range;
  typedef typename boost::range_value<causal_connector_range>
    ::type causal_connector_type;

  causal_connector_range r = connector_base_traits::causal_connector_all(base);

  causal_connector_id_predicate<base_identifier_type, causal_connector_type>
    predicate(base_identifier, identifier);

  return gntl::range::find_if(r, predicate);
}

template <typename ConnectorBase, typename IdentifierOp>
struct found_filter
{
  found_filter() {}
  found_filter(ConnectorBase base, IdentifierOp op = IdentifierOp())
    : base(base), op(op) {}
  typedef bool result_type;
  template <typename X>
  result_type operator()(X x) const
  {
    typedef typename boost::unwrap_reference<ConnectorBase>
      ::type connector_base;
    typedef concept::parser::connector_base_traits
      <connector_base> connector_base_traits;
    typedef typename connector_base_traits::causal_connector_range
      causal_connector_range;
    causal_connector_range causal_connectors
      = connector_base_traits::causal_connector_all(base);
    
    return find_by_identifier(base, op(x))
      != boost::end(causal_connectors);
  }

  ConnectorBase base;
  IdentifierOp op;
};

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
