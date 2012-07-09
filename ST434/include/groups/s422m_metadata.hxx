// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#ifndef GROUPS_S422M_METADATA_HXX
#define GROUPS_S422M_METADATA_HXX

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3030000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#ifndef XSD_USE_CHAR
#define XSD_USE_CHAR
#endif

#ifndef XSD_CXX_TREE_USE_CHAR
#define XSD_CXX_TREE_USE_CHAR
#endif

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/types.hxx>

#include <xsd/cxx/xml/error-handler.hxx>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

#include <xsd/cxx/tree/parsing.hxx>
#include <xsd/cxx/tree/parsing/byte.hxx>
#include <xsd/cxx/tree/parsing/unsigned-byte.hxx>
#include <xsd/cxx/tree/parsing/short.hxx>
#include <xsd/cxx/tree/parsing/unsigned-short.hxx>
#include <xsd/cxx/tree/parsing/int.hxx>
#include <xsd/cxx/tree/parsing/unsigned-int.hxx>
#include <xsd/cxx/tree/parsing/long.hxx>
#include <xsd/cxx/tree/parsing/unsigned-long.hxx>
#include <xsd/cxx/tree/parsing/boolean.hxx>
#include <xsd/cxx/tree/parsing/float.hxx>
#include <xsd/cxx/tree/parsing/double.hxx>
#include <xsd/cxx/tree/parsing/decimal.hxx>

#include <xsd/cxx/xml/dom/serialization-header.hxx>
#include <xsd/cxx/tree/serialization.hxx>
#include <xsd/cxx/tree/serialization/byte.hxx>
#include <xsd/cxx/tree/serialization/unsigned-byte.hxx>
#include <xsd/cxx/tree/serialization/short.hxx>
#include <xsd/cxx/tree/serialization/unsigned-short.hxx>
#include <xsd/cxx/tree/serialization/int.hxx>
#include <xsd/cxx/tree/serialization/unsigned-int.hxx>
#include <xsd/cxx/tree/serialization/long.hxx>
#include <xsd/cxx/tree/serialization/unsigned-long.hxx>
#include <xsd/cxx/tree/serialization/boolean.hxx>
#include <xsd/cxx/tree/serialization/float.hxx>
#include <xsd/cxx/tree/serialization/double.hxx>
#include <xsd/cxx/tree/serialization/decimal.hxx>

namespace xml_schema
{
  // anyType and anySimpleType.
  //
  typedef ::xsd::cxx::tree::type type;
  typedef ::xsd::cxx::tree::simple_type< type > simple_type;
  typedef ::xsd::cxx::tree::type container;

  // 8-bit
  //
  typedef signed char byte;
  typedef unsigned char unsigned_byte;

  // 16-bit
  //
  typedef short short_;
  typedef unsigned short unsigned_short;

  // 32-bit
  //
  typedef int int_;
  typedef unsigned int unsigned_int;

  // 64-bit
  //
  typedef long long long_;
  typedef unsigned long long unsigned_long;

  // Supposed to be arbitrary-length integral types.
  //
  typedef long long integer;
  typedef long long non_positive_integer;
  typedef unsigned long long non_negative_integer;
  typedef unsigned long long positive_integer;
  typedef long long negative_integer;

  // Boolean.
  //
  typedef bool boolean;

  // Floating-point types.
  //
  typedef float float_;
  typedef double double_;
  typedef double decimal;

  // String types.
  //
  typedef ::xsd::cxx::tree::string< char, simple_type > string;
  typedef ::xsd::cxx::tree::normalized_string< char, string > normalized_string;
  typedef ::xsd::cxx::tree::token< char, normalized_string > token;
  typedef ::xsd::cxx::tree::name< char, token > name;
  typedef ::xsd::cxx::tree::nmtoken< char, token > nmtoken;
  typedef ::xsd::cxx::tree::nmtokens< char, simple_type, nmtoken > nmtokens;
  typedef ::xsd::cxx::tree::ncname< char, name > ncname;
  typedef ::xsd::cxx::tree::language< char, token > language;

  // ID/IDREF.
  //
  typedef ::xsd::cxx::tree::id< char, ncname > id;
  typedef ::xsd::cxx::tree::idref< char, ncname, type > idref;
  typedef ::xsd::cxx::tree::idrefs< char, simple_type, idref > idrefs;

  // URI.
  //
  typedef ::xsd::cxx::tree::uri< char, simple_type > uri;

  // Qualified name.
  //
  typedef ::xsd::cxx::tree::qname< char, simple_type, uri, ncname > qname;

  // Binary.
  //
  typedef ::xsd::cxx::tree::buffer< char > buffer;
  typedef ::xsd::cxx::tree::base64_binary< char, simple_type > base64_binary;
  typedef ::xsd::cxx::tree::hex_binary< char, simple_type > hex_binary;

  // Date/time.
  //
  typedef ::xsd::cxx::tree::time_zone time_zone;
  typedef ::xsd::cxx::tree::date< char, simple_type > date;
  typedef ::xsd::cxx::tree::date_time< char, simple_type > date_time;
  typedef ::xsd::cxx::tree::duration< char, simple_type > duration;
  typedef ::xsd::cxx::tree::gday< char, simple_type > gday;
  typedef ::xsd::cxx::tree::gmonth< char, simple_type > gmonth;
  typedef ::xsd::cxx::tree::gmonth_day< char, simple_type > gmonth_day;
  typedef ::xsd::cxx::tree::gyear< char, simple_type > gyear;
  typedef ::xsd::cxx::tree::gyear_month< char, simple_type > gyear_month;
  typedef ::xsd::cxx::tree::time< char, simple_type > time;

  // Entity.
  //
  typedef ::xsd::cxx::tree::entity< char, ncname > entity;
  typedef ::xsd::cxx::tree::entities< char, simple_type, entity > entities;

  // Namespace information and list stream. Used in
  // serialization functions.
  //
  typedef ::xsd::cxx::xml::dom::namespace_info< char > namespace_info;
  typedef ::xsd::cxx::xml::dom::namespace_infomap< char > namespace_infomap;
  typedef ::xsd::cxx::tree::list_stream< char > list_stream;
  typedef ::xsd::cxx::tree::as_double< double_ > as_double;
  typedef ::xsd::cxx::tree::as_decimal< decimal > as_decimal;
  typedef ::xsd::cxx::tree::facet facet;

  // Flags and properties.
  //
  typedef ::xsd::cxx::tree::flags flags;
  typedef ::xsd::cxx::tree::properties< char > properties;

  // Parsing/serialization diagnostics.
  //
  typedef ::xsd::cxx::tree::severity severity;
  typedef ::xsd::cxx::tree::error< char > error;
  typedef ::xsd::cxx::tree::diagnostics< char > diagnostics;

  // Exceptions.
  //
  typedef ::xsd::cxx::tree::exception< char > exception;
  typedef ::xsd::cxx::tree::bounds< char > bounds;
  typedef ::xsd::cxx::tree::duplicate_id< char > duplicate_id;
  typedef ::xsd::cxx::tree::parsing< char > parsing;
  typedef ::xsd::cxx::tree::expected_element< char > expected_element;
  typedef ::xsd::cxx::tree::unexpected_element< char > unexpected_element;
  typedef ::xsd::cxx::tree::expected_attribute< char > expected_attribute;
  typedef ::xsd::cxx::tree::unexpected_enumerator< char > unexpected_enumerator;
  typedef ::xsd::cxx::tree::expected_text_content< char > expected_text_content;
  typedef ::xsd::cxx::tree::no_prefix_mapping< char > no_prefix_mapping;
  typedef ::xsd::cxx::tree::serialization< char > serialization;

  // Error handler callback interface.
  //
  typedef ::xsd::cxx::xml::error_handler< char > error_handler;

  // DOM interaction.
  //
  namespace dom
  {
    // Automatic pointer for DOMDocument.
    //
    using ::xsd::cxx::xml::dom::auto_ptr;

#ifndef XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
#define XSD_CXX_TREE_TREE_NODE_KEY__XML_SCHEMA
    // DOM user data key for back pointers to tree nodes.
    //
    const XMLCh* const tree_node_key = ::xsd::cxx::tree::user_data_keys::node;
#endif
  }
}

// Forward declarations.
//
namespace st434
{
  namespace s422m
  {
    namespace groups
    {
      class JPEG2000SubDescriptorType;
    }
  }
}


#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

#include "dataTypes/s377m_types.hxx"

#include "dictionary/rp210.hxx"

#include "groups/s377m_metadata.hxx"

namespace st434
{
  namespace s422m
  {
    namespace groups
    {
      class JPEG2000SubDescriptorType: public ::st434::s377m::groups::SubDescriptorsType
      {
        public:
        // Rsiz
        // 
        typedef ::st434::s377m::types::UInt16 Rsiz_type;
        typedef ::xsd::cxx::tree::traits< Rsiz_type, char > Rsiz_traits;

        const Rsiz_type&
        Rsiz () const;

        Rsiz_type&
        Rsiz ();

        void
        Rsiz (const Rsiz_type& x);

        void
        Rsiz (::std::auto_ptr< Rsiz_type > p);

        // Xsiz
        // 
        typedef ::st434::s377m::types::UInt32 Xsiz_type;
        typedef ::xsd::cxx::tree::traits< Xsiz_type, char > Xsiz_traits;

        const Xsiz_type&
        Xsiz () const;

        Xsiz_type&
        Xsiz ();

        void
        Xsiz (const Xsiz_type& x);

        void
        Xsiz (::std::auto_ptr< Xsiz_type > p);

        // Ysiz
        // 
        typedef ::st434::s377m::types::UInt32 Ysiz_type;
        typedef ::xsd::cxx::tree::traits< Ysiz_type, char > Ysiz_traits;

        const Ysiz_type&
        Ysiz () const;

        Ysiz_type&
        Ysiz ();

        void
        Ysiz (const Ysiz_type& x);

        void
        Ysiz (::std::auto_ptr< Ysiz_type > p);

        // XOsiz
        // 
        typedef ::st434::s377m::types::UInt32 XOsiz_type;
        typedef ::xsd::cxx::tree::traits< XOsiz_type, char > XOsiz_traits;

        const XOsiz_type&
        XOsiz () const;

        XOsiz_type&
        XOsiz ();

        void
        XOsiz (const XOsiz_type& x);

        void
        XOsiz (::std::auto_ptr< XOsiz_type > p);

        // YOsiz
        // 
        typedef ::st434::s377m::types::UInt32 YOsiz_type;
        typedef ::xsd::cxx::tree::traits< YOsiz_type, char > YOsiz_traits;

        const YOsiz_type&
        YOsiz () const;

        YOsiz_type&
        YOsiz ();

        void
        YOsiz (const YOsiz_type& x);

        void
        YOsiz (::std::auto_ptr< YOsiz_type > p);

        // XTsiz
        // 
        typedef ::st434::s377m::types::UInt32 XTsiz_type;
        typedef ::xsd::cxx::tree::traits< XTsiz_type, char > XTsiz_traits;

        const XTsiz_type&
        XTsiz () const;

        XTsiz_type&
        XTsiz ();

        void
        XTsiz (const XTsiz_type& x);

        void
        XTsiz (::std::auto_ptr< XTsiz_type > p);

        // YTsiz
        // 
        typedef ::st434::s377m::types::UInt32 YTsiz_type;
        typedef ::xsd::cxx::tree::traits< YTsiz_type, char > YTsiz_traits;

        const YTsiz_type&
        YTsiz () const;

        YTsiz_type&
        YTsiz ();

        void
        YTsiz (const YTsiz_type& x);

        void
        YTsiz (::std::auto_ptr< YTsiz_type > p);

        // XTOsiz
        // 
        typedef ::st434::s377m::types::UInt32 XTOsiz_type;
        typedef ::xsd::cxx::tree::traits< XTOsiz_type, char > XTOsiz_traits;

        const XTOsiz_type&
        XTOsiz () const;

        XTOsiz_type&
        XTOsiz ();

        void
        XTOsiz (const XTOsiz_type& x);

        void
        XTOsiz (::std::auto_ptr< XTOsiz_type > p);

        // YTOsiz
        // 
        typedef ::st434::s377m::types::UInt32 YTOsiz_type;
        typedef ::xsd::cxx::tree::traits< YTOsiz_type, char > YTOsiz_traits;

        const YTOsiz_type&
        YTOsiz () const;

        YTOsiz_type&
        YTOsiz ();

        void
        YTOsiz (const YTOsiz_type& x);

        void
        YTOsiz (::std::auto_ptr< YTOsiz_type > p);

        // Csiz
        // 
        typedef ::st434::s377m::types::UInt16 Csiz_type;
        typedef ::xsd::cxx::tree::traits< Csiz_type, char > Csiz_traits;

        const Csiz_type&
        Csiz () const;

        Csiz_type&
        Csiz ();

        void
        Csiz (const Csiz_type& x);

        void
        Csiz (::std::auto_ptr< Csiz_type > p);

        // PictureComponentSizing
        // 
        typedef ::properties::S335M::PictureComponentSizing PictureComponentSizing_type;
        typedef ::xsd::cxx::tree::traits< PictureComponentSizing_type, char > PictureComponentSizing_traits;

        const PictureComponentSizing_type&
        PictureComponentSizing () const;

        PictureComponentSizing_type&
        PictureComponentSizing ();

        void
        PictureComponentSizing (const PictureComponentSizing_type& x);

        void
        PictureComponentSizing (::std::auto_ptr< PictureComponentSizing_type > p);

        // CodingStyleDefault
        // 
        typedef ::st434::s422m::types::J2KCodingStyleDefault CodingStyleDefault_type;
        typedef ::xsd::cxx::tree::optional< CodingStyleDefault_type > CodingStyleDefault_optional;
        typedef ::xsd::cxx::tree::traits< CodingStyleDefault_type, char > CodingStyleDefault_traits;

        const CodingStyleDefault_optional&
        CodingStyleDefault () const;

        CodingStyleDefault_optional&
        CodingStyleDefault ();

        void
        CodingStyleDefault (const CodingStyleDefault_type& x);

        void
        CodingStyleDefault (const CodingStyleDefault_optional& x);

        void
        CodingStyleDefault (::std::auto_ptr< CodingStyleDefault_type > p);

        // QuantizationDefault
        // 
        typedef ::st434::s422m::types::J2KQuantisationDefault QuantizationDefault_type;
        typedef ::xsd::cxx::tree::optional< QuantizationDefault_type > QuantizationDefault_optional;
        typedef ::xsd::cxx::tree::traits< QuantizationDefault_type, char > QuantizationDefault_traits;

        const QuantizationDefault_optional&
        QuantizationDefault () const;

        QuantizationDefault_optional&
        QuantizationDefault ();

        void
        QuantizationDefault (const QuantizationDefault_type& x);

        void
        QuantizationDefault (const QuantizationDefault_optional& x);

        void
        QuantizationDefault (::std::auto_ptr< QuantizationDefault_type > p);

        // Constructors.
        //
        JPEG2000SubDescriptorType (const InstanceID_type&,
                                   const Rsiz_type&,
                                   const Xsiz_type&,
                                   const Ysiz_type&,
                                   const XOsiz_type&,
                                   const YOsiz_type&,
                                   const XTsiz_type&,
                                   const YTsiz_type&,
                                   const XTOsiz_type&,
                                   const YTOsiz_type&,
                                   const Csiz_type&,
                                   const PictureComponentSizing_type&);

        JPEG2000SubDescriptorType (const InstanceID_type&,
                                   const Rsiz_type&,
                                   const Xsiz_type&,
                                   const Ysiz_type&,
                                   const XOsiz_type&,
                                   const YOsiz_type&,
                                   const XTsiz_type&,
                                   const YTsiz_type&,
                                   const XTOsiz_type&,
                                   const YTOsiz_type&,
                                   const Csiz_type&,
                                   ::std::auto_ptr< PictureComponentSizing_type >&);

        JPEG2000SubDescriptorType (const ::xercesc::DOMElement& e,
                                   ::xml_schema::flags f = 0,
                                   ::xml_schema::container* c = 0);

        JPEG2000SubDescriptorType (const JPEG2000SubDescriptorType& x,
                                   ::xml_schema::flags f = 0,
                                   ::xml_schema::container* c = 0);

        virtual JPEG2000SubDescriptorType*
        _clone (::xml_schema::flags f = 0,
                ::xml_schema::container* c = 0) const;

        virtual 
        ~JPEG2000SubDescriptorType ();

        // Implementation.
        //
        protected:
        void
        parse (::xsd::cxx::xml::dom::parser< char >&,
               ::xml_schema::flags);

        protected:
        ::xsd::cxx::tree::one< Rsiz_type > Rsiz_;
        ::xsd::cxx::tree::one< Xsiz_type > Xsiz_;
        ::xsd::cxx::tree::one< Ysiz_type > Ysiz_;
        ::xsd::cxx::tree::one< XOsiz_type > XOsiz_;
        ::xsd::cxx::tree::one< YOsiz_type > YOsiz_;
        ::xsd::cxx::tree::one< XTsiz_type > XTsiz_;
        ::xsd::cxx::tree::one< YTsiz_type > YTsiz_;
        ::xsd::cxx::tree::one< XTOsiz_type > XTOsiz_;
        ::xsd::cxx::tree::one< YTOsiz_type > YTOsiz_;
        ::xsd::cxx::tree::one< Csiz_type > Csiz_;
        ::xsd::cxx::tree::one< PictureComponentSizing_type > PictureComponentSizing_;
        CodingStyleDefault_optional CodingStyleDefault_;
        QuantizationDefault_optional QuantizationDefault_;
      };
    }
  }
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace st434
{
  namespace s422m
  {
    namespace groups
    {
      // Parse a URI or a local file.
      //

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (const ::std::string& uri,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (const ::std::string& uri,
                                 ::xml_schema::error_handler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (const ::std::string& uri,
                                 ::xercesc::DOMErrorHandler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse std::istream.
      //

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 ::xml_schema::error_handler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 ::xercesc::DOMErrorHandler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 const ::std::string& id,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 const ::std::string& id,
                                 ::xml_schema::error_handler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::std::istream& is,
                                 const ::std::string& id,
                                 ::xercesc::DOMErrorHandler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse xercesc::InputSource.
      //

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::xercesc::InputSource& is,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::xercesc::InputSource& is,
                                 ::xml_schema::error_handler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::xercesc::InputSource& is,
                                 ::xercesc::DOMErrorHandler& eh,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse xercesc::DOMDocument.
      //

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (const ::xercesc::DOMDocument& d,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s377m::types::Ref >
      JPEG2000SubDescriptor_REF (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
                                 ::xml_schema::flags f = 0,
                                 const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse a URI or a local file.
      //

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (const ::std::string& uri,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (const ::std::string& uri,
                             ::xml_schema::error_handler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (const ::std::string& uri,
                             ::xercesc::DOMErrorHandler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse std::istream.
      //

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             ::xml_schema::error_handler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             ::xercesc::DOMErrorHandler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             const ::std::string& id,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             const ::std::string& id,
                             ::xml_schema::error_handler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::std::istream& is,
                             const ::std::string& id,
                             ::xercesc::DOMErrorHandler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse xercesc::InputSource.
      //

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::xercesc::InputSource& is,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::xercesc::InputSource& is,
                             ::xml_schema::error_handler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::xercesc::InputSource& is,
                             ::xercesc::DOMErrorHandler& eh,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      // Parse xercesc::DOMDocument.
      //

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (const ::xercesc::DOMDocument& d,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());

      ::std::auto_ptr< ::st434::s422m::groups::JPEG2000SubDescriptorType >
      JPEG2000SubDescriptor (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
                             ::xml_schema::flags f = 0,
                             const ::xml_schema::properties& p = ::xml_schema::properties ());
    }
  }
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace st434
{
  namespace s422m
  {
    namespace groups
    {
      // Serialize to std::ostream.
      //

      void
      JPEG2000SubDescriptor_REF (::std::ostream& os,
                                 const ::st434::s377m::types::Ref& x, 
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor_REF (::std::ostream& os,
                                 const ::st434::s377m::types::Ref& x, 
                                 ::xml_schema::error_handler& eh,
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor_REF (::std::ostream& os,
                                 const ::st434::s377m::types::Ref& x, 
                                 ::xercesc::DOMErrorHandler& eh,
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      // Serialize to xercesc::XMLFormatTarget.
      //

      void
      JPEG2000SubDescriptor_REF (::xercesc::XMLFormatTarget& ft,
                                 const ::st434::s377m::types::Ref& x, 
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor_REF (::xercesc::XMLFormatTarget& ft,
                                 const ::st434::s377m::types::Ref& x, 
                                 ::xml_schema::error_handler& eh,
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor_REF (::xercesc::XMLFormatTarget& ft,
                                 const ::st434::s377m::types::Ref& x, 
                                 ::xercesc::DOMErrorHandler& eh,
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 const ::std::string& e = "UTF-8",
                                 ::xml_schema::flags f = 0);

      // Serialize to an existing xercesc::DOMDocument.
      //

      void
      JPEG2000SubDescriptor_REF (::xercesc::DOMDocument& d,
                                 const ::st434::s377m::types::Ref& x,
                                 ::xml_schema::flags f = 0);

      // Serialize to a new xercesc::DOMDocument.
      //

      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
      JPEG2000SubDescriptor_REF (const ::st434::s377m::types::Ref& x, 
                                 const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                                 ::xml_schema::flags f = 0);

      // Serialize to std::ostream.
      //

      void
      JPEG2000SubDescriptor (::std::ostream& os,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor (::std::ostream& os,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             ::xml_schema::error_handler& eh,
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor (::std::ostream& os,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             ::xercesc::DOMErrorHandler& eh,
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      // Serialize to xercesc::XMLFormatTarget.
      //

      void
      JPEG2000SubDescriptor (::xercesc::XMLFormatTarget& ft,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor (::xercesc::XMLFormatTarget& ft,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             ::xml_schema::error_handler& eh,
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      void
      JPEG2000SubDescriptor (::xercesc::XMLFormatTarget& ft,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             ::xercesc::DOMErrorHandler& eh,
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             const ::std::string& e = "UTF-8",
                             ::xml_schema::flags f = 0);

      // Serialize to an existing xercesc::DOMDocument.
      //

      void
      JPEG2000SubDescriptor (::xercesc::DOMDocument& d,
                             const ::st434::s422m::groups::JPEG2000SubDescriptorType& x,
                             ::xml_schema::flags f = 0);

      // Serialize to a new xercesc::DOMDocument.
      //

      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
      JPEG2000SubDescriptor (const ::st434::s422m::groups::JPEG2000SubDescriptorType& x, 
                             const ::xml_schema::namespace_infomap& m = ::xml_schema::namespace_infomap (),
                             ::xml_schema::flags f = 0);

      void
      operator<< (::xercesc::DOMElement&, const JPEG2000SubDescriptorType&);
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // GROUPS_S422M_METADATA_HXX
