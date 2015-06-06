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

#define BOOST_TEST_MODULE test1
#include <boost/test/included/unit_test.hpp>

#include <gntl/parser/generic/parse_document.hpp>

struct import_ncl_node
{
  struct document_uri_type {};
  struct alias_type {};
};

import_ncl_node::document_uri_type document_uri(import_ncl_node)
{
  return import_ncl_node::document_uri_type();
}

import_ncl_node::alias_type alias(import_ncl_node)
{
  return import_ncl_node::alias_type();
}

struct import_document_node
{
    typedef import_ncl_node* import_ncl_iterator;
};

import_ncl_node* import_ncl_begin (import_document_node)
{
    return 0;
}

import_ncl_node* import_ncl_end (import_document_node)
{
    return 0;
}

struct rule_base_node
{
    typedef std::string identifier_type;
};

std::string identifier (rule_base_node)
{
    return "";
}

struct head_node
{
    typedef import_document_node import_document_type;
    typedef rule_base_node rule_base_type;
};

struct body_node
{
    typedef float result_type;
};

import_document_node import_document_base (head_node)
{
    return import_document_node ();
}

rule_base_node rule_base (head_node)
{
    return rule_base_node ();
}

struct document_node
{
    typedef head_node head_type;
    typedef body_node body_type;
};

head_node head (document_node)
{
    return head_node ();
}

body_node body (document_node)
{
    return body_node ();
}

struct import_document_factory
{
    typedef int result_type;
    typedef gntl::concept::any_type import_document_type;
    template <typename ImportDocument>
    result_type operator()(ImportDocument) const { return result_type (); }
};

struct rule_base_factory
{
    typedef int result_type;

    typedef rule_base_node rule_base_type;

    template <typename RuleBase>
    result_type operator()(RuleBase) const { return 0; }
};

struct head_factory
{
    typedef int result_type;
    typedef import_document_factory import_document_factory_type;
    typedef rule_base_factory rule_base_factory_type;

    result_type operator()(int, int) const { return result_type (); }
};

import_document_factory import_document_base (head_factory)
{
    return import_document_factory ();
}

rule_base_factory rule_base (head_factory)
{
    return rule_base_factory ();
}

struct body_factory
{
    typedef float result_type;
};

struct document_factory
{
    typedef void result_type;
    typedef body_factory body_type;
    typedef head_factory head_type;

    typedef head_factory::result_type head_result_type;
    typedef body_factory::result_type body_result_type;

    result_type operator()(head_result_type, body_result_type) const
    {
    }
};

head_factory head (document_factory)
{
    return head_factory ();
}

body_factory body (document_factory)
{
  return body_factory ();
}

BOOST_AUTO_TEST_CASE (test1)
{
    document_node v;
    document_factory f;
    gntl::parser::generic::parse_document (v, f);
}
