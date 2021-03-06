 /*
  *    Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
  *
  *    Licensed under the Apache License, Version 2.0 (the "License");
  *    you may not use this file except in compliance with the License.
  *    You may obtain a copy of the License at
  *
  *       http://www.apache.org/licenses/LICENSE-2.0
  *
  *    Unless required by applicable law or agreed to in writing, software
  *    distributed under the License is distributed on an "AS IS" BASIS,
  *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  *    See the License for the specific language governing permissions and
  *    limitations under the License.
  *
  */
  
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <memory>

#include <libMXF++/MXF.h>
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreDataFormatBase::setKey = MXF_SET_K(ebucoreDataFormat);


ebucoreDataFormatBase::ebucoreDataFormatBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreDataFormatBase::ebucoreDataFormatBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreDataFormatBase::~ebucoreDataFormatBase()
{}


bool ebucoreDataFormatBase::havedataFormatID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatID));
}

std::string ebucoreDataFormatBase::getdataFormatID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatID));
}

bool ebucoreDataFormatBase::havedataFormatVersionID() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatVersionID));
}

std::string ebucoreDataFormatBase::getdataFormatVersionID() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatVersionID));
}

bool ebucoreDataFormatBase::havedataFormatName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatName));
}

std::string ebucoreDataFormatBase::getdataFormatName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatName));
}

bool ebucoreDataFormatBase::havedataFormatDefinition() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatDefinition));
}

std::string ebucoreDataFormatBase::getdataFormatDefinition() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatDefinition));
}

bool ebucoreDataFormatBase::havedataTrackId() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackId));
}

std::string ebucoreDataFormatBase::getdataTrackId() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackId));
}

bool ebucoreDataFormatBase::havedataTrackName() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackName));
}

std::string ebucoreDataFormatBase::getdataTrackName() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackName));
}

bool ebucoreDataFormatBase::havedataTrackLanguageCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackLanguageCode));
}

std::string ebucoreDataFormatBase::getdataTrackLanguageCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackLanguageCode));
}

bool ebucoreDataFormatBase::havecaptioning() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, captioning));
}

std::vector<ebucoreCaptioning*> ebucoreDataFormatBase::getcaptioning() const
{
    vector<ebucoreCaptioning*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, captioning)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCaptioning*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCaptioning*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havesubtitling() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, subtitling));
}

std::vector<ebucoreSubtitling*> ebucoreDataFormatBase::getsubtitling() const
{
    vector<ebucoreSubtitling*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, subtitling)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreSubtitling*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreSubtitling*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::haveancillaryData() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, ancillaryData));
}

std::vector<ebucoreAncillaryData*> ebucoreDataFormatBase::getancillaryData() const
{
    vector<ebucoreAncillaryData*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, ancillaryData)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreAncillaryData*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreAncillaryData*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeString() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeString));
}

std::vector<ebucoreTechnicalAttributeString*> ebucoreDataFormatBase::getdataTechnicalAttributeString() const
{
    vector<ebucoreTechnicalAttributeString*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeString)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeString*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt8));
}

std::vector<ebucoreTechnicalAttributeInt8*> ebucoreDataFormatBase::getdataTechnicalAttributeInt8() const
{
    vector<ebucoreTechnicalAttributeInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt16));
}

std::vector<ebucoreTechnicalAttributeInt16*> ebucoreDataFormatBase::getdataTechnicalAttributeInt16() const
{
    vector<ebucoreTechnicalAttributeInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt32));
}

std::vector<ebucoreTechnicalAttributeInt32*> ebucoreDataFormatBase::getdataTechnicalAttributeInt32() const
{
    vector<ebucoreTechnicalAttributeInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt64));
}

std::vector<ebucoreTechnicalAttributeInt64*> ebucoreDataFormatBase::getdataTechnicalAttributeInt64() const
{
    vector<ebucoreTechnicalAttributeInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeUInt8() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt8));
}

std::vector<ebucoreTechnicalAttributeUInt8*> ebucoreDataFormatBase::getdataTechnicalAttributeUInt8() const
{
    vector<ebucoreTechnicalAttributeUInt8*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt8)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt8*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeUInt16() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt16));
}

std::vector<ebucoreTechnicalAttributeUInt16*> ebucoreDataFormatBase::getdataTechnicalAttributeUInt16() const
{
    vector<ebucoreTechnicalAttributeUInt16*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt16)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt16*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeUInt32() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt32));
}

std::vector<ebucoreTechnicalAttributeUInt32*> ebucoreDataFormatBase::getdataTechnicalAttributeUInt32() const
{
    vector<ebucoreTechnicalAttributeUInt32*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt32)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt32*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeUInt64() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt64));
}

std::vector<ebucoreTechnicalAttributeUInt64*> ebucoreDataFormatBase::getdataTechnicalAttributeUInt64() const
{
    vector<ebucoreTechnicalAttributeUInt64*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt64)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeUInt64*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeFloat() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeFloat));
}

std::vector<ebucoreTechnicalAttributeFloat*> ebucoreDataFormatBase::getdataTechnicalAttributeFloat() const
{
    vector<ebucoreTechnicalAttributeFloat*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeFloat)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeFloat*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeRational() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeRational));
}

std::vector<ebucoreTechnicalAttributeRational*> ebucoreDataFormatBase::getdataTechnicalAttributeRational() const
{
    vector<ebucoreTechnicalAttributeRational*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeRational)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeRational*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeAnyURI() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeAnyURI));
}

std::vector<ebucoreTechnicalAttributeAnyURI*> ebucoreDataFormatBase::getdataTechnicalAttributeAnyURI() const
{
    vector<ebucoreTechnicalAttributeAnyURI*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeAnyURI)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeAnyURI*>(iter->get()));
    }
    return result;
}

bool ebucoreDataFormatBase::havedataTechnicalAttributeBoolean() const
{
    return haveItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeBoolean));
}

std::vector<ebucoreTechnicalAttributeBoolean*> ebucoreDataFormatBase::getdataTechnicalAttributeBoolean() const
{
    vector<ebucoreTechnicalAttributeBoolean*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeBoolean)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTechnicalAttributeBoolean*>(iter->get()));
    }
    return result;
}

void ebucoreDataFormatBase::setdataFormatID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatID), value);
}

void ebucoreDataFormatBase::setdataFormatVersionID(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatVersionID), value);
}

void ebucoreDataFormatBase::setdataFormatName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatName), value);
}

void ebucoreDataFormatBase::setdataFormatDefinition(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataFormatDefinition), value);
}

void ebucoreDataFormatBase::setdataTrackId(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackId), value);
}

void ebucoreDataFormatBase::setdataTrackName(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackName), value);
}

void ebucoreDataFormatBase::setdataTrackLanguageCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreDataFormat, dataTrackLanguageCode), value);
}

void ebucoreDataFormatBase::setcaptioning(const std::vector<ebucoreCaptioning*>& value)
{
    WrapObjectVectorIterator<ebucoreCaptioning> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, captioning), &iter);
}

void ebucoreDataFormatBase::appendcaptioning(ebucoreCaptioning* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, captioning), value);
}

void ebucoreDataFormatBase::setsubtitling(const std::vector<ebucoreSubtitling*>& value)
{
    WrapObjectVectorIterator<ebucoreSubtitling> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, subtitling), &iter);
}

void ebucoreDataFormatBase::appendsubtitling(ebucoreSubtitling* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, subtitling), value);
}

void ebucoreDataFormatBase::setancillaryData(const std::vector<ebucoreAncillaryData*>& value)
{
    WrapObjectVectorIterator<ebucoreAncillaryData> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, ancillaryData), &iter);
}

void ebucoreDataFormatBase::appendancillaryData(ebucoreAncillaryData* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, ancillaryData), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeString(const std::vector<ebucoreTechnicalAttributeString*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeString> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeString), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeString(ebucoreTechnicalAttributeString* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeString), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeInt8(const std::vector<ebucoreTechnicalAttributeInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt8), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeInt8(ebucoreTechnicalAttributeInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt8), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeInt16(const std::vector<ebucoreTechnicalAttributeInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt16), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeInt16(ebucoreTechnicalAttributeInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt16), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeInt32(const std::vector<ebucoreTechnicalAttributeInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt32), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeInt32(ebucoreTechnicalAttributeInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt32), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeInt64(const std::vector<ebucoreTechnicalAttributeInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt64), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeInt64(ebucoreTechnicalAttributeInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeInt64), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeUInt8(const std::vector<ebucoreTechnicalAttributeUInt8*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt8> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt8), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeUInt8(ebucoreTechnicalAttributeUInt8* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt8), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeUInt16(const std::vector<ebucoreTechnicalAttributeUInt16*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt16> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt16), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeUInt16(ebucoreTechnicalAttributeUInt16* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt16), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeUInt32(const std::vector<ebucoreTechnicalAttributeUInt32*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt32> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt32), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeUInt32(ebucoreTechnicalAttributeUInt32* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt32), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeUInt64(const std::vector<ebucoreTechnicalAttributeUInt64*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeUInt64> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt64), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeUInt64(ebucoreTechnicalAttributeUInt64* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeUInt64), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeFloat(const std::vector<ebucoreTechnicalAttributeFloat*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeFloat> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeFloat), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeFloat(ebucoreTechnicalAttributeFloat* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeFloat), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeRational(const std::vector<ebucoreTechnicalAttributeRational*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeRational> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeRational), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeRational(ebucoreTechnicalAttributeRational* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeRational), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeAnyURI(const std::vector<ebucoreTechnicalAttributeAnyURI*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeAnyURI> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeAnyURI), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeAnyURI(ebucoreTechnicalAttributeAnyURI* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeAnyURI), value);
}

void ebucoreDataFormatBase::setdataTechnicalAttributeBoolean(const std::vector<ebucoreTechnicalAttributeBoolean*>& value)
{
    WrapObjectVectorIterator<ebucoreTechnicalAttributeBoolean> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeBoolean), &iter);
}

void ebucoreDataFormatBase::appenddataTechnicalAttributeBoolean(ebucoreTechnicalAttributeBoolean* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreDataFormat, dataTechnicalAttributeBoolean), value);
}

