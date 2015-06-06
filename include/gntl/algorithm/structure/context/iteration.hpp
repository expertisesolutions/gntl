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

#ifndef GNTL_ALGORITHM_STRUCTURE_CONTEXT_ITERATION_HPP
#define GNTL_ALGORITHM_STRUCTURE_CONTEXT_ITERATION_HPP

#include <gntl/concept/structure/context.hpp>
#include <gntl/range.hpp>

#include <boost/version.hpp>
#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <boost/ref.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace context {

template <typename Context, typename UnaryFunction>
void for_each_recursively_unprotected(Context c, UnaryFunction f);

struct for_each_recursively_functor
{
  typedef void result_type;
  template <typename Context, typename UnaryFunction>
  result_type operator()(Context c, UnaryFunction f) const
  {
    return for_each_recursively_unprotected(c, f);
  }
};

template <typename Context, typename UnaryFunction>
void for_each_recursively_unprotected(Context c, UnaryFunction f)
{
  f(c);

  typedef typename boost::unwrap_reference<Context>::type
    context_type;
  typedef concept::structure::context_traits<context_type>
    context_traits;
#if BOOST_VERSION > 104200
  boost::range::for_each(context_traits::context_all(c)
                         , boost::bind(for_each_recursively_functor()
                                       , _1, f));
#else
  typename context_traits::context_range contexts
    = context_traits::context_all(c);
  std::for_each(boost::begin(contexts), boost::end(contexts)
                , boost::bind(for_each_recursively_functor()
                              , _1, f));
#endif
}

// template <typename Context, typename UnaryFunction>
// void for_each_recursively(Context c, UnaryFunction f)
// {
//   return for_each_recursively_unprotected(c, boost::protect(f));
// }

template <typename Context, typename BinaryFunction, typename Value>
Value fold_recursively_unprotected(Context c, BinaryFunction f, Value v);

template <typename Value>
struct fold_recursively_functor
{
  typedef Value result_type;
  template <typename Context, typename BinaryFunction, Value>
  result_type operator()(Context c, BinaryFunction f, Value v) const
  {
    return for_each_recursively_unprotected(c, f, v);
  }
};

template <typename Context, typename BinaryFunction, typename Value>
Value fold_recursively_unprotected(Context c, BinaryFunction f, Value value)
{
  value = f(c, value);

  typedef typename boost::unwrap_reference<Context>::type
    context_type;
  typedef concept::structure::context_traits<context_type>
    context_traits;
  gntl::range::accumulate(context_traits::context_all(c)
                          , boost::bind(fold_recursively_functor<Value>()
                                        , _1, f, _2), value);
}

// template <typename Context, typename BinaryFunction, typename Value>
// Value fold_recursively(Context c, BinaryFunction f, Value v)
// {
//   return fold_recursively_unprotected(c, boost::protect(f), v);
// }

template <typename Context, typename Predicate>
bool for_each_until_recursively_unprotected(Context c, Predicate f);

struct for_each_until_recursively_functor
{
  typedef bool result_type;
  template <typename Context, typename Predicate>
  result_type operator()(Context c, Predicate f) const
  {
    return for_each_until_recursively_unprotected(c, f);
  }
};

template <typename Context, typename Predicate>
bool for_each_until_recursively_unprotected(Context c, Predicate f)
{
  if(f(c))
    return true;

  typedef typename boost::unwrap_reference<Context>::type
    context_type;
  typedef concept::structure::context_traits<context_type>
    context_traits;
  typename context_traits::context_range
    range = context_traits::context_all(c);
#if BOOST_VERSION > 104200
  return 
    boost::range::find_if(range
                          , boost::bind(for_each_until_recursively_functor()
                                        , _1, f))
    != boost::end(range);
#else
  return 
    std::find_if(boost::begin(range), boost::end(range)
                 , boost::bind(for_each_until_recursively_functor()
                               , _1, f))
    != boost::end(range);
#endif
}

// template <typename Context, typename Predicate>
// bool for_each_until_recursively(Context c, Predicate f)
// {
//   return for_each_until_recursively_unprotected (c, boost::protect(f));
// }

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
