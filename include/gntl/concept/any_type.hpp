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

#ifndef GNTL_CONCEPT_ANY_TYPE_HPP
#define GNTL_CONCEPT_ANY_TYPE_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl {

namespace mpl = boost::mpl;

namespace concept {

struct any_type {};

template <template <typename> class Concept, typename X>
struct ConceptOrAny : Concept<X>
{};

template <template <typename> class Concept>
struct ConceptOrAny<Concept, any_type> {};

template <typename T, typename Substitute>
struct substitute_if_is_any_type
    : mpl::if_<boost::is_same<T, any_type>
               , Substitute
               , T>
{
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
