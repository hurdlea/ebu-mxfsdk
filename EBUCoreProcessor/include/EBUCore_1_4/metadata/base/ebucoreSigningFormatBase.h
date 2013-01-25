/*
 * Copyright (C) 2008, British Broadcasting Corporation
 * All Rights Reserved.
 *
 * Author: Philip de Nier
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the British Broadcasting Corporation nor the names
 *       of its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __MXFPP_EBUCORESIGNINGFORMAT_BASE_H__
#define __MXFPP_EBUCORESIGNINGFORMAT_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreSigningFormatBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreSigningFormatBase>;
    static const mxfKey setKey;

public:
    ebucoreSigningFormatBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreSigningFormatBase();


   // getters

   bool havesigningFormatID() const;
   std::string getsigningFormatID() const;
   bool havesigningFormatVersionID() const;
   std::string getsigningFormatVersionID() const;
   bool havesigningFormatName() const;
   std::string getsigningFormatName() const;
   bool havesigningTrackID() const;
   std::string getsigningTrackID() const;
   bool havesigningTrackName() const;
   std::string getsigningTrackName() const;
   bool havesigningTrackLanguageCode() const;
   std::string getsigningTrackLanguageCode() const;
   bool havesigningSourceUri() const;
   std::string getsigningSourceUri() const;
   bool havesigningTypeGroup() const;
   ebucoreTypeGroup* getsigningTypeGroup() const;
   bool havesigningFormatGroup() const;
   ebucoreFormatGroup* getsigningFormatGroup() const;


   // setters

   void setsigningFormatID(std::string value);
   void setsigningFormatVersionID(std::string value);
   void setsigningFormatName(std::string value);
   void setsigningTrackID(std::string value);
   void setsigningTrackName(std::string value);
   void setsigningTrackLanguageCode(std::string value);
   void setsigningSourceUri(std::string value);
   void setsigningTypeGroup(ebucoreTypeGroup* value);
   void setsigningFormatGroup(ebucoreFormatGroup* value);


protected:
    ebucoreSigningFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
