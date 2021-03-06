/*
 *	Copyright 2012-2013 European Broadcasting Union and Limecraft, NV.
 *
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *	   http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 *
 */
 
#include <EBUCore_1_4/metadata/EBUCoreDMS++.h>

using namespace EBUSDK::EBUCore::EBUCore_1_4::KLV;

namespace EBUSDK {
namespace EBUCore {
namespace EBUCore_1_4 {

void RegisterExtensions(DataModel *data_model)
{
    // register AS-11 framework set and items in data model

#define MXF_LABEL(d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15) \
    {d0, d1, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15}

#define MXF_SET_DEFINITION(parent_name, name, label) \
    data_model->registerSetDef(#name, &MXF_SET_K(parent_name), &MXF_SET_K(name));

#define MXF_ITEM_DEFINITION(set_name, name, label, tag, type_id, is_required) \
    data_model->registerItemDef(#name, &MXF_SET_K(set_name), &MXF_ITEM_K(set_name, name), tag, type_id, is_required);

#include <EBUCore_1_4/metadata/ebucore_extensions_data_model.h>

    data_model->finalise();
}

void RegisterFrameworkObjectFactory(HeaderMetadata *header_metadata)
{
	header_metadata->registerObjectFactory(&ebucoreTextualAnnotation::setKey, new MetadataSetFactory<ebucoreTextualAnnotation>());
	header_metadata->registerObjectFactory(&ebucoreBasicLink::setKey, new MetadataSetFactory<ebucoreBasicLink>());
	header_metadata->registerObjectFactory(&ebucoreMainFramework::setKey, new MetadataSetFactory<ebucoreMainFramework>());
	header_metadata->registerObjectFactory(&ebucoreCoreMetadata::setKey, new MetadataSetFactory<ebucoreCoreMetadata>());
	header_metadata->registerObjectFactory(&ebucoreTitle::setKey, new MetadataSetFactory<ebucoreTitle>());
	header_metadata->registerObjectFactory(&ebucoreAlternativeTitle::setKey, new MetadataSetFactory<ebucoreAlternativeTitle>());
	header_metadata->registerObjectFactory(&ebucoreTypeGroup::setKey, new MetadataSetFactory<ebucoreTypeGroup>());
	header_metadata->registerObjectFactory(&ebucoreStatusGroup::setKey, new MetadataSetFactory<ebucoreStatusGroup>());
	header_metadata->registerObjectFactory(&ebucoreFormatGroup::setKey, new MetadataSetFactory<ebucoreFormatGroup>());
	header_metadata->registerObjectFactory(&ebucoreEntity::setKey, new MetadataSetFactory<ebucoreEntity>());
	header_metadata->registerObjectFactory(&ebucoreCompoundName::setKey, new MetadataSetFactory<ebucoreCompoundName>());
	header_metadata->registerObjectFactory(&ebucoreCountry::setKey, new MetadataSetFactory<ebucoreCountry>());
	header_metadata->registerObjectFactory(&ebucoreAddress::setKey, new MetadataSetFactory<ebucoreAddress>());
	header_metadata->registerObjectFactory(&ebucoreContact::setKey, new MetadataSetFactory<ebucoreContact>());
	header_metadata->registerObjectFactory(&ebucoreContactDetails::setKey, new MetadataSetFactory<ebucoreContactDetails>());
	header_metadata->registerObjectFactory(&ebucoreRole::setKey, new MetadataSetFactory<ebucoreRole>());
	header_metadata->registerObjectFactory(&ebucoreOrganisationDepartment::setKey, new MetadataSetFactory<ebucoreOrganisationDepartment>());
	header_metadata->registerObjectFactory(&ebucoreOrganisation::setKey, new MetadataSetFactory<ebucoreOrganisation>());
	header_metadata->registerObjectFactory(&ebucoreIdentifier::setKey, new MetadataSetFactory<ebucoreIdentifier>());
	header_metadata->registerObjectFactory(&ebucoreSubject::setKey, new MetadataSetFactory<ebucoreSubject>());
	header_metadata->registerObjectFactory(&ebucoreRating::setKey, new MetadataSetFactory<ebucoreRating>());
	header_metadata->registerObjectFactory(&ebucoreType::setKey, new MetadataSetFactory<ebucoreType>());
	header_metadata->registerObjectFactory(&ebucoreTargetAudience::setKey, new MetadataSetFactory<ebucoreTargetAudience>());
	header_metadata->registerObjectFactory(&ebucoreGenre::setKey, new MetadataSetFactory<ebucoreGenre>());
	header_metadata->registerObjectFactory(&ebucoreType::setKey, new MetadataSetFactory<ebucoreType>());
	header_metadata->registerObjectFactory(&ebucoreObjectType::setKey, new MetadataSetFactory<ebucoreObjectType>());
	header_metadata->registerObjectFactory(&ebucoreDescription::setKey, new MetadataSetFactory<ebucoreDescription>());
	header_metadata->registerObjectFactory(&ebucorePublicationHistoryEvent::setKey, new MetadataSetFactory<ebucorePublicationHistoryEvent>());
	header_metadata->registerObjectFactory(&ebucorePublicationChannel::setKey, new MetadataSetFactory<ebucorePublicationChannel>());
	header_metadata->registerObjectFactory(&ebucorePublicationHistory::setKey, new MetadataSetFactory<ebucorePublicationHistory>());
	header_metadata->registerObjectFactory(&ebucorePublicationMedium::setKey, new MetadataSetFactory<ebucorePublicationMedium>());
	header_metadata->registerObjectFactory(&ebucorePublicationService::setKey, new MetadataSetFactory<ebucorePublicationService>());
	header_metadata->registerObjectFactory(&ebucoreDateType::setKey, new MetadataSetFactory<ebucoreDate>());
	header_metadata->registerObjectFactory(&ebucoreDate::setKey, new MetadataSetFactory<ebucoreDate>());
	header_metadata->registerObjectFactory(&ebucoreLanguage::setKey, new MetadataSetFactory<ebucoreLanguage>());
	header_metadata->registerObjectFactory(&ebucoreCoordinates::setKey, new MetadataSetFactory<ebucoreCoordinates>());
	header_metadata->registerObjectFactory(&ebucoreRegion::setKey, new MetadataSetFactory<ebucoreRegion>());
	header_metadata->registerObjectFactory(&ebucoreSpatial::setKey, new MetadataSetFactory<ebucoreSpatial>());
	header_metadata->registerObjectFactory(&ebucoreLocation::setKey, new MetadataSetFactory<ebucoreLocation>());
	header_metadata->registerObjectFactory(&ebucoreTemporal::setKey, new MetadataSetFactory<ebucoreTemporal>());
	header_metadata->registerObjectFactory(&ebucorePeriodOfTime::setKey, new MetadataSetFactory<ebucorePeriodOfTime>());
	header_metadata->registerObjectFactory(&ebucoreCoverage::setKey, new MetadataSetFactory<ebucoreCoverage>());
	header_metadata->registerObjectFactory(&ebucoreVersion::setKey, new MetadataSetFactory<ebucoreVersion>());
	header_metadata->registerObjectFactory(&ebucoreRights::setKey, new MetadataSetFactory<ebucoreRights>());
	header_metadata->registerObjectFactory(&ebucoreFormat::setKey, new MetadataSetFactory<ebucoreFormat>());
	header_metadata->registerObjectFactory(&ebucoreAncillaryData::setKey, new MetadataSetFactory<ebucoreAncillaryData>());
	header_metadata->registerObjectFactory(&ebucoreWidth::setKey, new MetadataSetFactory<ebucoreWidth>());
	header_metadata->registerObjectFactory(&ebucoreHeight::setKey, new MetadataSetFactory<ebucoreHeight>());
	header_metadata->registerObjectFactory(&ebucoreAspectRatio::setKey, new MetadataSetFactory<ebucoreAspectRatio>());
	header_metadata->registerObjectFactory(&ebucoreAudioFormat::setKey, new MetadataSetFactory<ebucoreAudioFormat>());
	header_metadata->registerObjectFactory(&ebucoreCaptioning::setKey, new MetadataSetFactory<ebucoreCaptioning>());
	header_metadata->registerObjectFactory(&ebucoreSubtitling::setKey, new MetadataSetFactory<ebucoreSubtitling>());
	header_metadata->registerObjectFactory(&ebucoreCodec::setKey, new MetadataSetFactory<ebucoreCodec>());
	header_metadata->registerObjectFactory(&ebucoreDataFormat::setKey, new MetadataSetFactory<ebucoreDataFormat>());
	header_metadata->registerObjectFactory(&ebucoreDimension::setKey, new MetadataSetFactory<ebucoreDimension>());
	header_metadata->registerObjectFactory(&ebucoreImageFormat::setKey, new MetadataSetFactory<ebucoreImageFormat>());
	header_metadata->registerObjectFactory(&ebucoreMedium::setKey, new MetadataSetFactory<ebucoreMedium>());
	header_metadata->registerObjectFactory(&ebucorePackageInfo::setKey, new MetadataSetFactory<ebucorePackageInfo>());
	header_metadata->registerObjectFactory(&ebucorePartMetadata::setKey, new MetadataSetFactory<ebucorePartMetadata>());
	header_metadata->registerObjectFactory(&ebucorePartFramework::setKey, new MetadataSetFactory<ebucorePartFramework>());
	header_metadata->registerObjectFactory(&ebucoreRational::setKey, new MetadataSetFactory<ebucoreRational>());
	header_metadata->registerObjectFactory(&ebucoreSigningFormat::setKey, new MetadataSetFactory<ebucoreSigningFormat>());
	header_metadata->registerObjectFactory(&ebucoreTrack::setKey, new MetadataSetFactory<ebucoreTrack>());
	header_metadata->registerObjectFactory(&ebucoreVideoFormat::setKey, new MetadataSetFactory<ebucoreVideoFormat>());
	header_metadata->registerObjectFactory(&ebucoreBasicRelation::setKey, new MetadataSetFactory<ebucoreBasicRelation>());
	header_metadata->registerObjectFactory(&ebucoreCustomRelation::setKey, new MetadataSetFactory<ebucoreCustomRelation>());
	header_metadata->registerObjectFactory(&ebucoreMetadataSchemeInformation::setKey, new MetadataSetFactory<ebucoreMetadataSchemeInformation>());
	
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeAnyURI::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeAnyURI>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeString::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeString>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeBoolean::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeBoolean>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeFloat::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeFloat>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeRational::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeRational>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeInt8::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeInt8>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeInt16::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeInt16>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeInt32::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeInt32>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeInt64::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeInt64>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeUInt8::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeUInt8>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeUInt16::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeUInt16>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeUInt32::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeUInt32>());
	header_metadata->registerObjectFactory(&ebucoreTechnicalAttributeUInt64::setKey, new MetadataSetFactory<ebucoreTechnicalAttributeUInt64>());
}

} // namespace EBUCore_1_4
} // namespace EBUCore
} // namespace EBUSDK
