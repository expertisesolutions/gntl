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

#define BOOST_TEST_MODULE parse_rule_base_algorithm_fail1
#include <boost/test/included/unit_test.hpp>

#include <gntl/archetype/parser/rule_base.hpp>

struct rule_base_fail
{};

void compile_time_specific ()
{
  GNTL_CONCEPT_ASSERT((gntl::concept::parser::RuleBase<rule_base_fail>));
}

BOOST_AUTO_TEST_CASE (test1)
{
    
}

