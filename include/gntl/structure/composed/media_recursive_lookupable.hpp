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

#ifndef GNTL_STRUCTURE_COMPOSED_MEDIA_RECURSIVE_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_MEDIA_RECURSIVE_LOOKUPABLE_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/parameter.hpp>

#include <boost/mpl/contains.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/transform.hpp>

#include <boost/variant.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename Context, typename ContextRange>
struct media_recursive_lookupable
{
  media_recursive_lookupable() {}
  media_recursive_lookupable(Context body, ContextRange contexts)
    :  body(body), contexts(contexts) {}

  Context body;
  ContextRange contexts;
};

} }

namespace concept {

template <typename Context, typename ContextRange>
struct lookupable_traits<gntl::structure::composed::media_recursive_lookupable
                         <Context, ContextRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::media_recursive_lookupable<Context, ContextRange>
    media_lookupable;
  typedef std::string key_type;

  typedef typename boost::range_value<ContextRange>::type context_range_value_type;
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename unwrap_parameter<context_range_value_type>::type context_type_from_range;

  template <typename CurrentContext, typename List>
  struct get_context_types
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    typedef concept::structure::context_traits<context_type> traits;
    typedef typename traits::context_range context_range;
    typedef typename boost::range_value<context_range>::type context_inner_value_type;
    typedef typename unwrap_parameter<context_inner_value_type>::type context_inner_type;
    typedef typename boost::mpl::push_back<List, context_type>::type new_list;
    typedef typename boost::mpl::eval_if
      <boost::mpl::contains<new_list, context_inner_type>
       , boost::mpl::identity<new_list>
       , get_context_types<context_inner_type, new_list>
       >::type type;
  };

  typedef typename get_context_types<context_type, boost::mpl::vector0<> >::type context_types_from_body;
  typedef typename get_context_types<context_type_from_range, context_types_from_body>::type context_types;
  
  template <typename CurrentContext>
  struct context_to_media
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    typedef concept::structure::context_traits<context_type> traits;
    typedef typename traits::media_range media_range;
    typedef gntl::reference_wrapper<typename boost::range_value<media_range>::type> type;
  };

  typedef typename boost::mpl::transform<context_types, context_to_media<boost::mpl::_> >::type
    media_from_context_types;
  typedef typename boost::mpl::unique<media_from_context_types
                                      , boost::is_same<boost::mpl::_, boost::mpl::_>
                                      >::type media_types;
  typedef typename boost::mpl::if_
    <
     boost::mpl::equal_to
     <
       typename boost::mpl::size<media_types>::type
       , boost::mpl::int_<1>
     >
     , typename boost::mpl::deref<typename boost::mpl::begin<media_types>::type>::type
     , typename boost::make_variant_over<media_types>::type
    >::type value_type;

  BOOST_MPL_ASSERT((boost::mpl::if_
                    <
                      typename boost::mpl::equal_to
                      <
                        typename boost::mpl::size<media_types>::type
                        , boost::mpl::int_<1>
                      >::type
                    , boost::is_reference_wrapper
                      <
                        typename boost::mpl::deref
                        <
                          typename boost::mpl::begin
                          <media_types>::type
                        >::type
                      >
                    , boost::mpl::true_
                    >));

  struct result_type
  {
    boost::optional<value_type> r;
    result_type(boost::optional<value_type> r) : r(r) {}
    value_type operator*() const { return *r; }
    bool operator==(result_type const& other) const { return (r && other.r) || (!r && !other.r); }
    bool operator!=(result_type const& other) const { return !(*this == other); }
  };

  static result_type lookup(media_lookupable l, key_type key)
  {
    result_type r = lookup_aux(l.body, key);
    if(r != not_found(l))
      return r;
    else
    {
      typedef typename unwrap_parameter<ContextRange>::type context_range;
      typedef typename boost::range_iterator<context_range>::type context_iterator;
      for(context_iterator first = boost::begin(l.contexts), last = boost::end(l.contexts)
            ;first != last; ++first)
      {
        result_type r = lookup_aux(gntl::ref_once(*first), key);
        if(r != not_found(l))
          return r;
      }
      return result_type(boost::none);
    }
  }

  static result_type not_found(media_lookupable l)
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
    typedef typename context_traits::media_range media_range;
    typedef typename boost::range_iterator<media_range>::type media_iterator;

    media_range medias = context_traits::media_all(c);
    
    for(media_iterator first = boost::begin(medias), last = boost::end(medias)
          ;first != last;++first)
    {
      typedef typename boost::range_value<media_range>::type media_range_value_type;
      typedef typename unwrap_parameter<media_range_value_type>::type media_type;
      typedef concept::structure::media_traits<media_type> media_traits;
      if(media_traits::identifier(*first) == key)
        return result_type(gntl::ref_once(*first));
    }

    typedef typename context_traits::context_range context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;

    context_range contexts = context_traits::context_all(c);

    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last;++first)
    {
      result_type r = lookup_aux(gntl::ref(*first), key);
      if(r != result_type(boost::none))
        return r;
    }

    return result_type(boost::none);
  }                                
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
