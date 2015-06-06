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

#ifndef GNTL_CONCEPT_PARSER_HEAD_HPP
#define GNTL_CONCEPT_PARSER_HEAD_HPP

#include <gntl/concept/parser/transition/transition_base.hpp>
#include <gntl/concept/parser/import/import_document_base.hpp>
#include <gntl/concept/parser/rule/rule_base.hpp>
#include <gntl/concept/parser/descriptor/descriptor_base.hpp>
#include <gntl/concept/parser/connector/connector_base.hpp>
#include <gntl/concept_check.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/mpl/bool.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct head_traits
{
  typedef boost::mpl::false_ is_head;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct Head : boost::CopyConstructible<X>
{
    typedef head_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_head::value, ==, true);
    typedef typename traits::import_document_base_type import_document_base_type;
    typedef typename traits::rule_base_type rule_base_type;
    typedef typename traits::transition_base_type transition_base_type;
    typedef typename traits::descriptor_base_type descriptor_base_type;
    typedef typename traits::connector_base_type connector_base_type;
    typedef typename traits::region_base_range region_base_range;

    BOOST_CONCEPT_ASSERT ((ImportDocumentBase<import_document_base_type>));
    BOOST_CONCEPT_ASSERT ((RuleBase<rule_base_type>));
    BOOST_CONCEPT_ASSERT ((TransitionBase<transition_base_type>));
    BOOST_CONCEPT_ASSERT ((DescriptorBase<descriptor_base_type>));
    BOOST_CONCEPT_ASSERT ((ConnectorBase<connector_base_type>));

    BOOST_CONCEPT_USAGE (Head)
    {
        convertible_to<bool>(traits::has_import_document_base (i));
        convertible_to<import_document_base_type> (traits::import_document_base (i));
        convertible_to<bool>(traits::has_rule_base (i));
        convertible_to<rule_base_type> (traits::rule_base (i));
        convertible_to<bool>(traits::has_descriptor_base (i));
        convertible_to<descriptor_base_type> (traits::descriptor_base (i));
        convertible_to<bool>(traits::has_transition_base (i));
        convertible_to<transition_base_type> (traits::transition_base (i));
        convertible_to<bool>(traits::has_connector_base (i));
        convertible_to<connector_base_type> (traits::connector_base (i));
        convertible_to<region_base_range> (traits::region_base_all (i));
    }

    template <typename T0, typename T1>
    void convertible_to (T1 const&)
    {
        BOOST_MPL_ASSERT ((boost::is_convertible<T1,T0>));
    }

    X i;
};
#endif

} } }


#include <gntl/detail/pop_options.hpp>

#endif
