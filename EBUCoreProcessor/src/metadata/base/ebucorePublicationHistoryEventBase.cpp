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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;


const mxfKey ebucorePublicationHistoryEventBase::setKey = MXF_SET_K(ebucorePublicationHistoryEvent);


ebucorePublicationHistoryEventBase::ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucorePublicationHistoryEventBase::ebucorePublicationHistoryEventBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucorePublicationHistoryEventBase::~ebucorePublicationHistoryEventBase()
{}


bool ebucorePublicationHistoryEventBase::getfirstPublicationFlag() const
{
    return getBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, firstPublicationFlag));
}

bool ebucorePublicationHistoryEventBase::havepublicationDate() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate));
}

mxfTimestamp ebucorePublicationHistoryEventBase::getpublicationDate() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate));
}

bool ebucorePublicationHistoryEventBase::havepublicationTime() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime));
}

mxfTimestamp ebucorePublicationHistoryEventBase::getpublicationTime() const
{
    return getTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime));
}

bool ebucorePublicationHistoryEventBase::havepublicationService() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService));
}

std::string ebucorePublicationHistoryEventBase::getpublicationService() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService));
}

bool ebucorePublicationHistoryEventBase::havepublicationMedium() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium));
}

std::string ebucorePublicationHistoryEventBase::getpublicationMedium() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium));
}

bool ebucorePublicationHistoryEventBase::havepublicationChannel() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel));
}

std::string ebucorePublicationHistoryEventBase::getpublicationChannel() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel));
}

bool ebucorePublicationHistoryEventBase::havepublicationFormatIDRef() const
{
    return haveItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatIDRef));
}

std::string ebucorePublicationHistoryEventBase::getpublicationFormatIDRef() const
{
    return getStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatIDRef));
}

void ebucorePublicationHistoryEventBase::setfirstPublicationFlag(bool value)
{
    setBooleanItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, firstPublicationFlag), value);
}

void ebucorePublicationHistoryEventBase::setpublicationDate(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationDate), value);
}

void ebucorePublicationHistoryEventBase::setpublicationTime(mxfTimestamp value)
{
    setTimestampItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationTime), value);
}

void ebucorePublicationHistoryEventBase::setpublicationService(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationService), value);
}

void ebucorePublicationHistoryEventBase::setpublicationMedium(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationMedium), value);
}

void ebucorePublicationHistoryEventBase::setpublicationChannel(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationChannel), value);
}

void ebucorePublicationHistoryEventBase::setpublicationFormatIDRef(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucorePublicationHistoryEvent, publicationFormatIDRef), value);
}

