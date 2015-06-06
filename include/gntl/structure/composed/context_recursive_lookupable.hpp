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

#ifndef GNTL_STRUCTURE_COMPOSED_CONTEXT_RECURSIVE_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_CONTEXT_RECURSIVE_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>

#include <boost/mpl/contains.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/variant.hpp>
#include <boost/shared_ptr.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Context, typename DocumentURI>
struct context_recursive_lookupable
{
  typedef context_recursive_lookupable<Context, DocumentURI> self_type;
  typedef std::map<std::string, std::pair<DocumentURI, boost::shared_ptr<self_type> > >
    aliased_context_lookupables_map;

  context_recursive_lookupable(Context context, aliased_context_lookupables_map map)
    : context(context), map(map) {}

  Context context;
  aliased_context_lookupables_map map;
};

} }

namespace concept {

template <typename Context, typename DocumentURI>
struct lookupable_traits<gntl::structure::composed::context_recursive_lookupable
                         <Context, DocumentURI> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::context_recursive_lookupable
    <Context, DocumentURI> context_lookupable;
  typedef std::string key_type;

  template <typename CurrentContext, typename List>
  struct get_context_types
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    typedef typename gntl::ref_once_meta<CurrentContext>::type ref_context_type;
    typedef concept::structure::context_traits<context_type> traits;
    typedef typename traits::context_range context_range;
    typedef typename boost::range_value<context_range>::type context_inner_value_type;
    typedef typename gntl::ref_once_meta<context_inner_value_type>::type context_inner_type;
    typedef typename boost::mpl::push_back<List, ref_context_type>::type new_list;
    typedef typename boost::mpl::eval_if
      <boost::mpl::contains<new_list, context_inner_type>
       , boost::mpl::identity<new_list>
       , get_context_types<context_inner_type, new_list>
       >::type type;
  };
  typedef typename get_context_types<Context, boost::mpl::vector0<> >::type context_types;
  typedef typename boost::make_variant_over<context_types>::type value_type;

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) const { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) const { return !(*this == other); }
    value_type* operator->() { return &*r; }
  };

  static result_type lookup(context_lookupable l, key_type const key)
  {
    typedef typename key_type::const_iterator key_iterator;
    key_iterator sharp = std::find(key.begin(), key.end(), '#');

    if(sharp != key.end())
    {
      GNTL_DEBUG_LOG("sharp char" << std::endl)
      std::string alias(boost::begin(key), sharp);
      std::string new_key(boost::next(sharp), boost::end(key));
      
      typedef typename context_lookupable::aliased_context_lookupables_map aliased_context_lookupables_map;
      typedef typename aliased_context_lookupables_map::const_iterator alias_iterator;
      alias_iterator alias_it = l.map.find(alias);
      if(alias_it != l.map.end())
      {
        GNTL_DEBUG_LOG("Found alias" << std::endl)
        return lookup(*alias_it->second.second, new_key);
      }
      else
        GNTL_DEBUG_LOG("Not found alias " << alias << std::endl)
    }
    else
    {
      result_type r = lookup_aux(l.context, key);
      if(r != not_found(l))
        return r;
    }
    return result_type(boost::none);
  }

  static result_type not_found(context_lookupable l)
  {
    return result_type(boost::none);
  }
private:
  template <typename CurrentContext>
  static result_type lookup_aux(CurrentContext c, key_type key)
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    GNTL_CONCEPT_ASSERT((concept::structure::Context<context_type>));
    typedef concept::structure::context_traits<context_type> context_traits;

    typedef typename context_traits::context_range context_range_value_type;
    typedef typename unwrap_parameter<context_range_value_type>::type context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;

    if(context_traits::identifier(c) == key)
      return result_type(value_type(gntl::ref_once(c)));

    context_range_value_type contexts = context_traits::context_all(c);

    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last;++first)
    {
      typedef typename boost::range_value<context_range>::type inner_context_value_type;
      typedef typename unwrap_parameter<inner_context_value_type>::type inner_context_type;
      GNTL_CONCEPT_ASSERT((concept::structure::Context<inner_context_type>));
      typedef concept::structure::context_traits<inner_context_type> inner_context_traits;
      if(inner_context_traits::identifier(*first) == key)
        return result_type(value_type(gntl::ref_once(*first)));
      result_type r = lookup_aux(gntl::ref(*first), key);
      if(r != result_type(boost::none))
        return r;
    }

    typedef typename context_traits::switch_range switch_range_value_type;
    typedef typename unwrap_parameter<switch_range_value_type>::type switch_range;
    typedef typename boost::range_iterator<switch_range>::type switch_iterator;

    switch_range_value_type switches = context_traits::switch_all(c);

    for(switch_iterator first = boost::begin(switches), last = boost::end(switches)
          ;first != last;++first)
    {
      typedef typename boost::range_value<switch_range>::type switch_value_type;
      typedef typename unwrap_parameter<switch_value_type>::type switch_type;
      GNTL_CONCEPT_ASSERT((concept::structure::Switch<switch_type>));
      typedef concept::structure::switch_traits<switch_type> switch_traits;

      typedef typename switch_traits::context_range context_value_range;
      typedef typename gntl::unwrap_parameter<context_value_range>::type context_range;
      typedef typename boost::range_iterator<context_range>::type context_iterator;
      context_value_range contexts = switch_traits::context_all(*first);
      for(context_iterator cfirst = boost::begin(contexts), clast = boost::end(contexts)
            ;cfirst != clast; ++cfirst)
      {
        result_type r = lookup_aux(gntl::ref(*cfirst), key);
        if(r != result_type(boost::none))
          return r;
      }
    }

    return result_type(boost::none);
  }                                
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
