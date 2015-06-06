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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_HPP

#include <gntl/algorithm/structure/context/start.hpp>
#include <gntl/algorithm/structure/context/start_normal_action.hpp>
#include <gntl/algorithm/structure/context/abort.hpp>
#include <gntl/algorithm/structure/context/abort_normal_action.hpp>
#include <gntl/algorithm/structure/context/pause.hpp>
#include <gntl/algorithm/structure/context/pause_normal_action.hpp>
#include <gntl/algorithm/structure/context/resume.hpp>
#include <gntl/algorithm/structure/context/resume_normal_action.hpp>
#include <gntl/algorithm/structure/context/stop.hpp>
#include <gntl/algorithm/structure/context/stop_normal_action.hpp>
#include <gntl/concept/structure/context.hpp>
#include <gntl/algorithm/structure/context/iteration.hpp>
#include <gntl/detail/max_args.hpp>
#include <gntl/concept_check.hpp>
#include <gntl/unwrap_ref.hpp>

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#endif
