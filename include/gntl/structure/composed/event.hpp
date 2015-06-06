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

#ifndef GNTL_STRUCTURE_COMPOSED_EVENT_HPP
#define GNTL_STRUCTURE_COMPOSED_EVENT_HPP

#include <gntl/event_enum.hpp>
#include <gntl/transition_enum.hpp>

#include <boost/optional.hpp>

#include <string>
#include <iosfwd>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

struct event
{
  std::string component_identifier;
  boost::optional<std::string> interface_;
  transition_type transition;
  gntl::event_type event_;

  template <typename String, typename OptionalString>
  event(String const& component_identifier
        , OptionalString const& interface_
        , transition_type transition
        , gntl::event_type event)
    : component_identifier(component_identifier.begin(), component_identifier.end())
    , transition(transition)
    , event_(event)
  {
    if(interface_)
      {
        this->interface_ = std::string(interface_->begin(), interface_->end());
      }
  }

  template <typename OptionalString>
  event(std::string const& component_identifier
        , OptionalString const& interface_
        , transition_type transition
        , gntl::event_type event)
    : component_identifier(component_identifier)
    , transition(transition)
    , event_(event)
  {
    if(interface_)
      {
        this->interface_ = std::string(interface_->begin(), interface_->end());
      }
  }

  template <typename String>
  event(std::string const& component_identifier
        , boost::optional<String> const& interface_
        , transition_type transition
        , gntl::event_type event)
    : component_identifier(component_identifier)
    , transition(transition)
    , event_(event)
  {
    if(interface_)
      {
        this->interface_ = std::string(interface_->begin(), interface_->end());
      }
  }

  event(std::string const& component_identifier
        , boost::optional<std::string> const& interface_
        , transition_type transition
        , gntl::event_type event)
    : component_identifier(component_identifier)
    , interface_(interface_)
    , transition(transition)
    , event_(event)
  {
  }
};

inline std::ostream& operator<<(std::ostream& os, event e)
{
  os << "[identifier: " << e.component_identifier
     << " interface: ";
  if(e.interface_)
    os << *e.interface_;
  else
    os << "{none}";
  os << " transition: " << e.transition << " event: " << e.event_ << "]";

  return os;
}

} } }


#include <gntl/detail/pop_options.hpp>

#endif
