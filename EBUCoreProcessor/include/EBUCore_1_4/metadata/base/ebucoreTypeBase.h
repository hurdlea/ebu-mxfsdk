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

#ifndef __MXFPP_EBUCORETYPE_BASE_H__
#define __MXFPP_EBUCORETYPE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTypeBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTypeBase>;
    static const mxfKey setKey;

public:
    ebucoreTypeBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTypeBase();


   // getters

   bool havetypeNote() const;
   std::string gettypeNote() const;
   bool havetypeValue() const;
   std::vector<ebucoreTextualAnnotation*> gettypeValue() const;
   bool haveobjectType() const;
   std::vector<ebucoreObjectType*> getobjectType() const;
   bool havegenre() const;
   std::vector<ebucoreGenre*> getgenre() const;
   bool havetargetAudience() const;
   std::vector<ebucoreTargetAudience*> gettargetAudience() const;


   // setters

   void settypeNote(std::string value);
   void settypeValue(const std::vector<ebucoreTextualAnnotation*>& value);
   void appendtypeValue(ebucoreTextualAnnotation* value);
   void setobjectType(const std::vector<ebucoreObjectType*>& value);
   void appendobjectType(ebucoreObjectType* value);
   void setgenre(const std::vector<ebucoreGenre*>& value);
   void appendgenre(ebucoreGenre* value);
   void settargetAudience(const std::vector<ebucoreTargetAudience*>& value);
   void appendtargetAudience(ebucoreTargetAudience* value);


protected:
    ebucoreTypeBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif