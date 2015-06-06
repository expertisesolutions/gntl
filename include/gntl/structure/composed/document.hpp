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

#ifndef GNTL_STRUCTURE_COMPOSED_DOCUMENT_HPP
#define GNTL_STRUCTURE_COMPOSED_DOCUMENT_HPP

#include <gntl/concept/lookupable.hpp>
#include <gntl/concept/structure/document.hpp>
#include <gntl/concept/parser/document/document.hpp>
#include <gntl/algorithm/structure/property_container.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/event.hpp>
#include <gntl/structure/composed/document_lookupable.hpp>
#include <gntl/structure/composed/context_recursive_lookupable.hpp>
#include <gntl/structure/composed/media_recursive_lookupable.hpp>
#include <gntl/structure/composed/switch_recursive_lookupable.hpp>
#include <gntl/structure/composed/focus_index_presentation_lookupable.hpp>
#include <gntl/structure/composed/descriptor.hpp>
#include <gntl/structure/composed/descriptor_lookupable.hpp>
#include <gntl/structure/composed/causal_connector_lookupable.hpp>
#include <gntl/structure/composed/component_location.hpp>
#include <gntl/structure/composed/region_lookupable.hpp>
#include <gntl/structure/composed/context.hpp>
#include <gntl/structure/composed/property_container.hpp>
#include <gntl/structure/composed/rule_lookupable.hpp>
#include <gntl/event_enum.hpp>
#include <gntl/transition_enum.hpp>
#include <gntl/parameter.hpp>
#include <gntl/range.hpp>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/optional.hpp>
#include <boost/none.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/range/distance.hpp>
#include <boost/mpl/assert.hpp>

#include <vector>
#include <stack>
#include <map>

#include <gntl/detail/push_options.hpp>

namespace gntl { namespace structure { namespace composed {

template <typename ParserDocument, typename PresentationFactory, typename DocumentURI>
struct document
{
  GNTL_CONCEPT_ASSERT((concept::parser::Document<ParserDocument>));
  typedef document<ParserDocument, PresentationFactory, DocumentURI> self_type;
  typedef typename unwrap_parameter<ParserDocument>::type parser_document_type;
  typedef concept::parser::document_traits<parser_document_type> parser_document_traits;
  typedef typename parser_document_traits::body_type parser_document_body_type;
  typedef typename parser_document_traits::head_type parser_document_head_type;
  typedef typename unwrap_parameter<parser_document_body_type>::type parser_body_type;
  typedef typename unwrap_parameter<parser_document_head_type>::type parser_head_type;
  typedef concept::parser::body_traits<parser_body_type> parser_body_traits;
  typedef concept::parser::head_traits<parser_head_type> parser_head_traits;
  typedef DocumentURI document_uri_type;
  typedef composed::component_location<std::string, DocumentURI> component_location_type;

  typedef typename parser_body_traits::context_type parser_context_type;
  typedef typename parser_head_traits::descriptor_base_type parser_descriptor_base_value_type;

  typedef typename parser_head_traits::connector_base_type parser_connector_base_value_type;
  typedef typename unwrap_parameter<parser_connector_base_value_type>::type parser_connector_base_type;
  // typedef concept::parser::connector_base_traits<parser_connector_base_type> parser_connector_base_traits;
  // typedef typename parser_connector_base_traits::causal_connector_range parser_causal_connector_range_value_type; 
  // typedef typename unwrap_parameter<parser_causal_connector_range_value_type>::type parser_causal_connector_range;
  // typedef typename boost::range_value<parser_causal_connector_range>::type parser_causal_connector_value_type;

  typedef composed::context<parser_context_type, PresentationFactory
                            , parser_connector_base_type> context_type;

  typedef typename parser_head_traits::region_base_range region_base_range_value_type;

  template <typename Media>
  void set_settings_media_found (Media media)
  {
    typedef typename unwrap_parameter<Media>::type media_type;
    typedef concept::structure::media_traits<media_type> media_traits;
    global_properties_media = media_traits::identifier(media);

    algorithm::structure::property_container::initialize_from_structure_media
      (properties, gntl::ref(*this), media);
  }

  template <typename CurrentContext>
  bool set_settings_media(CurrentContext context)
  {
    typedef typename unwrap_parameter<CurrentContext>::type context_type;
    typedef concept::structure::context_traits<context_type> context_traits;
    typedef typename context_traits::media_range media_range_value_type;
    typedef typename unwrap_parameter<media_range_value_type>::type media_range;
    media_range_value_type medias = context_traits::media_all(context);
    typedef typename boost::range_iterator<media_range>::type media_iterator;
    for(media_iterator first = boost::begin(medias), last = boost::end(medias)
          ;first != last;++first)
    {
      typedef typename boost::range_value<media_range>::type media_value_type;
      typedef typename unwrap_parameter<media_value_type>::type media_type;
      typedef concept::structure::media_traits<media_type> media_traits;
      if(media_traits::type(*first) == "application/x-ginga-settings")
      {
        GNTL_DEBUG_LOG("found global_properties_media " << media_traits::identifier(*first) << std::endl)
        set_settings_media_found (gntl::ref_once(*first));
        return true;
      }
    }

    typedef typename context_traits::context_range inner_context_range_value_type;
    typedef typename unwrap_parameter<inner_context_range_value_type>::type inner_context_range;
    inner_context_range contexts = context_traits::context_all(context);
    typedef typename boost::range_iterator<inner_context_range>::type context_iterator;
    for(context_iterator first = boost::begin(contexts), last = boost::end(contexts)
          ;first != last; ++first)
    {
      if(set_settings_media(*first))
        return true;
    }

    return false;
  }

  typedef std::map<DocumentURI, self_type> import_documents_map_type;
  document (ParserDocument parser_document
            , std::string document_uri = std::string()
            , PresentationFactory presentation_factory = PresentationFactory()
            , std::map<DocumentURI, self_type> documents = import_documents_map_type())
    : parser_document(parser_document)
    , document_uri(document_uri)
    , documents(documents)
    , body(parser_body_traits::context
           (parser_document_traits::body(this->parser_document))
           , get_causal_connector_lookupable(), presentation_factory)
  {
    static const char* current_focus_string = "service.currentFocus";
    static const char* current_key_master_string = "service.currentKeyMaster";

    required_properties_names.insert(current_focus_string);
    required_properties_names.insert(current_key_master_string);

    if(!set_settings_media(gntl::ref_once(body)))
    {
      GNTL_DEBUG_LOG("not found settings media" << std::endl)
    }
  }

  document ()
    : parser_document()
    , document_uri()
    , documents()
  {
    static const char* current_focus_string = "service.currentFocus";
    static const char* current_key_master_string = "service.currentKeyMaster";

    required_properties_names.insert(current_focus_string);
    required_properties_names.insert(current_key_master_string);

    if(!set_settings_media(gntl::ref_once(body)))
    {
      GNTL_DEBUG_LOG("not found settings media" << std::endl)
    }
  }

  typedef composed::descriptor_lookupable<parser_descriptor_base_value_type, DocumentURI> descriptor_lookupable;
  typedef composed::region_lookupable<region_base_range_value_type> region_lookupable;
  typedef boost::iterator_range<context_type*> imported_context_range;

  typedef typename parser_head_traits::import_document_base_type import_document_base_type;

  typedef composed::context_recursive_lookupable<gntl::reference_wrapper<context_type>, DocumentURI> context_lookupable;
  typedef composed::media_recursive_lookupable<gntl::reference_wrapper<context_type>, imported_context_range>
    media_lookupable;
  typedef composed::switch_recursive_lookupable<gntl::reference_wrapper<context_type>, imported_context_range>
    switch_lookupable;
  typedef composed::causal_connector_lookupable<parser_connector_base_value_type>
    causal_connector_lookupable;
  typedef composed::focus_index_presentation_lookupable<gntl::reference_wrapper<context_type>, imported_context_range>
    focus_index_presentation_lookupable;
  typedef typename parser_head_traits::rule_base_type rule_base_value_type;
  typedef typename unwrap_parameter<rule_base_value_type>::type rule_base_type;
  typedef concept::parser::rule_base_traits<rule_base_type> rule_base_traits;
  typedef typename rule_base_traits::rule_range rule_range;
  typedef composed::rule_lookupable<rule_range> rule_lookupable;

  causal_connector_lookupable get_causal_connector_lookupable()
  {
    GNTL_DEBUG_LOG("document::get_causal_connector_lookupable " << std::endl)
    typename causal_connector_lookupable::aliased_connector_bases_map map;
    typedef typename parser_document_traits::head_type head_value_type;
    head_value_type head = parser_document_traits::head(parser_document);
    if(parser_head_traits::has_connector_base(head))
    {
      GNTL_DEBUG_LOG("parser_document has connector_base" << std::endl)
      typedef typename parser_head_traits::connector_base_type connector_base_value_type;
      connector_base_value_type connector_base = parser_head_traits::connector_base(head);

      typedef typename unwrap_parameter<connector_base_value_type>::type connector_base_type;
      typedef concept::parser::connector_base_traits<connector_base_type> connector_base_traits;
      typedef typename connector_base_traits::import_base_range import_base_range_value_type;
      import_base_range_value_type import_bases = connector_base_traits::import_base_all(connector_base);
      typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
      typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
      for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
            ;first != last;++first)
      {
        typedef typename boost::range_value<import_base_range>::type import_base_value_type;
        typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;
        typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
        GNTL_DEBUG_LOG("searching document_uri " << import_base_traits::document_uri(*first) << std::endl)
        typename std::map<DocumentURI, self_type>::iterator 
          iterator = documents.find(import_base_traits::document_uri(*first));
        if(iterator != documents.end())
        {
          GNTL_DEBUG_LOG("found, adding its connector_base" << std::endl)
          if(parser_head_traits::has_connector_base
             (parser_document_traits::head(iterator->second.parser_document)))
          {
            map.insert(std::make_pair(import_base_traits::alias(*first)
                                      , parser_head_traits::connector_base
                                      (parser_document_traits::head(iterator->second.parser_document))));
          }
          else
            GNTL_DEBUG_LOG("doesnt have any connector_base" << std::endl)
        }          
      }        

      return causal_connector_lookupable(connector_base, map);
    }
    else
      return causal_connector_lookupable();
  }

  typedef event event_type;

  // required properties
  boost::optional<int> focus_index, next_focus_index;
  std::string focus_media;
  std::string current_key_master_media, next_current_key_master_media;

  struct cstring_less
  {
    typedef bool result_type;
    result_type operator()(const char* lhs, const char* rhs)
    {
      return std::strcmp(lhs, rhs) < 0;
    }
  };
  typedef std::set<const char*, cstring_less> required_properties_names_container;
  required_properties_names_container required_properties_names;
  typedef composed::property<std::string, int, double> property_type;

  enum
  {
    current_focus_name
    , current_key_master_name 
  };

  struct required_properties
  {
    typedef typename required_properties_names_container::const_iterator required_properties_names_iterator;
    struct iterator : boost::iterator_facade<iterator, property_type, boost::forward_traversal_tag
                                             , property_type>
    {
      iterator(required_properties_names_iterator begin, required_properties_names_iterator base
               , self_type const& document)
        : begin(begin), base(base), document(&document) {}

      void increment()
      {
        ++base;
      }
      property_type dereference() const
      {
        switch(std::distance(begin, base))
        {
        case current_focus_name:
        {
          if(this->document->focus_index)
            return property_type(*base, *document->focus_index);
          else
            return property_type(*base);
        }
        case current_key_master_name:
        {
          return property_type(*base, document->current_key_master_media);
        }
        default:
          std::abort();
          throw -1;
        };
      }
      bool equal(iterator const& other) const
      {
        return base == other.base;
      }

      required_properties_names_iterator begin, base;
      self_type const* document;
    };

    typedef iterator const_iterator;

    static iterator begin(self_type const& document)
    {
      return iterator(document.required_properties_names.begin(), document.required_properties_names.begin()
                      , document);
    }
    static iterator end(self_type const& document)
    {
      return iterator(document.required_properties_names.begin(), document.required_properties_names.end()
                      , document);
    }
    static iterator find(self_type const& document, std::string name)
    {
      std::pair<required_properties_names_iterator
                , required_properties_names_iterator> equal = std::equal_range
        (document.required_properties_names.begin(), document.required_properties_names.end()
         , name.c_str(), cstring_less());
      return iterator(document.required_properties_names.begin()
                      , equal.first == equal.second?document.required_properties_names.end():equal.first
                      , document);
    }
    struct set_next_current_key_master
    {
      typedef void result_type;
      result_type operator()(self_type& document, std::string const& v) const
      {
        GNTL_DEBUG_LOG("set_next_current_key_master " << v << std::endl)
        if(!document.next_current_key_master_media.empty())
          GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                 , (typename error::reason<const char*>::type
                                    ("Trying to set a property being set")));
        document.next_current_key_master_media = v;
      }
      template <typename T>
      result_type operator()(self_type& document, T const& v) const
      {
        std::stringstream s;
        s << v;
        document.next_current_key_master_media = s.str();
      }
    };
    struct set_next_focus_index
    {
      typedef void result_type;
      result_type operator()(self_type& document, int i) const
      {
        GNTL_DEBUG_LOG("set_next_focus_index " << i << std::endl)
        if(!!document.next_focus_index)
          GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                 , (typename error::reason<const char*>::type
                                    ("Trying to set a property being set")));
        document.next_focus_index = i;
      }
      template <typename T>
      result_type operator()(self_type& document, T const& value) const
      {
        GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                               , (typename error::reason<const char*>::type
                                  ("service.currentFocus can be set only with a integer value or an empty string"))
                                 (typename error::property_value<T>::type(value))
                                 (typename error::property_name<const char*>::type("service.currentFocus")));
      }
      result_type operator()(self_type& document, std::string const& s) const
      {
        if(!s.empty())
          GNTL_UNWIND_ERROR_INFO(gntl::invalid_ncl_error()
                                 , (typename error::reason<const char*>::type
                                    ("service.currentFocus can't be set with a non-empty string"))
                                   (typename error::property_value<std::string>::type(s))
                                   (typename error::property_name<const char*>::type("service.currentFocus")));
      }
    };

    template <typename Value>
    static void start_set(self_type& document, std::string name, Value v)
    {
      GNTL_DEBUG_LOG("Setting document property: " << name << " with value " << v << std::endl)
      std::pair<required_properties_names_iterator
                , required_properties_names_iterator> equal = std::equal_range
        (document.required_properties_names.begin(), document.required_properties_names.end()
         , name.c_str(), cstring_less());
      assert(equal.first != equal.second);
      switch(std::distance(document.required_properties_names.begin(), equal.first))
      {
      case current_focus_name:
        {
          GNTL_DEBUG_LOG("should set focus index" << std::endl)
          set_next_focus_index()(document, v);
          break;
        }
      case current_key_master_name:
        {
          GNTL_DEBUG_LOG("set current key master " << v << std::endl)
          set_next_current_key_master()(document, v);
          break;
        }
      default:
        std::abort();
        throw - 1;
      }
    }
    static void commit_set(self_type& document, std::string name)
    {
      GNTL_DEBUG_LOG("Committing document property: " << name << std::endl)
      std::pair<required_properties_names_iterator
                , required_properties_names_iterator> equal = std::equal_range
        (document.required_properties_names.begin(), document.required_properties_names.end()
         , name.c_str(), cstring_less());
      assert(equal.first != equal.second);
      switch(std::distance(document.required_properties_names.begin(), equal.first))
      {
      case current_focus_name:
      {
        assert(!!document.next_focus_index);
        GNTL_DEBUG_LOG("commit focus_index " << *document.next_focus_index << std::endl)
        document.focus_index = document.next_focus_index;
        document.next_focus_index = boost::none;
        break;
      }
      case current_key_master_name:
      {
        GNTL_DEBUG_LOG("commit current_key_master " << document.next_current_key_master_media
                       << std::endl)
        document.current_key_master_media = document.next_current_key_master_media;
        document.next_current_key_master_media.clear();
        break;
      }
      default:
        std::abort();
        throw - 1;
      }
    }
  };
  typedef composed::property_container<std::string, int, double, required_properties> property_container;

  component_location_type body_location() const
  {
    typedef concept::structure::context_traits<context_type> context_traits;
    return component_location_type(context_traits::identifier(body), document_uri);
  }

  // Other things
  ParserDocument parser_document;
  std::stack<event_type> pending_events;
  property_container properties;
  std::string global_properties_media;
  std::string document_uri;
  std::map<DocumentURI, self_type> documents;
  context_type body;
};

} }

namespace concept { namespace structure {

template <typename ParserDocument, typename PresentationFactory, typename DocumentURI>
struct document_traits<gntl::structure::composed::document
                       <ParserDocument, PresentationFactory, DocumentURI> >
{
    typedef gntl::structure::composed::document<ParserDocument, PresentationFactory
                                                , DocumentURI> document_type;
    typedef boost::true_type is_document;
    typedef typename document_type::descriptor_lookupable descriptor_lookupable;
    typedef concept::lookupable_traits<descriptor_lookupable> descriptor_lookupable_traits;
    typedef typename descriptor_lookupable_traits::value_type descriptor_type;
    typedef typename document_type::region_lookupable region_lookupable;
    typedef concept::lookupable_traits<region_lookupable> region_lookupable_traits;
    typedef typename region_lookupable_traits::value_type region_lookupable_value_type;
    typedef typename boost::range_value<region_lookupable_value_type>::type region_type;
    typedef typename document_type::event_type event_type;
    typedef typename document_type::context_type body_type;
    typedef std::string component_identifier;
    typedef std::string property_name;
    typedef typename document_type::property_type property_type;
    typedef gntl::structure::composed::document_lookupable<document_type, std::string> document_lookupable;
    typedef typename document_type::parser_document_traits parser_document_traits;
    typedef typename document_type::parser_head_traits parser_head_traits;
    typedef typename document_type::causal_connector_lookupable causal_connector_lookupable;
    typedef typename parser_head_traits::descriptor_base_type descriptor_base_type;
    typedef typename parser_head_traits::region_base_range region_base_range;
    typedef typename parser_head_traits::connector_base_type connector_base_type;

    typedef typename document_type::document_uri_type document_uri_type;
    typedef typename document_type::context_lookupable context_lookupable;
    typedef typename document_type::media_lookupable media_lookupable;
    typedef typename document_type::switch_lookupable switch_lookupable;
    typedef typename document_type::focus_index_presentation_lookupable focus_index_presentation_lookupable;
    typedef typename document_type::rule_lookupable rule_lookupable;
    typedef typename document_type::component_location_type component_location_type;

    static component_location_type component_location(document_type const& d
                                                      , component_identifier identifier)
    {
      return component_location_type(identifier, d.document_uri);
    }
    static focus_index_presentation_lookupable focus_index_presentation_lookup(document_type& d)
    {
      body_type* p = 0;
      typedef typename document_type::imported_context_range imported_context_range;
      return focus_index_presentation_lookupable(gntl::ref(d.body), imported_context_range(p, p));
    }
    static media_lookupable media_lookup(document_type& d)
    {
      body_type* p = 0;
      typedef typename document_type::imported_context_range imported_context_range;
      return media_lookupable(gntl::ref(d.body), imported_context_range(p, p));
    }
    static switch_lookupable switch_lookup(document_type& d)
    {
      body_type* p = 0;
      typedef typename document_type::imported_context_range imported_context_range;
      return switch_lookupable(gntl::ref(d.body), imported_context_range(p, p));
    }
    static context_lookupable context_lookup(document_type& d)
    {
      typedef typename context_lookupable::aliased_context_lookupables_map aliased_context_lookupables_map;
      aliased_context_lookupables_map map;

      if(parser_head_traits::has_import_document_base(parser_document_traits::head(d.parser_document)))
      {
        typedef typename parser_head_traits::import_document_base_type import_document_base_value_type;
        import_document_base_value_type import_base
          = parser_head_traits::import_document_base
          (parser_document_traits::head(d.parser_document));

        typedef typename unwrap_parameter<import_document_base_value_type>::type import_document_base_type;
        typedef concept::parser::import_document_base_traits<import_document_base_type> import_document_base_traits;
        typedef typename import_document_base_traits::import_ncl_range import_ncl_value_range;
        import_ncl_value_range import_ncls = import_document_base_traits::import_ncl_all(import_base);
        typedef typename unwrap_parameter<import_ncl_value_range>::type import_ncl_range;
        typedef typename boost::range_iterator<import_ncl_range>::type import_ncl_iterator;

        GNTL_DEBUG_LOG("number of import_ncls "
                       << boost::distance(import_ncls) << std::endl)

        for(import_ncl_iterator first = boost::begin(import_ncls)
              , last = boost::end(import_ncls); first != last; ++first)
        {
          typedef typename boost::range_value<import_ncl_range>::type import_ncl_value_type;
          typedef typename unwrap_parameter<import_ncl_value_type>::type import_ncl_type;
          typedef concept::parser::import_ncl_traits<import_ncl_type> import_ncl_traits;
          typedef typename import_ncl_traits::document_uri_type document_uri_type;
          GNTL_DEBUG_LOG("Searching " << import_ncl_traits::document_uri(*first)
                         << " alias: " << import_ncl_traits::alias(*first) << std::endl)
          typename std::map<DocumentURI, document_type>::iterator 
            iterator = d.documents.find(import_ncl_traits::document_uri(*first));
          if(iterator != d.documents.end())
          {
            GNTL_DEBUG_LOG("Found document_uri" << std::endl)
            boost::shared_ptr<context_lookupable> lookupable
              (new context_lookupable(context_lookup(iterator->second)));
            map.insert(std::make_pair(import_ncl_traits::alias(*first)
                                      , std::make_pair
                                      (import_ncl_traits::document_uri(*first)
                                       , lookupable)));
          }
          else
            GNTL_DEBUG_LOG("Not found document_uri" << std::endl)
        }
      }

      return context_lookupable
        (gntl::ref(d.body), map);
    }
    static descriptor_lookupable descriptor_lookup (document_type& d)
    {
      typename descriptor_lookupable::aliased_descriptor_bases_map map;

      typedef typename parser_head_traits::descriptor_base_type descriptor_base_value_type;
      if(parser_head_traits::has_descriptor_base(parser_document_traits::head(d.parser_document)))
      {
        descriptor_base_value_type descriptor_base
          = parser_head_traits::descriptor_base(parser_document_traits::head(d.parser_document));
        typedef typename unwrap_parameter<descriptor_base_value_type>::type descriptor_base_type;
        typedef concept::parser::descriptor_base_traits<descriptor_base_type> descriptor_base_traits;
        typedef typename descriptor_base_traits::import_base_range import_base_range_value_type;
        import_base_range_value_type import_bases = descriptor_base_traits::import_base_all(descriptor_base);
        typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
        typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
        for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
              ;first != last;++first)
        {
          typedef typename boost::range_value<import_base_range>::type import_base_value_type;
          typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;
          typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
          typename std::map<DocumentURI, document_type>::iterator 
            iterator = d.documents.find(import_base_traits::document_uri(*first));
          if(iterator != d.documents.end())
          {
            if(parser_head_traits::has_descriptor_base
               (parser_document_traits::head(iterator->second.parser_document)))
            {
              map.insert(std::make_pair(import_base_traits::alias(*first)
                                        , std::make_pair
                                        (iterator->first
                                         , parser_head_traits::descriptor_base
                                         (parser_document_traits::head(iterator->second.parser_document)))));
            }
          }
        }
        
        return descriptor_lookupable
          (parser_head_traits::descriptor_base(parser_document_traits::head(d.parser_document))
           , d.document_uri, map);
      }
      else
      {
        return descriptor_lookupable();
      }
    }
    static rule_lookupable rule_lookup (document_type const& d)
    {
      typedef typename parser_head_traits::rule_base_type rule_base_value_type;
      typedef typename unwrap_parameter<rule_base_value_type>::type rule_base_type;
      typedef concept::parser::rule_base_traits<rule_base_type> rule_base_traits;

      return rule_lookupable(rule_base_traits::rule_all
                             (parser_head_traits::rule_base
                              (parser_document_traits::head(d.parser_document))));
    }

    static region_lookupable region_lookup (document_type& d)
    {
      typename region_lookupable::aliased_region_bases_map map;
      typedef typename parser_head_traits::region_base_range region_base_range_value_type;
      region_base_range_value_type region_bases
        = parser_head_traits::region_base_all(parser_document_traits::head(d.parser_document));
      typedef typename unwrap_parameter<region_base_range_value_type>::type region_base_range;
      typedef typename boost::range_iterator<region_base_range>::type region_base_iterator;
      for(region_base_iterator first = boost::begin(region_bases), last = boost::end(region_bases)
            ;first != last; ++first)
      {
        typedef typename boost::range_value<region_base_range>::type region_base_value_type;
        typedef typename unwrap_parameter<region_base_value_type>::type region_base_type;
        typedef concept::parser::region_base_traits<region_base_type> region_base_traits;
        typedef typename region_base_traits::import_base_range import_base_range_value_type;
        import_base_range_value_type import_bases = region_base_traits::import_base_all(*first);
        typedef typename unwrap_parameter<import_base_range_value_type>::type import_base_range;
        typedef typename boost::range_iterator<import_base_range>::type import_base_iterator;
        for(import_base_iterator first = boost::begin(import_bases), last = boost::end(import_bases)
              ;first != last;++first)
        {
          typedef typename boost::range_value<import_base_range>::type import_base_value_type;
          typedef typename unwrap_parameter<import_base_value_type>::type import_base_type;
          typedef concept::parser::import_base_traits<import_base_type> import_base_traits;
          typename std::map<DocumentURI, document_type>::iterator 
            iterator = d.documents.find(import_base_traits::document_uri(*first));
          if(iterator != d.documents.end())
          {
            map.insert(std::make_pair(import_base_traits::alias(*first)
                                      , parser_head_traits::region_base_all
                                      (parser_document_traits::head(iterator->second.parser_document))));
          }
        }
      }
      return region_lookupable(region_bases, map);
    }

    static void register_event (document_type& d, component_identifier const& identifier
                                , boost::optional<component_identifier> const& interface_
                                , gntl::transition_type transition, gntl::event_type event)
    {
      GNTL_DEBUG_LOG("registering transition " << transition << " event " << event
                << " id: " << identifier << " interface ")
      if(interface_)
        GNTL_DEBUG_LOG(*interface_)
      else
        GNTL_DEBUG_LOG("[none]")
          GNTL_DEBUG_LOG(" this: " << &d << std::endl)
      d.pending_events.push (event_type (identifier, interface_, transition, event));
    }

    static std::size_t pending_events (document_type const& d)
    {
        return d.pending_events.size ();
    }

    static event_type top_event (document_type const& d)
    {
        return d.pending_events.top ();
    }

    static void pop_event (document_type& d)
    {
        d.pending_events.pop ();
    }

    static bool has_property(document_type const& d, property_name name)
    {
      typedef typename document_type::property_container::iterator iterator;
      iterator property = d.properties.find(gntl::ref(d), name);
      return property != d.properties.end(gntl::ref(d));
    }
    static property_type get_property(document_type const& d, property_name name)
    {
      return *d.properties.find(gntl::ref(d), name);
    }
    static void start_set_property(document_type& d, property_name name, int v)
    {
      d.properties.start_set_generic(gntl::ref(d), name, v);
    }
    static void start_set_property(document_type& d, property_name name, std::string v)
    {
      d.properties.start_set(gntl::ref(d), name, v);
    }
    static void commit_set_property(document_type& d, property_name name)
    {
      d.properties.commit_set(gntl::ref(d), name);
    }
    static int focus_index(document_type const& d)
    {
      return d.focus_index?*d.focus_index:*d.next_focus_index;
    }
    static bool has_focus(document_type const& d)
    {
      return d.focus_index || d.next_focus_index;
    }
    static bool is_focus_bound(document_type const& d)
    {
      GNTL_DEBUG_LOG("testing bound of focus index to media: " << d.focus_media << " this: " << &d << std::endl)
      return !d.focus_media.empty();
    }
    static component_identifier focused_media(document_type const& d)
    {
      return d.focus_media;
    }
    static void set_focused_media(document_type& d, component_identifier id)
    {
      GNTL_DEBUG_LOG("focused media " << id << " this: " << &d << std::endl)
      d.focus_media = id;
    }
    static void set_current_key_master_from_focused_media(document_type& d)
    {
      d.current_key_master_media = d.focus_media;
    }
    static component_identifier current_key_master(document_type const& d)
    {
      return d.current_key_master_media;
    }
    static bool has_current_key_master(document_type const& d)
    {
      return !d.current_key_master_media.empty();
    }
    static void reset_focus (document_type& d)
    {
      GNTL_DEBUG_LOG("document_traits reset_focus " << &d << std::endl)
      d.focus_media.clear();
      d.focus_index = boost::none;
    }
    static void global_properties_media(document_type& d, component_identifier id)
    {
      d.global_properties_media = id;
    }
    static bool has_global_properties_media(document_type const& d)
    {
      return !d.global_properties_media.empty();
    }
    static component_identifier global_properties_media(document_type const& d)
    {
      return d.global_properties_media;
    }
    static body_type body(document_type& d)
    {
      return d.body;
    }
    static document_lookupable document_lookup(document_type& d)
    {
      document_lookupable l;
      l.add_document(d.document_uri, d);

      for(typename std::map<DocumentURI, document_type>::iterator
            first = d.documents.begin(), last = d.documents.end()
            ;first != last; ++first)
        l.add_document(first->first, first->second);

      return l;
    }
    static causal_connector_lookupable causal_connector_lookup(document_type& d)
    {
      return d.get_causal_connector_lookupable();
    }
    static bool has_descriptor_base(document_type const& d)
    {
      return parser_head_traits::has_descriptor_base
        (parser_document_traits::head(d.parser_document));
    }
    static bool has_connector_base(document_type const& d)
    {
      return parser_head_traits::has_connector_base
        (parser_document_traits::head(d.parser_document));
    }
    static descriptor_base_type descriptor_base(document_type const& d)
    {
      return parser_head_traits::descriptor_base
        (parser_document_traits::head(d.parser_document));
    }
    static connector_base_type connector_base(document_type const& d)
    {
      return parser_head_traits::connector_base
        (parser_document_traits::head(d.parser_document));
    }
    static region_base_range region_base_all(document_type const& d)
    {
      return parser_head_traits::region_base_all
        (parser_document_traits::head(d.parser_document));
    }
};

} } }


#include <gntl/detail/pop_options.hpp>

#endif
