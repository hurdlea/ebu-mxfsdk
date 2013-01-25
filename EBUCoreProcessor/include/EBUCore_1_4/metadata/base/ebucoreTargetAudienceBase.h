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

#ifndef __MXFPP_EBUCORETARGETAUDIENCE_BASE_H__
#define __MXFPP_EBUCORETARGETAUDIENCE_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>

using namespace mxfpp;

namespace EBUSDK { namespace EBUCore { namespace EBUCore_1_4 { namespace KLV
{


class ebucoreTargetAudienceBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreTargetAudienceBase>;
    static const mxfKey setKey;

public:
    ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreTargetAudienceBase();


   // getters

   bool havetargetAudienceReason() const;
   std::string gettargetAudienceReason() const;
   bool havetargetAudienceLinkToLogo() const;
   std::string gettargetAudienceLinkToLogo() const;
   bool havetargetAudienceNotRatedFlag() const;
   bool gettargetAudienceNotRatedFlag() const;
   bool havetargetAudienceAdultContentFlag() const;
   bool gettargetAudienceAdultContentFlag() const;
   bool havetargetAudienceTypeGroup() const;
   ebucoreTypeGroup* gettargetAudienceTypeGroup() const;
   bool havetargetAudienceRegion() const;
   std::vector<ebucoreRegion*> gettargetAudienceRegion() const;


   // setters

   void settargetAudienceReason(std::string value);
   void settargetAudienceLinkToLogo(std::string value);
   void settargetAudienceNotRatedFlag(bool value);
   void settargetAudienceAdultContentFlag(bool value);
   void settargetAudienceTypeGroup(ebucoreTypeGroup* value);
   void settargetAudienceRegion(const std::vector<ebucoreRegion*>& value);
   void appendtargetAudienceRegion(ebucoreRegion* value);


protected:
    ebucoreTargetAudienceBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


}}}};


#endif
