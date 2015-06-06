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

macro (add_compile_test name file)
      set(GNTL_COMPILE_TEST false)
      set(GNTL_COMPILE_INCLUDE_DIRECTORIES ${GNTL_ROOT_DIR}/include ${Boost_INCLUDE_DIR}
          ${LIBXML2_INCLUDE_DIR}
        )
      try_compile(GNTL_COMPILE_TEST ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${file}
                  CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${GNTL_COMPILE_INCLUDE_DIRECTORIES}"
                  OUTPUT_VARIABLE GNTL_COMPILE_TEST_OUTPUT
                  )
      if(NOT GNTL_COMPILE_TEST)
             message(FATAL_ERROR "Test compilation failure " ${name} "\n" ${GNTL_COMPILE_TEST_OUTPUT})
      endif(NOT GNTL_COMPILE_TEST)
endmacro (add_compile_test)

macro (add_compile_fail_test name file)
      set(GNTL_COMPILE_TEST false)
      set(GNTL_COMPILE_INCLUDE_DIRECTORIES ${GNTL_ROOT_DIR}/include ${Boost_INCLUDE_DIR}
          ${LIBXML2_INCLUDE_DIR}
        )
      try_compile(GNTL_COMPILE_TEST ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${file}
                  CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${GNTL_COMPILE_INCLUDE_DIRECTORIES}"
                  OUTPUT_VARIABLE GNTL_COMPILE_TEST_OUTPUT
                  )
      if(GNTL_COMPILE_TEST)
             message(FATAL_ERROR "Failure compilation test unexpectadly succeeded " ${name} "\n" ${GNTL_COMPILE_TEST_OUTPUT})
      endif(GNTL_COMPILE_TEST)
endmacro (add_compile_fail_test)
