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
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>


using namespace std;
using namespace mxfpp;
using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;


const mxfKey ebucoreAddressBase::setKey = MXF_SET_K(ebucoreAddress);


ebucoreAddressBase::ebucoreAddressBase(HeaderMetadata *headerMetadata)
: InterchangeObject(headerMetadata, headerMetadata->createCSet(&setKey))
{
    headerMetadata->add(this);
}

ebucoreAddressBase::ebucoreAddressBase(HeaderMetadata *headerMetadata, ::MXFMetadataSet *cMetadataSet)
: InterchangeObject(headerMetadata, cMetadataSet)
{}

ebucoreAddressBase::~ebucoreAddressBase()
{}


bool ebucoreAddressBase::havedeliveryCode() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode));
}

std::string ebucoreAddressBase::getdeliveryCode() const
{
    return getStringItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode));
}

bool ebucoreAddressBase::havetownCity() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, townCity));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::gettownCity() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::havecountyState() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, countyState));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::getcountyState() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::havecountry() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, country));
}

std::vector<ebucoreCountry*> ebucoreAddressBase::getcountry() const
{
    vector<ebucoreCountry*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreCountry*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreCountry*>(iter->get()));
    }
    return result;
}

bool ebucoreAddressBase::haveaddressLines() const
{
    return haveItem(&MXF_ITEM_K(ebucoreAddress, addressLines));
}

std::vector<ebucoreTextualAnnotation*> ebucoreAddressBase::getaddressLines() const
{
    vector<ebucoreTextualAnnotation*> result;
    auto_ptr<ObjectIterator> iter(getStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines)));
    while (iter->next())
    {
        MXFPP_CHECK(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()) != 0);
        result.push_back(dynamic_cast<ebucoreTextualAnnotation*>(iter->get()));
    }
    return result;
}

void ebucoreAddressBase::setdeliveryCode(std::string value)
{
    setStringItem(&MXF_ITEM_K(ebucoreAddress, deliveryCode), value);
}

void ebucoreAddressBase::settownCity(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity), &iter);
}

void ebucoreAddressBase::appendtownCity(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, townCity), value);
}

void ebucoreAddressBase::setcountyState(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState), &iter);
}

void ebucoreAddressBase::appendcountyState(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, countyState), value);
}

void ebucoreAddressBase::setcountry(const std::vector<ebucoreCountry*>& value)
{
    WrapObjectVectorIterator<ebucoreCountry> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country), &iter);
}

void ebucoreAddressBase::appendcountry(ebucoreCountry* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, country), value);
}

void ebucoreAddressBase::setaddressLines(const std::vector<ebucoreTextualAnnotation*>& value)
{
    WrapObjectVectorIterator<ebucoreTextualAnnotation> iter(value);
    setStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines), &iter);
}

void ebucoreAddressBase::appendaddressLines(ebucoreTextualAnnotation* value)
{
    appendStrongRefArrayItem(&MXF_ITEM_K(ebucoreAddress, addressLines), value);
}
