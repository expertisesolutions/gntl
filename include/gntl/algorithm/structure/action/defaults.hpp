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

#ifndef GNTL_ALGORITHM_STRUCTURE_ACTION_DEFAULTS_HPP
#define GNTL_ALGORITHM_STRUCTURE_ACTION_DEFAULTS_HPP

#include <gntl/event_enum.hpp>
#include <gntl/action_enum.hpp>

#include <utility>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace action {

template <typename EventType, typename Action, typename Role>
boost::optional<std::pair<EventType, Action> >
default_from_role(Role r)
{
  if(r == "start")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::action_enum::start);
  else if(r == "stop")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::action_enum::stop);
  else if(r == "abort")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::action_enum::abort);
  else if(r == "pause")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::action_enum::pause);
  else if(r == "resume")
    return std::make_pair(gntl::event_enum::presentation
                          , gntl::action_enum::resume);
  else if(r == "set")
    return std::make_pair(gntl::event_enum::attribution
                          , gntl::action_enum::start);
  else
    return boost::none;
}

template <typename EventType, typename Action>
boost::optional<const char*> role_from_event_action(EventType e, Action t)
{
  switch(e)
  {
  case gntl::event_enum::presentation:
    switch(t)
    {
    case gntl::action_enum::start:
      return "start";
    case gntl::action_enum::stop:
      return "stop";
    case gntl::action_enum::abort:
      return "abort";
    case gntl::action_enum::pause:
      return "pause";
    case gntl::action_enum::resume:
      return "resume";
    default:
      break;
    }
    break;
  case gntl::event_enum::attribution:
    switch(t)
    {
    case gntl::action_enum::start:
      return "set";
    default:
      break;
    }
  default:
    break;
  }
  return boost::none;
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif

