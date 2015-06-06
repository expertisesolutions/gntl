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

# pause_media_normal_action_default_descriptor1.cpp
add_executable(pause_media_normal_action_default_descriptor1_exe pause_media_normal_action_default_descriptor1.cpp)
target_link_libraries(pause_media_normal_action_default_descriptor1_exe ${LIBXML2_LIBRARIES})
add_test(pause_media_normal_action_default_descriptor1 pause_media_normal_action_default_descriptor1_exe)

# resume_media_normal_action_default_descriptor1.cpp
add_executable(resume_media_normal_action_default_descriptor1_exe resume_media_normal_action_default_descriptor1.cpp)
target_link_libraries(resume_media_normal_action_default_descriptor1_exe ${LIBXML2_LIBRARIES})
add_test(resume_media_normal_action_default_descriptor1 resume_media_normal_action_default_descriptor1_exe)

# start_media1.cpp
add_executable(start_media1_exe start_media1.cpp)
target_link_libraries(start_media1_exe ${LIBXML2_LIBRARIES})
add_test(start_media1 start_media1_exe)

# start_media_with_descriptor1.cpp
add_executable(start_media_with_descriptor1_exe start_media_with_descriptor1.cpp)
target_link_libraries(start_media_with_descriptor1_exe ${LIBXML2_LIBRARIES})
add_test(start_media_with_descriptor1 start_media_with_descriptor1_exe)

# start_media_with_dimensions1.cpp
add_executable(start_media_with_dimensions1_exe start_media_with_dimensions1.cpp)
target_link_libraries(start_media_with_dimensions1_exe ${LIBXML2_LIBRARIES})
add_test(start_media_with_dimensions1 start_media_with_dimensions1_exe)

# start_media_with_dimensions_through_property1.cpp
add_executable(start_media_with_dimensions_through_property1_exe start_media_with_dimensions_through_property1.cpp)
target_link_libraries(start_media_with_dimensions_through_property1_exe ${LIBXML2_LIBRARIES})
add_test(start_media_with_dimensions_through_property1 start_media_with_dimensions_through_property1_exe)

# stop_media_normal_action_default_descriptor1.cpp
add_executable(stop_media_normal_action_default_descriptor1_exe stop_media_normal_action_default_descriptor1.cpp)
target_link_libraries(stop_media_normal_action_default_descriptor1_exe ${LIBXML2_LIBRARIES})
add_test(stop_media_normal_action_default_descriptor1 stop_media_normal_action_default_descriptor1_exe)
