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

#ifndef GNTL_STRUCTURE_NEW_INSTANCE_REUSED_CONTEXT_HPP
#define GNTL_STRUCTURE_NEW_INSTANCE_REUSED_CONTEXT_HPP

#include <gntl/concept/structure/context.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure {

template <typename Context, typename ReusedContext>
struct new_instance_reused_context
{
  Context context;
  ReusedContext reused_context;

  new_instance_reused_context(Context context, ReusedContext reused_context)
    : context(context), reused_context(reused_context)
  {}
};

}

namespace concept { namespace structure {

template <typename Context, typename ReusedContext>
struct context_traits<gntl::structure::new_instance_reused_context<Context, ReusedContext> >
{
  typedef boost::mpl::true_ is_context;
  typedef structure::context_traits<typename unwrap_parameter<Context>::type> structure_context_traits;
  typedef structure::context_traits<typename unwrap_parameter<ReusedContext>::type> reused_context_traits;

  typedef gntl::structure::new_instance_reused_context<Context, ReusedContext> context_type;
  typedef typename structure_context_traits::identifier_type identifier_type;
  typedef typename reused_context_traits::port_range port_range;
  typedef typename reused_context_traits::media_const_range media_const_range;
  typedef typename reused_context_traits::media_range media_range;
  typedef typename reused_context_traits::context_range context_range;
  typedef typename reused_context_traits::link_range link_range;
  typedef typename reused_context_traits::switch_range switch_range;
  typedef typename reused_context_traits::media_lookupable media_lookupable;
  typedef typename reused_context_traits::context_lookupable context_lookupable;
  typedef typename reused_context_traits::switch_lookupable switch_lookupable;
  typedef typename reused_context_traits::port_lookupable port_lookupable;
  typedef typename reused_context_traits::refer_type refer_type;
  
  static identifier_type identifier(context_type const& c)
  {
    return structure_context_traits::identifier(c.context);
  }
  static port_range port_all(context_type& c)
  {
    return reused_context_traits::port_all(c.reused_context);
  }
  static media_const_range media_all(context_type const& c)
  {
    return reused_context_traits::media_all(c.reused_context);
  }
  static media_range media_all(context_type& c)
  {
    return reused_context_traits::media_all(c.reused_context);
  }
  static port_lookupable port_lookup(context_type& c)
  {
    return reused_context_traits::port_lookup(c.reused_context);
  }
  static media_lookupable media_lookup(context_type& c)
  {
    return reused_context_traits::media_lookup(c.reused_context);
  }
  static context_lookupable context_lookup(context_type& c)
  {
    return reused_context_traits::context_lookup(c.reused_context);
  }
  static switch_lookupable switch_lookup(context_type& c)
  {
    return reused_context_traits::switch_lookup(c.reused_context);
  }
  static context_range context_all(context_type& c)
  {
    return reused_context_traits::context_all(c.reused_context);
  }
  static switch_range switch_all(context_type& c)
  {
    return reused_context_traits::switch_all(c.reused_context);
  }
  static link_range link_all(context_type& c)
  {
    return reused_context_traits::link_all(c.reused_context);
  }
  static bool is_presentation_occurring(context_type const& c)
  {
    return reused_context_traits::is_presentation_occurring(c.reused_context);
  }
  static bool is_presentation_paused(context_type const& c)
  {
    return reused_context_traits::is_presentation_paused(c.reused_context);
  }
  static bool is_presentation_sleeping(context_type const& c)
  {
    return reused_context_traits::is_presentation_sleeping(c.reused_context);
  }
  static bool has_refer(context_type const& c)
  {
    return reused_context_traits::has_refer(c.reused_context);
  }
  static refer_type refer(context_type const& c)
  {
    return reused_context_traits::refer(c.reused_context);
  }
};

} } }



#include <gntl/detail/pop_options.hpp>

#endif
