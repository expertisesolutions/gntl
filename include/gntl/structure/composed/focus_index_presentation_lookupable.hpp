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

#ifndef GNTL_STRUCTURE_COMPOSED_FOCUS_INDEX_PRESENTATION_LOOKUPABLE_HPP
#define GNTL_STRUCTURE_COMPOSED_FOCUS_INDEX_PRESENTATION_LOOKUPABLE_HPP

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
struct focus_index_presentation_lookupable
{
  focus_index_presentation_lookupable() {}
  focus_index_presentation_lookupable(Context body, ContextRange contexts)
    :  body(body), contexts(contexts) {}

  Context body;
  ContextRange contexts;
};

} }

namespace concept {

template <typename Context, typename ContextRange>
struct lookupable_traits<gntl::structure::composed::focus_index_presentation_lookupable
                         <Context, ContextRange> >
{
  typedef boost::mpl::true_ is_lookupable;
  typedef gntl::structure::composed::focus_index_presentation_lookupable<Context, ContextRange>
    presentation_lookupable;

  typedef typename boost::range_value<ContextRange>::type context_range_value_type;
  typedef typename unwrap_parameter<Context>::type context_type;
  typedef typename unwrap_parameter<context_range_value_type>::type context_type_from_range;

  typedef typename concept::structure::context_traits<context_type>::media_range first_media_range;
  typedef typename boost::range_value<first_media_range>::type first_media_range_value_type;
  typedef typename unwrap_parameter<first_media_range_value_type>::type first_media_type;
  typedef typename concept::structure::media_traits<first_media_type>::descriptor_type descriptor_type;
  typedef typename concept::structure::descriptor_traits<descriptor_type>::focus_index_type key_type;

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
  struct context_to_media_presentation_pair
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    typedef concept::structure::context_traits<context_type> traits;
    typedef typename traits::media_range media_range;
    typedef typename boost::range_value<media_range>::type media_range_value_type;
    typedef typename unwrap_parameter<media_range_value_type>::type media_type;
    typedef typename concept::structure::media_traits<media_type> media_traits;
    typedef typename media_traits::presentation_type presentation_type;
    typedef 
    std::pair<gntl::reference_wrapper<media_type>
              , gntl::reference_wrapper<presentation_type> > type;
  };

  typedef typename boost::mpl::transform<context_types, context_to_media_presentation_pair<boost::mpl::_> >::type
    presentation_from_context_types;
  typedef typename boost::mpl::unique<presentation_from_context_types
                                      , boost::is_same<boost::mpl::_, boost::mpl::_>
                                      >::type presentation_types;
  typedef typename boost::mpl::if_
    <
     boost::mpl::equal_to
     <
       typename boost::mpl::size<presentation_types>::type
       , boost::mpl::int_<1>
     >
     , typename boost::mpl::deref<typename boost::mpl::begin<presentation_types>::type>::type
     , typename boost::make_variant_over<presentation_types>::type
    >::type unit_value_type;
  typedef std::vector<unit_value_type> value_type;

  struct result_type
  {
    value_type r;
    result_type () {}
    result_type(value_type r) : r(r) {}
    value_type operator*() const { return r; }
    bool operator==(result_type const& other) { return r.empty () && other.r.empty (); }
    bool operator!=(result_type const& other) { return !(*this == other); }
    
    typedef bool(result_type::*bool_type)(result_type const&);
    operator bool_type() const
    {
      bool_type false_ = 0;
      return !r.empty ()?&result_type::operator== : false_;
    }

    void append (result_type const& other)
    {
      r.insert(r.end (), other.r.begin (), other.r.end ());
    }
  };

  template <typename Key>
  static result_type lookup(presentation_lookupable l, Key key)
  {
    result_type r;
    if(result_type other_r = lookup_aux(l.body, key))
      r.append(other_r);

    typedef typename unwrap_parameter<ContextRange>::type context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;
    for(context_iterator first = boost::begin(l.contexts), last = boost::end(l.contexts)
          ;first != last; ++first)
    {
      if(result_type other_r = lookup_aux(gntl::ref_once(*first), key))
        r.append(other_r);
    }
    return r;
  }

  static result_type not_found(presentation_lookupable l)
  {
    return result_type();
  }

private:
  template <typename CurrentContext, typename Key>
  static result_type lookup_aux(CurrentContext c, Key key)
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    GNTL_CONCEPT_ASSERT((concept::structure::Context<context_type>));
    typedef concept::structure::context_traits<context_type> context_traits;
    typedef typename context_traits::media_range media_range;
    typedef typename boost::range_iterator<media_range>::type media_iterator;

    result_type r;

    media_range medias = context_traits::media_all(c);
    
    for(media_iterator media_first = boost::begin(medias), last = boost::end(medias)
          ;media_first != last;++media_first)
    {
      typedef typename boost::range_value<media_range>::type media_range_value_type;
      typedef typename unwrap_parameter<media_range_value_type>::type media_type;
      typedef concept::structure::media_traits<media_type> media_traits;
      typedef typename media_traits::presentation_range presentation_range;
      presentation_range presentations = media_traits::presentation_all(*media_first);
      typedef typename boost::range_iterator<presentation_range>::type presentation_iterator;
      for(presentation_iterator first = boost::begin(presentations), last = boost::end(presentations)
            ;first != last;++first)
      {
        typedef typename boost::range_value<presentation_range>::type presentation_range_value_type;
        typedef typename unwrap_parameter<presentation_range_value_type>::type presentation_type;
        typedef concept::structure::presentation_traits<presentation_type> presentation_traits;
        typedef typename presentation_traits::descriptor_type descriptor_type;
        typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
        descriptor_type descriptor = presentation_traits::current_descriptor(*first);
        if(descriptor_traits::has_focus_index(descriptor)
           && descriptor_traits::focus_index(descriptor) == key)
        {
          std::vector<unit_value_type> v;
          v.push_back(std::make_pair(gntl::ref_once(*media_first), gntl::ref_once(*first)));
          r.append(v);
        }
      }
      
    }

    typedef typename context_traits::context_range context_range;
    typedef typename boost::range_iterator<context_range>::type context_iterator;

    context_range contexts = context_traits::context_all(c);

    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last;++first)
    {
      if(result_type other_r = lookup_aux(gntl::ref_once(*first), key))
        r.append(other_r);
    }

    return r;
  }                                
};

} }


#include <gntl/detail/pop_options.hpp>

#endif
