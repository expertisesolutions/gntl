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

# concept_check1.cpp
#add_executable(concept_check1_exe concept_check1.cpp)
#target_link_libraries(concept_check1_exe ${LIBXML2_LIBRARIES})
#add_test(concept_check1 concept_check1_exe)

# create_document_with_libxml2_dom1.cpp
add_executable(create_document_with_libxml2_dom1_exe create_document_with_libxml2_dom1.cpp)
target_link_libraries(create_document_with_libxml2_dom1_exe ${LIBXML2_LIBRARIES})
add_test(create_document_with_libxml2_dom1 create_document_with_libxml2_dom1_exe)
