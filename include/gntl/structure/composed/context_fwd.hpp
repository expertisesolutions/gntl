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

#ifndef GNTL_STRUCTURE_COMPOSED_CONTEXT_FWD_HPP
#define GNTL_STRUCTURE_COMPOSED_CONTEXT_FWD_HPP

#include <gntl/concept/parser/context/context.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/concept/structure/media.hpp>
#include <gntl/concept/structure/presentation.hpp>
#include <gntl/algorithm/parser/causal_connector.hpp>
#include <gntl/structure/composed/media_recursive_lookupable.hpp>
#include <gntl/structure/composed/media_lookupable.hpp>
#include <gntl/structure/composed/context_lookupable.hpp>
#include <gntl/structure/composed/media.hpp>
#include <gntl/structure/composed/link.hpp>
#include <gntl/structure/composed/switch.hpp>
#include <gntl/parameter.hpp>
#include <gntl/range.hpp>

#include <boost/iterator/iterator_adaptor.hpp>

#include <vector>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserContext, typename PresentationFactory, typename ParserCausalConnector>
struct context;

} }

namespace concept { namespace structure {

template <typename ParserContext, typename PresentationFactory, typename ParserCausalConnector>
struct context_traits<gntl::structure::composed::context<ParserContext, PresentationFactory
                                                         , ParserCausalConnector> >;

} } }


#include <gntl/detail/pop_options.hpp>

#endif
