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

#ifndef GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_ACTION_TRAITS_IPP
#define GNTL_ALGORITHM_STRUCTURE_MEDIA_NATURAL_END_ACTION_TRAITS_IPP

#include <gntl/algorithm/structure/document/register_event.hpp>
#include <gntl/algorithm/structure/media/natural_end_action_traits.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace algorithm { namespace structure { namespace media {

template <typename Media, typename Presentation, typename Document, typename...Args>
void natural_end_action_traits::natural_end(Media m, Presentation presentation, Document document, Args&& ...args)
{
    typedef typename boost::unwrap_reference<Media>::type media_type;
    typedef typename boost::unwrap_reference<Presentation>::type presentation_type;
    typedef typename boost::unwrap_reference<Document>::type document_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    typedef concept::structure::document_traits<document_type> document_traits;
    typedef concept::structure::presentation_traits<presentation_type> presentation_traits;

    bool focused = presentation_traits::is_focused(presentation);

    presentation_traits::reset_focus(presentation);
    presentation_traits::reset_selection(presentation);
    presentation_traits::remove_border(presentation, args...);

    presentation_traits::natural_end (presentation);

    if(focused)
    {
        GNTL_DEBUG_LOG("this media is focused" << std::endl)
        typedef typename presentation_traits::descriptor_type descriptor_type;
        descriptor_type descriptor = presentation_traits::current_descriptor(presentation);
        typedef concept::structure::descriptor_traits<descriptor_type> descriptor_traits;
        typedef typename descriptor_traits::focus_index_type focus_index_type;
        assert(descriptor_traits::has_focus_index(descriptor));
        focus_index_type current_focus = descriptor_traits::focus_index(descriptor);
        typedef typename document_traits::focus_index_presentation_lookupable presentation_lookupable;
        presentation_lookupable lookupable = document_traits::focus_index_presentation_lookup(document);
        typedef concept::lookupable_traits<presentation_lookupable> lookupable_traits;
        typedef typename lookupable_traits::result_type lookup_result;
        lookup_result r = lookupable_traits::lookup(lookupable, current_focus); // unnecessary lookup
        do
        {
            --current_focus;
            r = lookupable_traits::lookup(lookupable, current_focus);
        } while(current_focus >= 0 && r == lookupable_traits::not_found (lookupable));

        if(current_focus >= 0) // found
        {
            typedef typename lookupable_traits::value_type lookup_value_type;
            lookup_value_type v = *r;
            typedef typename lookup_value_type::value_type value_type;
            typedef typename lookup_value_type::const_iterator iterator;
            for(iterator first = v.begin (), last = v.end (); first != last; ++first)
            {
                typedef typename unwrap_parameter<value_type>::type pair_type;
                typedef typename pair_type::second_type presentation_pair_type;
                typedef typename unwrap_parameter<presentation_pair_type>::type presentation_type;
                typedef concept::structure::presentation_traits<presentation_type>
                        presentation_traits;
                if(presentation_traits::is_occurring(first->second))
                {
                    typedef typename presentation_traits::descriptor_type descriptor_type;
                    typedef concept::structure::descriptor_traits<descriptor_type>
                            descriptor_traits;
                    typedef typename descriptor_traits::width_type width_type;
                    typedef typename descriptor_traits::color_type color_type;
                    descriptor_type descriptor = presentation_traits::current_descriptor
                            (first->second);
                    std::pair<width_type, color_type>
                            c = media::calculate_focused_border (first->second, descriptor
                            , presentation_traits
                                                                 ::is_selected(first->second));
                    presentation_traits::add_border (first->second, c.first, c.second, args...);
                    presentation_traits::focused(first->second);
                    structure::document::set_focus(document, first->first, descriptor);
                    break;
                }
            }
        }
    }

    boost::optional<typename document_traits::component_identifier> interface_;
    algorithm::structure::document::register_event (document, m, interface_
    , gntl::transition_enum::stops
    , gntl::event_enum::presentation);
}

} } } }

#include <gntl/detail/pop_options.hpp>

#endif
