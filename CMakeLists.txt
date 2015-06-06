# (c) Copyright 2011-2014 Felipe Magno de Almeida
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.6)
project (gntl)

add_definitions(-DBOOST_ALL_NO_LIB=1 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)

find_package(Boost)
find_package(LibXml2)

if (NOT LIBXML2_FOUND)
  message(FATAL_ERROR "Could not find the required libxml2 library")
endif (NOT LIBXML2_FOUND)

if (NOT Boost_FOUND)
  message(FATAL_ERROR "Could not find the required Boost libraries. Define BOOST_ROOT")
endif (NOT Boost_FOUND)

include_directories(include)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${LIBXML2_INCLUDE_DIR})

set(GNTL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(cmake/CompileTest.cmake)

enable_testing()

add_subdirectory(tests)
