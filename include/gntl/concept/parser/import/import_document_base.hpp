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

#ifndef GNTL_CONCEPT_PARSER_IMPORT_DOCUMENT_BASE_HPP
#define GNTL_CONCEPT_PARSER_IMPORT_DOCUMENT_BASE_HPP

#include <gntl/concept/parser/import/import_ncl.hpp>
#include <gntl/concept_check.hpp>

#include <iterator>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace concept { namespace parser {

template <typename T>
struct import_document_base_traits
{
  typedef boost::mpl::false_ is_import_document_base;
};

#ifndef GNTL_DISABLE_CONCEPTS
template <typename X>
struct ImportDocumentBase : boost::CopyConstructible<X>
{
    typedef import_document_base_traits<X> traits;
    BOOST_MPL_ASSERT_RELATION(traits::is_import_document_base::value, ==, true);
    typedef typename traits::import_ncl_range import_ncl_range;

    BOOST_CONCEPT_USAGE (ImportDocumentBase)
    {
      convertible_to<import_ncl_range>(traits::import_ncl_all(const_i));
    }

    template <typename To, typename From>
    void convertible_to (From const&)
    {
        BOOST_STATIC_ASSERT ((boost::is_convertible<From, To>::type::value));
    }

    ImportDocumentBase();
    
    X const const_i;
};
#endif
} } }


#include <gntl/detail/pop_options.hpp>

#endif
