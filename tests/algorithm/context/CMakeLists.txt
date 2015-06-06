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

# start_context1.cpp
add_executable(start_context1_exe start_context1.cpp)
target_link_libraries(start_context1_exe ${LIBXML2_LIBRARIES})
add_test(start_context1 start_context1_exe)

# stop_context1.cpp
add_executable(stop_context1_exe stop_context1.cpp)
target_link_libraries(stop_context1_exe ${LIBXML2_LIBRARIES})
add_test(stop_context1 stop_context1_exe)
