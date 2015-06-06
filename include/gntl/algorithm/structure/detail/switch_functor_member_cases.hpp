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

#ifndef BOOST_PP_IS_ITERATING
#error This header must not be included directly
#endif

case BOOST_PP_CAT(C, BOOST_PP_ITERATION())::first::value:
{
  typedef BOOST_PP_CAT(C, BOOST_PP_ITERATION()) case_type;
  GNTL_DEBUG_LOG("=== CASE " << case_type::first::value << std::endl)
  typename case_type::second f;
  return f(BOOST_PP_ENUM_PARAMS(GNTL_ALGORITHM_STRUCTURE_switch_arguments, a));
}
