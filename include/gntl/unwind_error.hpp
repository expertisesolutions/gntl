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

#ifndef GNTL_UNWIND_ERROR_HPP
#define GNTL_UNWIND_ERROR_HPP

#ifndef GNTL_USER_DEFINED_UNWIND_ERROR
#ifndef GNTL_NO_BOOST_EXCEPTION
#include <boost/version.hpp>
#if BOOST_VERSION >= 104200
#include <boost/exception/all.hpp>
#else
#include <boost/exception.hpp>
#endif
#endif

#ifndef GNTL_NO_BOOST_EXCEPTION
#include <gntl/error/reason.hpp>
#include <gntl/error/component_identifier.hpp>
#include <gntl/error/refer.hpp>
#include <gntl/error/property_name.hpp>
#include <gntl/error/property_value.hpp>
#include <gntl/error/role.hpp>
#include <gntl/error/event_type.hpp>
#include <gntl/error/xml_attribute.hpp>

#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define GNTL_UNWIND_ERROR_EXPAND_INFO_REPEAT(z, n, data) << BOOST_PP_SEQ_ELEM(n, data)
#define GNTL_UNWIND_ERROR_EXPAND_INFO(x) BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(x), GNTL_UNWIND_ERROR_EXPAND_INFO_REPEAT, x)

#define GNTL_UNWIND_ERROR(x) BOOST_THROW_EXCEPTION(x)
#define GNTL_UNWIND_ERROR_INFO(x, y) BOOST_THROW_EXCEPTION(::boost::enable_error_info(x) GNTL_UNWIND_ERROR_EXPAND_INFO(y))
#else
#define GNTL_UNWIND_ERROR(x) throw x
#define GNTL_UNWIND_ERROR_INFO(x, y) throw x
#endif

#include <gntl/detail/push_options.hpp>

namespace gntl {

struct gntl_error
#ifndef GNTL_NO_BOOST_EXCEPTION
  : boost::exception, virtual std::exception
#else
  : std::runtime_error
#endif
{
  gntl_error()
#ifdef GNTL_NO_BOOST_EXCEPTION
    : std::runtime_error("")
#endif
  {}

  ~gntl_error() throw() {}
};

}

#include <gntl/detail/pop_options.hpp>

#endif

#endif
