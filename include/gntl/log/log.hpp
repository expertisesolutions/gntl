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

#ifndef GNTL_LOG_LOG_HPP
#define GNTL_LOG_LOG_HPP

#ifdef GNTL_ENABLE_DEBUG
#ifndef GNTL_LOG_OUTPUT
#include <boost/io/ios_state.hpp>
#include <iostream>
#define GNTL_LOG_OUTPUT std::cerr
#endif

#define GNTL_DEBUG_LOG(x)     \
    { \
      boost::io::ios_flags_saver BOOST_PP_CAT (ghtv_ncl_interpreter_log_flags_saver_, __LINE__)(GNTL_LOG_OUTPUT); \
      boost::io::ios_precision_saver BOOST_PP_CAT (ghtv_ncl_interpreter_log_precision_saver, __LINE__)(GNTL_LOG_OUTPUT); \
      boost::io::ios_width_saver BOOST_PP_CAT (ghtv_ncl_interpreter_log_width_saver, __LINE__)(GNTL_LOG_OUTPUT); \
      GNTL_LOG_OUTPUT << x;                                             \
    }
#define GNTL_LOG(x) GNTL_DEBUG_LOG(x)
#else
#define GNTL_DEBUG_LOG(x) {}
#define GNTL_LOG(x) {}
#endif

#endif
