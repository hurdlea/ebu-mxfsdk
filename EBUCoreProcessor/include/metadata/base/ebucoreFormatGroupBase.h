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

#ifndef __MXFPP_EBUCOREFORMATGROUP_BASE_H__
#define __MXFPP_EBUCOREFORMATGROUP_BASE_H__



#include <libMXF++/metadata/InterchangeObject.h>


namespace mxfpp
{


class ebucoreFormatGroupBase : public InterchangeObject
{
public:
    friend class MetadataSetFactory<ebucoreFormatGroupBase>;
    static const mxfKey setKey;

public:
    ebucoreFormatGroupBase(HeaderMetadata *headerMetadata);
    virtual ~ebucoreFormatGroupBase();


   // getters

   bool haveformatGroupThesaurus() const;
   std::string getformatGroupThesaurus() const;
   bool haveformatGroupLabel() const;
   std::string getformatGroupLabel() const;
   bool haveformatGroupLink() const;
   std::string getformatGroupLink() const;
   bool haveformatGroupUL() const;
   mxfUL getformatGroupUL() const;
   bool haveformatGroupDefinition() const;
   std::string getformatGroupDefinition() const;
   bool haveformatGroupLanguage() const;
   std::string getformatGroupLanguage() const;


   // setters

   void setformatGroupThesaurus(std::string value);
   void setformatGroupLabel(std::string value);
   void setformatGroupLink(std::string value);
   void setformatGroupUL(mxfUL value);
   void setformatGroupDefinition(std::string value);
   void setformatGroupLanguage(std::string value);


protected:
    ebucoreFormatGroupBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet);
};


};


#endif
