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

add_compile_test(parse_body_algorithm parse_body_algorithm.cpp)
add_compile_test(parse_connector_base_algorithm parse_connector_base_algorithm.cpp)
add_compile_test(parse_context_algorithm parse_context_algorithm.cpp)
add_compile_test(parse_descriptor_base_algorithm parse_descriptor_base_algorithm.cpp)
add_compile_test(parse_import_documents_algorithm parse_import_documents_algorithm.cpp)
add_compile_fail_test(parse_import_documents_algorithm_fail1 parse_import_documents_algorithm_fail1.cpp)
add_compile_test(parse_link_algorithm parse_link_algorithm.cpp)
add_compile_test(parse_media_algorithm parse_media_algorithm.cpp)
add_compile_test(parse_region_base_algorithm parse_region_base_algorithm.cpp)
add_compile_fail_test(parse_region_base_algorithm_fail1 parse_region_base_algorithm_fail1.cpp)
add_compile_test(parse_rule_base_algorithm parse_rule_base_algorithm.cpp)
add_compile_fail_test(parse_rule_base_algorithm_fail1 parse_rule_base_algorithm_fail1.cpp)
add_compile_test(parse_transition_base_algorithm parse_transition_base_algorithm.cpp)
add_compile_fail_test(parse_transition_base_algorithm_fail1 parse_transition_base_algorithm_fail1.cpp)
