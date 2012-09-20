/*#include <iostream>
#include <fstream>
#include <memory>

#include <bmx/BMXException.h>
#include <bmx/Logging.h>*/

#include "EBUCoreMapping.h"
#include "AppUtils.h"

#include <xercesc/util/TransService.hpp>

using namespace ebuCore_2012;
using namespace mxfpp;
//using namespace bmx;

namespace EBUSDK {
namespace EBUCore {

#define	SIMPLE_MAP(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty().get());
#define	SIMPLE_MAP_NO_GET(source, sourceProperty, dest, destProperty)	\
	dest->destProperty(source.sourceProperty());

#define	SIMPLE_MAP_OPTIONAL(source, sourceProperty, dest, destProperty)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(source.sourceProperty().get());
#define	SIMPLE_MAP_OPTIONAL_CONVERT(source, sourceProperty, dest, destProperty, convertFunction)	\
	if (source.sourceProperty().present())	\
		dest->destProperty(convertFunction(source.sourceProperty().get()));

#define NEW_OBJECT_AND_ASSIGN(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	{	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty(), obj, mod);	\
		dest->destProperty(obj);	\
	}

#define NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj, mod);	\
		dest->destProperty(obj);	\
	}

#define NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, iteratorType, mapMethod, dest, destProperty)	\
	{ std::vector<destType*> vec_dest_destProperty;	\
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(*it, obj, mod);	\
		vec_dest_destProperty.push_back(obj);	\
	}	\
	dest->destProperty(vec_dest_destProperty); }

#define NEW_VECTOR_AND_APPEND(source, sourceProperty, destType, iteratorType, mapMethod, dest, destVector)	\
	{ \
	for (iteratorType it = source.sourceProperty().begin(); it != source.sourceProperty().end(); it++) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(*it, obj, mod);	\
		destVector.push_back(obj);	\
	} }

#define	SIMPLE_MAP_OPTIONAL_TO_NEW_VECTOR_AND_ASSIGN(source, sourceProperty, destType, mapMethod, dest, destProperty) \
	if (source.sourceProperty().present()) {	\
		destType *obj = newAndModifyObject<destType>(dest->getHeaderMetadata(), mod);	\
		mapMethod(source.sourceProperty().get(), obj, mod);	\
		std::vector<destType*> v_dest_destProperty;	\
		v_dest_destProperty.push_back(obj);	\
		dest->destProperty(v_dest_destProperty);	\
	}

#define MAP_TYPE_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, typeDefinition, dest, settypeGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, typeLabel, dest, settypeGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, typeLink, dest, settypeGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, typeLanguage, dest, settypeGroupLanguage)

	/*
	This macro is not defined as a function since typeGroups are not separate types 
	but are more like duck typing (just a group of included attributes).
	Same for other such groups (format-, status-)
	*/

#define MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreTypeGroup *typeGroup = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);	\
	MAP_TYPE_GROUP(source, typeGroup)	\
	dest->destProperty(typeGroup);	\


#define MAP_STATUS_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, statusDefinition, dest, setstatusGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, statusLabel, dest, setstatusGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, statusLink, dest, setstatusGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, statusLanguage, dest, setstatusGroupLanguage)

#define MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreStatusGroup *statusGroup = newAndModifyObject<ebucoreStatusGroup>(dest->getHeaderMetadata(), mod); \
	MAP_STATUS_GROUP(source, statusGroup)	\
	dest->destProperty(statusGroup);


#define MAP_FORMAT_GROUP(source, dest)	\
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setformatGroupDefinition) \
	SIMPLE_MAP_OPTIONAL(source, formatLabel, dest, setformatGroupLabel) \
	SIMPLE_MAP_OPTIONAL(source, formatLink, dest, setformatGroupLink) \
	SIMPLE_MAP_OPTIONAL(source, formatLanguage, dest, setformatGroupLanguage)

#define MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, destProperty) \
	ebucoreFormatGroup *statusGroup = newAndModifyObject<ebucoreFormatGroup>(dest->getHeaderMetadata(), mod);	\
	MAP_FORMAT_GROUP(source, statusGroup)	\
	dest->destProperty(statusGroup);

template <class T> T* newAndModifyObject(HeaderMetadata *headerMetadata, ObjectModifier *mod) {
	T *obj = new T(headerMetadata);
	if (mod != NULL)
		mod->Modify(obj);
	return obj;
}

void mapRole(role& source, ebucoreTypeGroup *dest, ObjectModifier* mod = NULL) {
	MAP_TYPE_GROUP(source, dest)
}

void mapTextualAnnotation(std::string source, ebucoreTextualAnnotation *dest, ObjectModifier* mod = NULL) {
	/* cannot deal with lang as source is single string */
	dest->settext(source);
}

void mapTextualAnnotation(dc::elementType source, ebucoreTextualAnnotation *dest, ObjectModifier* mod = NULL) {
	dest->settext(source);
	dest->settextLanguage(source.lang());
}

void mapAddress(addressType& source, ebucoreAddress *dest, ObjectModifier* mod = NULL) {

	if (source.addressLine().size() > 0) {
		NEW_VECTOR_AND_ASSIGN(source, addressLine, ebucoreTextualAnnotation, addressType::addressLine_iterator, mapTextualAnnotation, dest, setaddressLines)
	}
	
	SIMPLE_MAP_OPTIONAL(source, addressTownCity, dest, settownCity)
	SIMPLE_MAP_OPTIONAL(source, addressCountyState, dest, setcountyState)
	SIMPLE_MAP_OPTIONAL(source, addressDeliveryCode, dest, setdeliveryCode)

	// special treatment for country, current KLV mapping is not via a typeGroup!
	if (source.country().present()) {
		addressType::country_type& c = source.country().get();
		SIMPLE_MAP_OPTIONAL(c, typeLink, dest, setcountryCode)
		SIMPLE_MAP_OPTIONAL(c, typeLabel, dest, setcountryName)
	}
}

void mapDetails(detailsType& source, ebucoreContactDetails *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element name="emailAddress" type="string" minOccurs="0">
			</element>
			<element name="webAddress" type="string" minOccurs="0">
			</element>
			<element name="address" type="ebucore:addressType" minOccurs="0">
			</element>
			<element name="telephoneNumber" type="string" minOccurs="0"/>
			<element name="mobileTelephoneNumber" type="string" minOccurs="0"/>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup"/>
	*/
	NEW_VECTOR_AND_ASSIGN(source, emailAddress, ebucoreTextualAnnotation, detailsType::emailAddress_iterator, mapTextualAnnotation, dest, setemailAddress)
	SIMPLE_MAP_OPTIONAL(source, webAddress, dest, setwebAddress)

	// map address
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, address, ebucoreAddress, mapAddress, dest, setaddress)
	SIMPLE_MAP_OPTIONAL(source, telephoneNumber, dest, settelephoneNumber)
	SIMPLE_MAP_OPTIONAL(source, mobileTelephoneNumber, dest, setmobileTelephoneNumber)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdetailsType)
}

void mapContact(contactDetailsType& source, ebucoreContact *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, contactId, dest, setcontactId)

	SIMPLE_MAP_OPTIONAL(source, name, dest, setcontactName)
	SIMPLE_MAP_OPTIONAL(source, givenName, dest, setgivenName)
	SIMPLE_MAP_OPTIONAL(source, familyName, dest, setfamilyName)
	SIMPLE_MAP_OPTIONAL(source, suffix, dest, setsuffix)
	SIMPLE_MAP_OPTIONAL(source, salutation, dest, setsalutation)

	NEW_VECTOR_AND_ASSIGN(source, otherGivenName, ebucoreTextualAnnotation, contactDetailsType::otherGivenName_iterator, mapTextualAnnotation, dest, setotherGivenName)
	NEW_VECTOR_AND_ASSIGN(source, username, ebucoreTextualAnnotation, contactDetailsType::username_iterator, mapTextualAnnotation, dest, setusername)
	SIMPLE_MAP_OPTIONAL(source, occupation, dest, setoccupation)
	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setcontactDetails)
	NEW_VECTOR_AND_ASSIGN(source, stageName, ebucoreTextualAnnotation, contactDetailsType::stageName_iterator, mapTextualAnnotation, dest, setstageName)
	NEW_VECTOR_AND_ASSIGN(source, relatedContacts, ebucoreEntity, contactDetailsType::relatedContacts_iterator, mapEntity, dest, setcontactRelatedContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcontactType)
}

void mapOrganisationDepartment(organisationDepartment& source, ebucoreOrganisationDepartment *dest, ObjectModifier* mod = NULL) {
	dest->setdepartmentName(source);
	SIMPLE_MAP_OPTIONAL(source, departmentId, dest, setdepartmentId)
}

void mapOrganisation(organisationDetailsType& source, ebucoreOrganisation *dest, ObjectModifier* mod = NULL) {

	// [TODO] The KLV mapping is somewhat inconsistent at this point with the XSD:
	//		- XSD does not define an organisationCode
	//		- XSD departmentId is not present in KLV

	SIMPLE_MAP_OPTIONAL(source, organisationId, dest, setorganisationId)

	NEW_VECTOR_AND_ASSIGN(source, organisationName, ebucoreTextualAnnotation, organisationDetailsType::organisationName_iterator, mapTextualAnnotation, dest, setorganisationName)
	NEW_VECTOR_AND_ASSIGN(source, organisationCode, ebucoreTextualAnnotation, organisationDetailsType::organisationCode_iterator, mapTextualAnnotation, dest, setorganisationCode)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, organisationDepartment, ebucoreOrganisationDepartment, mapOrganisationDepartment, dest, setorganisationDepartment)

	NEW_VECTOR_AND_ASSIGN(source, details, ebucoreContactDetails, contactDetailsType::details_sequence::iterator, mapDetails, dest, setorganisationDetails)
	NEW_VECTOR_AND_ASSIGN(source, contacts, ebucoreEntity, organisationDetailsType::contacts_iterator, mapEntity, dest, setorganisationRelatedContacts)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setorganisationType)
}

void mapEntity(entityType& source, ebucoreEntity *dest, ObjectModifier* mod) {
	SIMPLE_MAP_OPTIONAL(source, entityId, dest, setentityId)
	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, entityType::contactDetails_iterator, mapContact, dest, setentityContact)
	NEW_VECTOR_AND_ASSIGN(source, organisationDetails, ebucoreOrganisation, entityType::organisationDetails_iterator, mapOrganisation, dest, setentityOrganisation)
	NEW_VECTOR_AND_ASSIGN(source, role, ebucoreTypeGroup, entityType::role_iterator, mapRole, dest, setentityRole)
}

void mapMetadataSchemeInformation(ebuCoreMainType& source, ebucoreMetadataSchemeInformation *dest, ObjectModifier* mod) {
	/*
	<sequence>
		<element name="coreMetadata" type="ebucore:coreMetadataType">
		</element>
		<element name="metadataProvider" type="ebucore:entityType" minOccurs="0">
		</element>
	</sequence>
	<attribute name="schema" default="EBU_CORE_20110531.xsd">
	</attribute>
	<attribute name="version" default="1.3">
	</attribute>
	<attribute name="dateLastModified" type="date">
	</attribute>
	<attribute name="documentId" type="NMTOKEN">
	</attribute>
	<attribute ref="xml:lang">
	</attribute>
	*/

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, metadataProvider, ebucoreEntity, mapEntity, dest, setebucoreMetadataProvider)

	// is there a version node? appearently, no easier way to check than
	// to look through the attributes of the source node and see if there 
	// is a matching attribute
	xercesc_3_1::DOMNamedNodeMap* attrs = source._node()->getAttributes();
	XMLCh* str_version = xercesc_3_1::XMLString::transcode("version");
	const xercesc_3_1::DOMNode* version_node = attrs->getNamedItem(str_version);
	xercesc_3_1::XMLString::release(&str_version);
	if (version_node != NULL) {
		xercesc_3_1::TranscodeToStr version(source.version()._node()->getTextContent(), "UTF-8");
		std::string std_version((char*)version.str());
		dest->setebucoreMetadataSchemeVersion(std_version);
	}
	/* EBUCore1.4:
	XMLCh* str_schema = xercesc_3_1::XMLString::transcode("schema");
	const xercesc_3_1::DOMNode* schema_node = attrs->getNamedItem(str_schema);
	xercesc_3_1::XMLString::release(&str_schema);
	if (schema_node != NULL) {
		xercesc_3_1::TranscodeToStr schema(source.schema()._node()->getTextContent(), "UTF-8");
		std::string std_schema((char*)schema.str());
		dest->setebucoreMetadataScheme(std_schema);
	}*/
}

mxfTimestamp convert_timestamp(xml_schema::date& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.day = source.day();
	ts.month = source.month();
	ts.year = source.year();
	return ts;
}

mxfTimestamp convert_timestamp(xml_schema::gyear& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.year = source.year();
	return ts;
}

std::string convert(xml_schema::gyear& source) {
	std::stringstream ss;
	ss << source.year();
	return ss.str();
}

std::string convert(xml_schema::date& source) {
	std::stringstream ss;
	ss << source.day() << '/' << source.month() << '/' << source.year();
	return ss.str();
}

std::string convert(xml_schema::time& source) {
	std::stringstream ss;
	ss << source.hours() << ':' << source.minutes() << ':' << source.seconds();
	return ss.str();
}

mxfTimestamp convert_timestamp(xml_schema::time& source) {
	mxfTimestamp ts = {0,0,0,0,0,0,0};
	ts.hour = source.hours();
	ts.min = source.minutes();
	ts.sec = source.seconds();
	return ts;
}

std::string convert(xml_schema::idrefs& source) {
	std::stringstream ss;
	size_t l = source.size(); size_t i = 0;
	for (xml_schema::idrefs::iterator it = source.begin(); it != source.end(); it++) {
		i++;
		ss << (*it);
		if (i < l) ss << ' ';
	}
	return ss.str();
}

mxfRational convert(xml_schema::long_& source) {
	mxfRational r = {source, 1};
	return r;
}

mxfRational convert(rationalType& source) {
	mxfRational r = {source.factorNumerator(), source.factorDenominator()};
	return r;
}

std::string convert_to_string(::xml_schema::integer& source) {
	std::stringstream ss;
	ss << source;
	return ss.str();
}

mxfRational convert_rational(xml_schema::duration& source) {
	mxfRational r = { 
	   (source.years() * 365 * 86400 + 
		source.months() * 30 * 86400 + 
		source.days() * 86400 + 
		source.hours() * 3600 + 
		source.minutes() * 60 + 
		source.seconds()) * 100,
	100};
	return r;
}

mxfRational convert_rational(xml_schema::time& source) {
	mxfRational r = { 
	   (source.hours() * 3600 + 
		source.minutes() * 60 + 
		source.seconds()) * 100,
	100};
	return r;
}

void mapTitle(titleType& source, ebucoreTitle *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTextualAnnotation, titleType::title_iterator, mapTextualAnnotation, dest, settitleValue)

	SIMPLE_MAP_OPTIONAL(source, note, dest, settitleNote)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, attributiondate, dest, settitleAttributionDate, convert_timestamp)
}

void mapAlternativeTitle(alternativeTitleType& source, ebucoreAlternativeTitle *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTextualAnnotation, alternativeTitleType::title_iterator, mapTextualAnnotation, dest, setalternativeTitleValue)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setalternativeTitleNote)

	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setalternativeTitleAttributionDate, convert_timestamp)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setalternativeTitleTypeGroup)
	MAP_NEW_STATUS_GROUP_AND_ASSIGN(source, dest, setalternativeTitleStatusGroup)
}

void mapIdentifier(identifierType& source, ebucoreIdentifier *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_NO_GET(source, identifier, dest, setidentifierValue)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setidentifierNote)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setidentifierTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setidentifierFormatGroup)

	if (source.attributor().present()) {
		ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
		mapEntity(source.attributor().get(), obj);
		dest->setidentifierAttributorEntity(obj);
	}
}

void mapDescription(descriptionType& source, ebucoreDescription *dest, ObjectModifier* mod = NULL) {
	NEW_VECTOR_AND_ASSIGN(source, description, ebucoreTextualAnnotation, descriptionType::description_iterator, mapTextualAnnotation, dest, setdescriptionValue)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdescriptionTypeGroup)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setdescriptionNote)
}

void mapSubject(subjectType& source, ebucoreSubject *dest, ObjectModifier* mod = NULL) {
	NEW_OBJECT_AND_ASSIGN(source, subject, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setsubjectValue)

	SIMPLE_MAP_OPTIONAL(source, subjectCode, dest, setsubjectCode)
	SIMPLE_MAP_OPTIONAL(source, subjectDefinition, dest, setsubjectDefinition)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setsubjectNote)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsubjectTypeGroup)

	if (source.attributor().present()) {
		ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
		mapEntity(source.attributor().get(), obj);
		dest->setsubjectAttributorEntity(obj);
	}
}

void mapRating(ratingType& source, ebucoreRating *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element name="ratingValue" type="string"/>
			<element name="ratingScaleMaxValue" type="string"/>
			<element name="ratingScaleMinValue" type="string"/>
			<element name="ratingProvider" type="ebucore:entityType"/>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup"/>
		<attributeGroup ref="ebucore:formatGroup"/>
	*/
	SIMPLE_MAP_NO_GET(source, ratingValue, dest, setratingValue)
	SIMPLE_MAP_NO_GET(source, ratingScaleMaxValue, dest, setratingScaleMaxValue)
	SIMPLE_MAP_NO_GET(source, ratingScaleMinValue, dest, setratingScaleMinValue)

	ebucoreEntity *obj = newAndModifyObject<ebucoreEntity>(dest->getHeaderMetadata(), mod);
	mapEntity(source.ratingProvider(), obj);
	dest->setratingProviderEntity(obj);

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setratingTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setratingFormatGroup)
}

void mapVersion(coreMetadataType::version_type& source, ebucoreVersion *dest, ObjectModifier* mod = NULL) {
	/*
	  <xs:simpleContent>
		<xs:extension base="xs:string">
			<xs:attribute ref="xml:lang" use="optional" default="en"/>
		</xs:extension>
	  </xs:simpleContent>
	*/

	dest->setversionValue(source);
	SIMPLE_MAP_NO_GET(source, lang, dest, setversionLanguage)
}

void mapLanguage(languageType& source, ebucoreLanguage *dest, ObjectModifier* mod = NULL) {
	/*
		<sequence>
			<element ref="dc:language" minOccurs="0">
			</element>
		</sequence>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="note" type="string">
		</attribute>
	*/

	// TODO: KLV Language has an indirection for languagepurpose via a languagepurposeset which contains
	// only a reference to the typegroup, required?
	SIMPLE_MAP_OPTIONAL(source, language, dest, setlanguageLanguage)
	if (source.language().present())
		dest->setlanguageCode(source.language().get().lang());
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlanguagePurposeSet)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setlanguageNote)
}

void mapType(typeType& source, ebucoreType *dest, ObjectModifier* mod = NULL) {

	NEW_VECTOR_AND_ASSIGN(source, type, ebucoreTextualAnnotation, typeType::type_iterator, mapTextualAnnotation, dest, settypeValue)
	
	std::vector<ebucoreObjectType*> vec_dest_objecttype;
	for (typeType::objectType_iterator it = source.objectType().begin(); it != source.objectType().end(); it++) {
		ebucoreObjectType *obj = newAndModifyObject<ebucoreObjectType>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.objectType().front(), obj, setobjectTypeGroup)
		vec_dest_objecttype.push_back(obj);
	}
	dest->setobjectType(vec_dest_objecttype);

	std::vector<ebucoreTargetAudience*> v1;
	for (typeType::targetAudience_sequence::iterator it = source.targetAudience().begin(); it != source.targetAudience().end(); it++) {
		ebucoreTargetAudience *obj = newAndModifyObject<ebucoreTargetAudience>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN((*it), obj, settargetAudienceKindGroup)
		v1.push_back(obj);
	}
	dest->settargetAudience(v1);

	std::vector<ebucoreGenre*> v2;
	for (typeType::genre_sequence::iterator it = source.genre().begin(); it != source.genre().end(); it++) {
		ebucoreGenre *obj = newAndModifyObject<ebucoreGenre>(dest->getHeaderMetadata(), mod);
		MAP_NEW_TYPE_GROUP_AND_ASSIGN((*it), obj, setgenreKindGroup)
		v2.push_back(obj);
	}
	dest->setgenre(v2);

	SIMPLE_MAP_OPTIONAL(source, note, dest, settypeNote)
}

void mapDateType(alternative& source, ebucoreDateType *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setdateValue, convert_timestamp)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setdateTypeGroup)
}

void mapDate(dateType& source, ebucoreDate* dest, ObjectModifier* mod = NULL) {
	// no valid mapping currently for a single note element (DC date is candidate, but cardinality is wrong)

	if (source.created().present()) {
		dateType::created_type& date = source.created().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearCreated, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateCreated, convert_timestamp)
	}
	if (source.issued().present()) {
		dateType::issued_type& date = source.issued().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearIssued, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateIssued, convert_timestamp)
	}
	if (source.modified().present()) {
		dateType::modified_type& date = source.modified().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearModified, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateModified, convert_timestamp)
	}
	if (source.digitised().present()) {
		dateType::digitised_type& date = source.digitised().get();
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startYear, dest, setyearDigitized, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(date, startDate, dest, setdateDigitized, convert_timestamp)
	}

	NEW_VECTOR_AND_ASSIGN(source, alternative, ebucoreDateType, dateType::alternative_iterator, mapDateType, dest, setalternativeDate)
}

void mapPeriodOfTime(PeriodOfTime& source, ebucorePeriodOfTime* dest, ObjectModifier* mod = NULL) {
	// [TODO] PeriodId is at temporal level
	//SIMPLE_MAP_OPTIONAL(source, period, dest, setperiodId)
	SIMPLE_MAP_OPTIONAL(source, periodName, dest, setperiodName)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startYear, dest, setperiodStartYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startDate, dest, setperiodStartDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, startTime, dest, setperiodStartTime, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endYear, dest, setperiodEndYear, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endDate, dest, setperiodEndDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, endTime, dest, setperiodEndTime, convert_timestamp)
}

void mapTemporal(temporal& source, ebucoreTemporal *dest, ObjectModifier* mod = NULL) {
	// [EBUCore1.4] PeriodId in temporal??
	NEW_VECTOR_AND_ASSIGN(source, PeriodOfTime, ebucorePeriodOfTime, temporal::PeriodOfTime_iterator, mapPeriodOfTime, dest, setperiodOfTime)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settemporalTypeGroup)
	SIMPLE_MAP_OPTIONAL(source, note, dest, settemporalDefinitionNote)
}

void mapLocation(spatial::location_type& source, ebucoreLocation *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, locationId, dest, setlocationId)
	SIMPLE_MAP_OPTIONAL(source, name, dest, setlocationName)
	SIMPLE_MAP_OPTIONAL(source, code, dest, setlocationCode)
	SIMPLE_MAP_OPTIONAL(source, note, dest, setlocationNote)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlocationTypeGroup)
}

void mapCoordinates(coordinates& source, ebucoreCoordinates *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_NO_GET(source, posx, dest, setposX)
	SIMPLE_MAP_NO_GET(source, posy, dest, setposY)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setcoordinatesFormatGroup)
}

void mapSpatial(spatial& source, ebucoreSpatial *dest, ObjectModifier* mod = NULL) {
	std::vector<ebucoreLocation*> vec_dest_locs;
	std::vector<ebucoreCoordinates*> vec_dest_coords;

	for (spatial::location_iterator it = source.location().begin(); it != source.location().end(); it++) {
		ebucoreLocation *obj = newAndModifyObject<ebucoreLocation>(dest->getHeaderMetadata(), mod);
		mapLocation(*it, obj, mod);

		if ((*it).coordinates().present()) {
			// also map the coordinates of this location
			ebucoreCoordinates *coords = newAndModifyObject<ebucoreCoordinates>(dest->getHeaderMetadata(), mod);
			mapCoordinates((*it).coordinates().get(), coords);
			vec_dest_coords.push_back(coords);

			obj->setcoordinateReference(coords);
		}
		vec_dest_locs.push_back(obj);
	}

	dest->setlocation(vec_dest_locs);
	dest->setcoordinates(vec_dest_coords);
}

void mapMetadataCoverage(coverageType& source, ebucoreCoverage *dest, ObjectModifier* mod = NULL) {
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coverage, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setcoverageValue)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, temporal, ebucoreTemporal, mapTemporal, dest, settemporal)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, spatial, ebucoreSpatial, mapSpatial, dest, setspatial)
}

void mapRights(rightsType& source, ebucoreRights *dest, std::map<xml_schema::id, ebucoreFormat*>& formatMap, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, rightsID, dest, setrightsId)
	NEW_VECTOR_AND_ASSIGN(source, rightsAttributedId, ebucoreIdentifier, rightsType::rightsAttributedId_iterator, mapIdentifier, dest, setrightsAttributeID)
	NEW_VECTOR_AND_ASSIGN(source, rights, ebucoreTextualAnnotation, rightsType::rights_iterator, mapTextualAnnotation, dest, setrightsValue)
	SIMPLE_MAP_OPTIONAL(source, rightsClearanceFlag, dest, setrightsClearanceFlag)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, exploitationIssues, ebucoreTextualAnnotation, mapTextualAnnotation, dest, setexploitationIssues)
	SIMPLE_MAP_OPTIONAL(source, rightsLink, dest, setrightsLink)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, coverage, ebucoreCoverage, mapMetadataCoverage, dest, setrightsCoverage)

	NEW_VECTOR_AND_ASSIGN(source, rightsHolder, ebucoreEntity, rightsType::rightsHolder_iterator, mapEntity, dest, setrightsHolderEntity)

	NEW_VECTOR_AND_ASSIGN(source, contactDetails, ebucoreContact, rightsType::contactDetails_sequence::iterator, mapContact, dest, setrightsContacts)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setrightsTypeGroup)

	// [TODO] Deal with format references
	//SIMPLE_MAP_OPTIONAL_CONVERT(source, formatIDRefs, dest, setrightsFormatIDRef, convert)

	// find this formatIdRef in the map of formats
	if (source.formatIDRefs().present()) {
		std::vector<ebucoreFormat*> destRefs;
		rightsType::formatIDRefs_type& refs = source.formatIDRefs().get();
		for (xml_schema::idrefs::iterator it = refs.begin(); it != refs.end(); it++) {
			if (formatMap.find(*it) != formatMap.end()) {
				// present!
				destRefs.push_back(formatMap[*it]);
			}
		}
		if (destRefs.size() > 0)
			dest->setrightsFormatReferences(destRefs);
	}

}

void mapPublicationHistoryEvent(publicationEvent& source, ebucorePublicationHistoryEvent* dest, std::map<xml_schema::id, ebucoreFormat*>& formatMap, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, firstShowing, dest, setfirstPublicationFlag)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationDate, dest, setpublicationDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, publicationTime, dest, setpublicationDate, convert_timestamp)
	SIMPLE_MAP_OPTIONAL(source, publicationChannel, dest, setpublicationChannel)
	SIMPLE_MAP_OPTIONAL(source, publicationService, dest, setpublicationService)

	if (source.publicationMedium().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.publicationMedium().get(), dest, setpublicationMedium)
	}

	if (source.formatIdRef().present()) {
		// find this formatIdRef in the map of formats
		if (formatMap.find(source.formatIdRef().get()) != formatMap.end()) {
			// present!
			dest->setpublicationFormatReference(formatMap[source.formatIdRef().get()]);
		}
	}
}

void mapPublicationHistory(publicationHistoryType& source, std::vector<ebucorePublicationHistoryEvent*>& dest, mxfpp::HeaderMetadata *header_metadata, std::map<xml_schema::id, ebucoreFormat*>& formatMap, ObjectModifier* mod = NULL) {

	std::vector<ebucorePublicationHistoryEvent*> vec_dest_hist;
	for (publicationHistoryType::publicationEvent_iterator it = source.publicationEvent().begin(); it != source.publicationEvent().end(); it++) {
		ebucorePublicationHistoryEvent *obj = newAndModifyObject<ebucorePublicationHistoryEvent>(header_metadata, mod);
		mapPublicationHistoryEvent(*it, obj, formatMap, mod);
		vec_dest_hist.push_back(obj);
	}
	dest.assign(vec_dest_hist.begin(), vec_dest_hist.end());
}

#define MAP_BASIC_RELATION_FUNCTION(destProperty) \
	void mapBasicRelation_##destProperty(relationType& source, ebucoreBasicRelation *dest, ObjectModifier* mod = NULL) { \
		SIMPLE_MAP_OPTIONAL(source, relationLink, dest, destProperty) \
	}

MAP_BASIC_RELATION_FUNCTION(setisVersionOf)
MAP_BASIC_RELATION_FUNCTION(sethasVersion)
MAP_BASIC_RELATION_FUNCTION(setisReplacedBy)
MAP_BASIC_RELATION_FUNCTION(setreplaces)
MAP_BASIC_RELATION_FUNCTION(setisRequiredBy)
MAP_BASIC_RELATION_FUNCTION(setrequires)
MAP_BASIC_RELATION_FUNCTION(setisPartOf)
MAP_BASIC_RELATION_FUNCTION(sethasPart)
MAP_BASIC_RELATION_FUNCTION(setisReferencedBy)
MAP_BASIC_RELATION_FUNCTION(setreferences)
MAP_BASIC_RELATION_FUNCTION(setisFormatOf)
MAP_BASIC_RELATION_FUNCTION(sethasFormat)
MAP_BASIC_RELATION_FUNCTION(setisEpisodeOf)
MAP_BASIC_RELATION_FUNCTION(setisMemberOf)

void mapBasicRelations(coreMetadataType& source, ebucoreCoreMetadata *dest, ObjectModifier* mod = NULL) {
	std::vector<ebucoreBasicRelation*> rels;

	NEW_VECTOR_AND_APPEND(source, isVersionOf, ebucoreBasicRelation, 
		coreMetadataType::isVersionOf_iterator, mapBasicRelation_setisVersionOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasVersion, ebucoreBasicRelation, 
		coreMetadataType::hasVersion_iterator, mapBasicRelation_sethasVersion, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isReplacedBy, ebucoreBasicRelation, 
		coreMetadataType::isReplacedBy_iterator, mapBasicRelation_setisReplacedBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, replaces, ebucoreBasicRelation, 
		coreMetadataType::replaces_iterator, mapBasicRelation_setreplaces, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isRequiredBy, ebucoreBasicRelation, 
		coreMetadataType::isRequiredBy_iterator, mapBasicRelation_setisRequiredBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, requires, ebucoreBasicRelation, 
		coreMetadataType::requires_iterator, mapBasicRelation_setrequires, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isPartOf, ebucoreBasicRelation, 
		coreMetadataType::isPartOf_iterator, mapBasicRelation_setisPartOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasPart, ebucoreBasicRelation, 
		coreMetadataType::hasPart_iterator, mapBasicRelation_sethasVersion, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isReferencedBy, ebucoreBasicRelation, 
		coreMetadataType::isReferencedBy_iterator, mapBasicRelation_setisReferencedBy, dest, rels)
	NEW_VECTOR_AND_APPEND(source, references, ebucoreBasicRelation, 
		coreMetadataType::references_iterator, mapBasicRelation_setreferences, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isFormatOf, ebucoreBasicRelation, 
		coreMetadataType::isFormatOf_iterator, mapBasicRelation_setisFormatOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, hasFormat, ebucoreBasicRelation, 
		coreMetadataType::hasFormat_iterator, mapBasicRelation_sethasFormat, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isEpisodeOf, ebucoreBasicRelation, 
		coreMetadataType::isEpisodeOf_iterator, mapBasicRelation_setisEpisodeOf, dest, rels)
	NEW_VECTOR_AND_APPEND(source, isMemberOf, ebucoreBasicRelation, 
		coreMetadataType::isMemberOf_iterator, mapBasicRelation_setisMemberOf, dest, rels)

	dest->setbasicRelation(rels);
}

void mapCustomRelation(relationType& source, ebucoreCustomRelation *dest, ObjectModifier* mod = NULL) {
	/*
		<choice>
			<element ref="dc:relation">
			</element>
			<element name="relationIdentifier" type="ebucore:identifierType">
			</element>
			<element name="relationLink" type="anyURI">
			</element>
		</choice>
		<attributeGroup ref="ebucore:typeGroup">
		</attributeGroup>
		<attribute name="runningOrderNumber" type="integer">
		</attribute>
		<attribute name="note" type="string">
		</attribute>
	*/

	// [TODO] XSD relationIdentifier is identifierType, KLV identifier is a UMID, how do we resolve?
	// [TODO] KLV totalNumberOfGroupMembers should be resolved by other means that just the EBU-Core source XML document?
	// [TODO] KLV orderedGroupFlag should be resolved by other means that just the EBU-Core source XML document?

	SIMPLE_MAP_OPTIONAL(source, relation, dest, setrelationByName)
	SIMPLE_MAP_OPTIONAL(source, relationLink, dest, setrelationLink)
	SIMPLE_MAP_OPTIONAL(source, runningOrderNumber, dest, setrunningOrderNumber)
	SIMPLE_MAP_OPTIONAL(source, totalNumberOfGroupMembers, dest, settotalNumberOfGroupMembers)
	SIMPLE_MAP_OPTIONAL(source, orderedGroupFlag, dest, setorderedGroupFlag)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcustomRelationTypeGroup)

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, relationIdentifier, ebucoreIdentifier, mapIdentifier, dest, setrelationIdentifier)
}

#define MAP_TECHNICAL_ATTRIBUTE_FUNCTION(functionName, sourceType, destType, destProperty) \
	void functionName(sourceType& source, destType *dest, ObjectModifier* mod) { \
		dest->destProperty(source);	\
		MAP_TYPE_GROUP(source, dest)	\
	}

MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeString, String, ebucoreTechnicalAttributeString, settechnicalAttributeStringValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt8, Int8, ebucoreTechnicalAttributeInt8, settechnicalAttributeInt8Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt16, Int16, ebucoreTechnicalAttributeInt16, settechnicalAttributeInt16Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt32, Int32, ebucoreTechnicalAttributeInt32, settechnicalAttributeInt32Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeInt64, Int64, ebucoreTechnicalAttributeInt64, settechnicalAttributeInt64Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt8, UInt8, ebucoreTechnicalAttributeUInt8, settechnicalAttributeUInt8Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt16, UInt16, ebucoreTechnicalAttributeUInt16, settechnicalAttributeUInt16Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt32, UInt32, ebucoreTechnicalAttributeUInt32, settechnicalAttributeUInt32Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeUInt64, UInt64, ebucoreTechnicalAttributeUInt64, settechnicalAttributeUInt64Value)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeFloat, Float, ebucoreTechnicalAttributeFloat, settechnicalAttributeFloatValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeAnyURI, technicalAttributeUriType, ebucoreTechnicalAttributeAnyURI, settechnicalAttributeAnyURIValue)
MAP_TECHNICAL_ATTRIBUTE_FUNCTION(mapTechnicalAttributeBoolean, Boolean, ebucoreTechnicalAttributeBoolean, settechnicalAttributeBooleanValue)

void mapTechnicalAttributeRational(technicalAttributeRationalType& source, ebucoreTechnicalAttributeRational *dest, ObjectModifier* mod) {
	mxfRational r = { source.factorNumerator(), source.factorDenominator() };
	dest->settechnicalAttributeRationalValue(r);
	MAP_TYPE_GROUP(source, dest)
}

void mapMIMEType(mimeType& source, ebucoreMimeType *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setmimeTypeGroup)
}

void mapContainerFormat(formatType::containerFormat_type& source, ebucoreContainerFormat *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setcontainerFormatGroup)
}

void mapMedium(medium& source, ebucoreMedium *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, mediumId, dest, setmediumID)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setmediumTypeGroup)
}

void mapLocator(formatType::locator_type& source, ebucoreLocator *dest, ObjectModifier* mod = NULL) {
	// [TODO] In XSD, provide a locator string that can be mapped to the KLV locatorLocation field
	//SIMPLE_MAP(source, <<locator value>>, dest, setlocatorLocation)
	dest->setlocatorLocation("");

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setlocatorTypeGroup)
}

void mapPackageInfo(formatType& source, ebucorePackageInfo *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, fileName, dest, setpackageName)
	SIMPLE_MAP_OPTIONAL(source, fileSize, dest, setpackageSize)

	NEW_VECTOR_AND_ASSIGN(source, locator, ebucoreLocator, formatType::locator_iterator, mapLocator, dest, setpackageLocator)
}

void mapSigningFormat(signingFormat& source, ebucoreSigningFormat *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, setsigningTrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, setsigningTrackName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setsigningTrackLanguageName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setsigningTrackLanguageCode) /* find alternative? */
	SIMPLE_MAP_OPTIONAL(source, signingSourceUri, dest, setsigningSourceUri)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setsigningTypeGroup)
	MAP_NEW_FORMAT_GROUP_AND_ASSIGN(source, dest, setsigningFormatGroup)
}

void mapCodec(codecType& source, ebucoreCodec *dest, ObjectModifier* mod = NULL) {	
	SIMPLE_MAP_OPTIONAL(source, name, dest, setname)
	SIMPLE_MAP_OPTIONAL(source, vendor, dest, setvendor)
	SIMPLE_MAP_OPTIONAL(source, version, dest, setversion)
	SIMPLE_MAP_OPTIONAL(source, family, dest, setfamily)
	// [TODO] XSD Codec identifier is an identifiertype, KLV is string
	//SIMPLE_MAP_OPTIONAL(source, codecIdentifier, dest, setcodecIdentifier)
}

void mapAudioTrack(audioTrack& source, ebucoreTrack *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, settrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, settrackName)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settrackTypeGroup)
}

void mapVideoTrack(videoTrack& source, ebucoreTrack *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, trackId, dest, settrackID)
	SIMPLE_MAP_OPTIONAL(source, trackName, dest, settrackName)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, settrackTypeGroup)
}

void mapAudioEncoding(audioFormatType::audioEncoding_type& source, ebucoreEncoding *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setencodingTypeGroup)
}

void mapAudioFormat(audioFormatType& source, ebucoreAudioFormat *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, audioFormatId, dest, setaudioFormatID)
	SIMPLE_MAP_OPTIONAL(source, audioFormatName, dest, setaudioFormatName)
	SIMPLE_MAP_OPTIONAL(source, audioFormatDefinition, dest, setaudioFormatDefinition)

	if (source.audioTrackConfiguration().present()) {
		MAP_NEW_TYPE_GROUP_AND_ASSIGN(source.audioTrackConfiguration().get(), dest, setaudioTrackConfiguration)
	}

	SIMPLE_MAP_OPTIONAL(source, sampleSize, dest, setaudioSamplingSize)
	SIMPLE_MAP_OPTIONAL(source, sampleType, dest, setaudioSamplingType)
	SIMPLE_MAP_OPTIONAL(source, channels, dest, setaudioTotalNumberOfChannels)
	SIMPLE_MAP_OPTIONAL(source, bitRate, dest, setaudioBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMode, dest, setaudioBitRateMode)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, samplingRate, dest, setaudioSamplingRate, convert)
	

	NEW_VECTOR_AND_ASSIGN(source, audioEncoding, ebucoreEncoding, audioFormatType::audioEncoding_iterator, mapAudioEncoding, dest, setaudioEncoding)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setaudioCodec)
	NEW_VECTOR_AND_ASSIGN(source, audioTrack, ebucoreTrack, audioFormatType::audioTrack_iterator, mapAudioTrack, dest, setaudioTrack)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		audioFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setaudioTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		audioFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setaudioTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		audioFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setaudioTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		audioFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setaudioTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		audioFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setaudioTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		audioFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setaudioTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		audioFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setaudioTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		audioFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setaudioTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		audioFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setaudioTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		audioFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setaudioTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		audioFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setaudioTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		audioFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setaudioTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		audioFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setaudioTechnicalAttributeBoolean)
}

void mapImageEncoding(imageFormatType::imageEncoding_type& source, ebucoreEncoding *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setencodingTypeGroup)
}

void mapAspectRatio(aspectRatioType& source, ebucoreAspectRatio *dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_NO_GET(source, factorNumerator, dest, setaspectRatioFactorNumerator)
	SIMPLE_MAP_NO_GET(source, factorDenominator, dest, setaspectRatioFactorDenominator)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setaspectRatioTypeGroup)
}

void mapDimension(lengthType& source, ebucoreDimension *dest, ObjectModifier* mod = NULL) {
	dest->setdimensionValue(source);
	SIMPLE_MAP_OPTIONAL(source, unit, dest, setdimensionUnit)
}

void mapImageFormat(imageFormatType& source, ebucoreImageFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, imageFormatId, dest, setimageFormatID)
	SIMPLE_MAP_OPTIONAL(source, imageFormatName, dest, setimageFormatName)
	SIMPLE_MAP_OPTIONAL(source, imageFormatDefinition, dest, setimageFormatDefinition)
	SIMPLE_MAP_OPTIONAL(source, orientation, dest, setimageOrientation)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, aspectRatio, ebucoreAspectRatio, mapAspectRatio, dest, setimageAspectRatio)
	
	NEW_VECTOR_AND_ASSIGN(source, imageEncoding, ebucoreEncoding, imageFormatType::imageEncoding_iterator, mapImageEncoding, dest, setimageEncoding)

	/* [TODO] XSD is missing image codec
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setimageCodec) */

	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, width, ebucoreDimension, mapDimension, dest, setimageWidth)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, height, ebucoreDimension, mapDimension, dest, setimageHeight)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		imageFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setimageTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		imageFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setimageTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		imageFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setimageTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		imageFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setimageTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		imageFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setimageTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		imageFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setimageTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		imageFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setimageTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		imageFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setimageTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		imageFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setimageTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		imageFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setimageTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		imageFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setimageTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		imageFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setimageTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		imageFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setimageTechnicalAttributeBoolean)
}

void mapVideoEncoding(videoFormatType::videoEncoding_type& source, ebucoreEncoding *dest, ObjectModifier* mod = NULL) {
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setencodingTypeGroup)
}

void mapVideoFormat(videoFormatType& source, ebucoreVideoFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, videoFormatId, dest, setvideoFormatID)
	SIMPLE_MAP_OPTIONAL(source, videoFormatName, dest, setvideoFormatName)
	SIMPLE_MAP_OPTIONAL(source, videoFormatDefinition, dest, setvideoFormatDefinition)
	
	SIMPLE_MAP_OPTIONAL(source, bitRate, dest, setvideoBitRate)
	SIMPLE_MAP_OPTIONAL(source, bitRateMode, dest, setvideoBitRateMode)
	SIMPLE_MAP_OPTIONAL(source, scanningFormat, dest, setvideoSamplingFormat)
	SIMPLE_MAP_OPTIONAL(source, scanningOrder, dest, setvideoScanningOrder)
	SIMPLE_MAP_OPTIONAL(source, lines, dest, setvideoActiveLines)
	SIMPLE_MAP_OPTIONAL(source, noiseFilter, dest, setvideoNoiseFilterFlag)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, aspectRatio, ebucoreAspectRatio, mapAspectRatio, dest, setvideoAspectRatio)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, frameRate, dest, setvideoFrameRate, convert)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, width, ebucoreDimension, mapDimension, dest, setvideoWidth)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, height, ebucoreDimension, mapDimension, dest, setvideoHeight)

	NEW_VECTOR_AND_ASSIGN(source, videoEncoding, ebucoreEncoding, videoFormatType::videoEncoding_iterator, mapVideoEncoding, dest, setvideoEncoding)
	NEW_OBJECT_AND_ASSIGN_OPTIONAL(source, codec, ebucoreCodec, mapCodec, dest, setvideoCodectype)
	NEW_VECTOR_AND_ASSIGN(source, videoTrack, ebucoreTrack, videoFormatType::videoTrack_iterator, mapVideoTrack, dest, setvideoTrack)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		videoFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setvideoTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		videoFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setvideoTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		videoFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setvideoTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		videoFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setvideoTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		videoFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setvideoTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		videoFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setvideoTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		videoFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setvideoTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		videoFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setvideoTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		videoFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setvideoTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		videoFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setvideoTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		videoFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setvideoTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		videoFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setvideoTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		videoFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setvideoTechnicalAttributeBoolean)
}

void mapCaptioning(captioningFormat& source, ebucoreCaptioning* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, captioningFormatId, dest, setcaptioningFormatID)
	SIMPLE_MAP_OPTIONAL(source, captioningFormatName, dest, setcaptioningFormatName)
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setcaptioningFormatDefinition)
	SIMPLE_MAP_OPTIONAL(source, captioningSourceUri, dest, setcaptioningSourceUri)
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setcaptioningFormatDefinition)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setcaptioningLanguageName)
	SIMPLE_MAP_OPTIONAL(source, language, dest, setcaptioningLanguageCode)

	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setcaptioningTypeGroup)
}

void mapAncillaryData(ancillaryDataFormat& source, ebucoreAncillaryData* dest, ObjectModifier* mod = NULL) {
	SIMPLE_MAP_OPTIONAL(source, DID, dest, setDID)
	SIMPLE_MAP_OPTIONAL(source, SDID, dest, setSDID)

	std::vector<uint32_t> vec_lines;
	for (ancillaryDataFormat::lineNumber_const_iterator it = source.lineNumber().begin(); it != source.lineNumber().end(); it++) {
		vec_lines.push_back(*it);
	}
	dest->setlineNumber(vec_lines);

	ebucoreTypeGroup *obj = newAndModifyObject<ebucoreTypeGroup>(dest->getHeaderMetadata(), mod);
	// source is only an integer to map from, lets be creative
	SIMPLE_MAP_OPTIONAL(source, ancillaryDataFormatName, obj, settypeGroupLabel)
	SIMPLE_MAP_OPTIONAL(source, ancillaryDataFormatId, obj, settypeGroupLink)
	SIMPLE_MAP_OPTIONAL_CONVERT(source, wrappingType, obj, settypeGroupDefinition, convert_to_string)
}

void mapDataFormat(dataFormatType& source, ebucoreDataFormat *dest, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, dataFormatId, dest, setdataFormatID)
	SIMPLE_MAP_OPTIONAL(source, dataFormatName, dest, setdataFormatName)
	SIMPLE_MAP_OPTIONAL(source, dataFormatDefinition, dest, setdataFormatDefinition)
	
	NEW_VECTOR_AND_ASSIGN(source, captioningFormat, ebucoreCaptioning, dataFormatType::captioningFormat_iterator, mapCaptioning, dest, setcaptioning)
	NEW_VECTOR_AND_ASSIGN(source, ancillaryDataFormat, ebucoreAncillaryData, dataFormatType::ancillaryDataFormat_iterator, mapAncillaryData, dest, setancillaryData)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		dataFormatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setdataTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		dataFormatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setdataTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		dataFormatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setdataTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		dataFormatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setdataTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		dataFormatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setdataTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		dataFormatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setdataTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		dataFormatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setdataTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		dataFormatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setdataTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		dataFormatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setdataTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		dataFormatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setdataTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		dataFormatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setdataTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		dataFormatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setdataTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		dataFormatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setdataTechnicalAttributeBoolean)
}

void mapFormat(formatType& source, ebucoreFormat *dest, std::map<xml_schema::id, ebucoreFormat*>& formatMap, ObjectModifier* mod = NULL) {

	SIMPLE_MAP_OPTIONAL(source, formatId, dest, setformatID)
	SIMPLE_MAP_OPTIONAL(source, formatVersionId, dest, setformatVersionID)
	SIMPLE_MAP_OPTIONAL(source, formatName, dest, setformatName)
	SIMPLE_MAP_OPTIONAL(source, formatDefinition, dest, setformatDefinition)
	
	if (source.dateCreated().present()) {
		SIMPLE_MAP_OPTIONAL_CONVERT(source, dateCreated().get().startYear, dest, setformatYearCreated, convert_timestamp)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, dateCreated().get().startDate, dest, setformatDateCreated, convert_timestamp)
	}

	if (source.duration().present()) {
		// [NOTE] Mapped playtime as duration because we need a numeric value (rational) # of seconds.
		// [NOTE] We just map the timecode as a string to the KLV representation
		SIMPLE_MAP_OPTIONAL(source, duration().get().editUnitNumber, dest, setoverallDurationEditUnit)
		SIMPLE_MAP_OPTIONAL(source, duration().get().timecode, dest, setoverallDurationTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, duration().get().normalPlayTime, dest, setoverallDurationTime, convert_rational)
	}

	if (source.start().present()) {
		SIMPLE_MAP_OPTIONAL(source, start().get().editUnitNumber, dest, setoverallStartEditUnit)
		SIMPLE_MAP_OPTIONAL(source, start().get().timecode, dest, setoverallStartTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, start().get().normalPlayTime, dest, setoverallStartTime, convert_rational)
	}
	if (source.end().present()) {
		SIMPLE_MAP_OPTIONAL(source, end().get().editUnitNumber, dest, setoverallEndEditUnit)
		SIMPLE_MAP_OPTIONAL(source, end().get().timecode, dest, setoverallEndTimecode)
		SIMPLE_MAP_OPTIONAL_CONVERT(source, end().get().normalPlayTime, dest, setoverallEndTime, convert_rational)
	}

	NEW_VECTOR_AND_ASSIGN(source, containerFormat, ebucoreContainerFormat, formatType::containerFormat_iterator, mapContainerFormat, dest, setcontainerFormat)
	NEW_VECTOR_AND_ASSIGN(source, medium, ebucoreMedium, formatType::medium_iterator, mapMedium, dest, setmedium)
	
	ebucorePackageInfo *obj = newAndModifyObject<ebucorePackageInfo>(dest->getHeaderMetadata(), mod);
	mapPackageInfo(source, obj, mod);
	dest->setpackageInfo(obj);

	NEW_VECTOR_AND_ASSIGN(source, mimeType, ebucoreMimeType, formatType::mimeType_iterator, mapMIMEType, dest, setmimeType)

	NEW_VECTOR_AND_ASSIGN(source, audioFormat, ebucoreAudioFormat, formatType::audioFormat_iterator, mapAudioFormat, dest, setmaterialAudioFormat)
	NEW_VECTOR_AND_ASSIGN(source, videoFormat, ebucoreVideoFormat, formatType::videoFormat_iterator, mapVideoFormat, dest, setmaterialVideoFormat)
	NEW_VECTOR_AND_ASSIGN(source, imageFormat, ebucoreImageFormat, formatType::imageFormat_iterator, mapImageFormat, dest, setmaterialImageFormat)
	NEW_VECTOR_AND_ASSIGN(source, dataFormat, ebucoreDataFormat, formatType::dataFormat_iterator, mapDataFormat, dest, setmaterialDataFormat)
	NEW_VECTOR_AND_ASSIGN(source, signingFormat, ebucoreSigningFormat, formatType::signingFormat_iterator, mapSigningFormat, dest, setmaterialSigningFormat)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeString, ebucoreTechnicalAttributeString, 
		formatType::technicalAttributeString_iterator, mapTechnicalAttributeString, dest, setmaterialTechnicalAttributeString)
	
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeByte, ebucoreTechnicalAttributeInt8, 
		formatType::technicalAttributeByte_iterator, mapTechnicalAttributeInt8, dest, setmaterialTechnicalAttributeInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeShort, ebucoreTechnicalAttributeInt16, 
		formatType::technicalAttributeShort_iterator, mapTechnicalAttributeInt16, dest, setmaterialTechnicalAttributeInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeInteger, ebucoreTechnicalAttributeInt32, 
		formatType::technicalAttributeInteger_iterator, mapTechnicalAttributeInt32, dest, setmaterialTechnicalAttributeInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeLong, ebucoreTechnicalAttributeInt64, 
		formatType::technicalAttributeLong_iterator, mapTechnicalAttributeInt64, dest, setmaterialTechnicalAttributeInt64)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedByte, ebucoreTechnicalAttributeUInt8, 
		formatType::technicalAttributeUnsignedByte_iterator, mapTechnicalAttributeUInt8, dest, setmaterialTechnicalAttributeUInt8)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedShort, ebucoreTechnicalAttributeUInt16, 
		formatType::technicalAttributeUnsignedShort_iterator, mapTechnicalAttributeUInt16, dest, setmaterialTechnicalAttributeUInt16)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedInteger, ebucoreTechnicalAttributeUInt32, 
		formatType::technicalAttributeUnsignedInteger_iterator, mapTechnicalAttributeUInt32, dest, setmaterialTechnicalAttributeUInt32)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUnsignedLong, ebucoreTechnicalAttributeUInt64, 
		formatType::technicalAttributeUnsignedLong_iterator, mapTechnicalAttributeUInt64, dest, setmaterialTechnicalAttributeUInt64)

	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeFloat, ebucoreTechnicalAttributeFloat, 
		formatType::technicalAttributeFloat_iterator, mapTechnicalAttributeFloat, dest, setmaterialTechnicalAttributeFloat)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeRational, ebucoreTechnicalAttributeRational, 
		formatType::technicalAttributeRational_iterator, mapTechnicalAttributeRational, dest, setmaterialTechnicalAttributeRational)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeUri, ebucoreTechnicalAttributeAnyURI, 
		formatType::technicalAttributeUri_iterator, mapTechnicalAttributeAnyURI, dest, setmaterialTechnicalAttributeAnyURI)
	NEW_VECTOR_AND_ASSIGN(source, technicalAttributeBoolean, ebucoreTechnicalAttributeBoolean, 
		formatType::technicalAttributeBoolean_iterator, mapTechnicalAttributeBoolean, dest, setmaterialTechnicalAttributeBoolean)

	// add this format element to the list
	if (source.formatId().present()) {
		formatMap[source.formatId().get()] = dest;
	}
}

void mapPart(partType& source, ebucorePartMetadata *dest, mxfRational overallFrameRate, std::vector<ebucorePartMetadata*>& timelineParts, ObjectModifier* mod) {
	SIMPLE_MAP_OPTIONAL(source, partId, dest, setpartId)
	SIMPLE_MAP_OPTIONAL(source, partName, dest, setpartName)
	SIMPLE_MAP_OPTIONAL(source, partDefinition, dest, setpartDefinition)
	MAP_NEW_TYPE_GROUP_AND_ASSIGN(source, dest, setpartTypeGroup)

	// map ourselves (we are an extension of the coreMetadataType) onto a new ebucoreCoreMetadata object
	ebucoreCoreMetadata *obj = newAndModifyObject<ebucoreCoreMetadata>(dest->getHeaderMetadata(), mod);
	mapCoreMetadata(source, obj, overallFrameRate, timelineParts, mod);
	dest->setpartMeta(obj);
}

void mapCoreMetadata(coreMetadataType& source, ebucoreCoreMetadata *dest, mxfRational overallFrameRate, std::vector<ebucorePartMetadata*>& timelineParts, ObjectModifier* mod) {

	std::map<xml_schema::id, ebucoreFormat*> formatMap;

	NEW_VECTOR_AND_ASSIGN(source, title, ebucoreTitle, coreMetadataType::title_iterator, mapTitle, dest, settitle)	
	NEW_VECTOR_AND_ASSIGN(source, alternativeTitle, ebucoreAlternativeTitle, coreMetadataType::alternativeTitle_iterator, mapAlternativeTitle, dest, setalternativeTitle)
	NEW_VECTOR_AND_ASSIGN(source, creator, ebucoreEntity, coreMetadataType::creator_iterator, mapEntity, dest, setcreator)
	NEW_VECTOR_AND_ASSIGN(source, subject, ebucoreSubject, coreMetadataType::subject_iterator, mapSubject, dest, setsubject)
	NEW_VECTOR_AND_ASSIGN(source, description, ebucoreDescription, coreMetadataType::description_iterator, mapDescription, dest, setdescription)
	NEW_VECTOR_AND_ASSIGN(source, publisher, ebucoreEntity, coreMetadataType::publisher_iterator, mapEntity, dest, setpublisher)
	NEW_VECTOR_AND_ASSIGN(source, contributor, ebucoreEntity, coreMetadataType::contributor_iterator, mapEntity, dest, setcontributor)
	NEW_VECTOR_AND_ASSIGN(source, date, ebucoreDate, coreMetadataType::date_iterator, mapDate, dest, setdate)
	NEW_VECTOR_AND_ASSIGN(source, type, ebucoreType, coreMetadataType::type_iterator, mapType, dest, settype)
	NEW_VECTOR_AND_ASSIGN(source, identifier, ebucoreIdentifier, coreMetadataType::identifier_iterator, mapIdentifier, dest, setidentifier)
	NEW_VECTOR_AND_ASSIGN(source, language, ebucoreLanguage, coreMetadataType::language_iterator, mapLanguage, dest, setlanguage)
	NEW_VECTOR_AND_ASSIGN(source, coverage, ebucoreCoverage, coreMetadataType::coverage_iterator, mapMetadataCoverage, dest, setcoverage)

	// do formats before rights and publicationhistory to make sure references are available in the map
	std::vector<ebucoreFormat*> vec_dest_fmt;
	for (coreMetadataType::format_iterator it = source.format().begin(); it != source.format().end(); it++) {
		ebucoreFormat *obj = newAndModifyObject<ebucoreFormat>(dest->getHeaderMetadata(), mod);
		mapFormat(*it, obj, formatMap, mod);
		vec_dest_fmt.push_back(obj);
	}
	dest->setformat(vec_dest_fmt);
	//NEW_VECTOR_AND_ASSIGN(source, format, ebucoreFormat, coreMetadataType::format_iterator, mapFormat, dest, setformat)

	std::vector<ebucoreRights*> vec_dest_rights;
	for (coreMetadataType::rights_iterator it = source.rights().begin(); it != source.rights().end(); it++) {
		ebucoreRights *obj = newAndModifyObject<ebucoreRights>(dest->getHeaderMetadata(), mod);
		mapRights(*it, obj, formatMap, mod);
		vec_dest_rights.push_back(obj);
	}
	dest->setrights(vec_dest_rights);
	//NEW_VECTOR_AND_ASSIGN(source, rights, ebucoreRights, coreMetadataType::rights_iterator, mapRights, dest, setrights)

	NEW_VECTOR_AND_ASSIGN(source, rating, ebucoreRating, coreMetadataType::rating_iterator, mapRating, dest, setrating)

	if (source.version().size() > 0) {
		ebucoreVersion *obj = newAndModifyObject<ebucoreVersion>(dest->getHeaderMetadata(), mod);
		mapVersion(source.version()[0], obj);
		dest->setversion(obj);
	}
	
	if (source.publicationHistory().present()) {
		std::vector<ebucorePublicationHistoryEvent*> vec_publications;
		mapPublicationHistory(source.publicationHistory().get(), vec_publications, dest->getHeaderMetadata(), formatMap, mod);
		dest->setpublicationHistoryEvent(vec_publications);
	}

	mapBasicRelations(source, dest, mod);
	NEW_VECTOR_AND_ASSIGN(source, relation, ebucoreCustomRelation, coreMetadataType::relation_iterator, mapCustomRelation, dest, setcustomRelation)

	std::vector<ebucorePartMetadata*> vec_parts;
	for (coreMetadataType::part_iterator it = source.part().begin(); it != source.part().end(); it++) {
		ebucorePartMetadata *obj = newAndModifyObject<ebucorePartMetadata>(dest->getHeaderMetadata(), mod);
		mapPart(*it, obj, overallFrameRate, timelineParts, mod);
		vec_parts.push_back(obj);

		// set extremes to start with
		mxfPosition partStart = 0x7FFFFFFFFFFFFFFF;
		mxfLength partEnd = 0;

		// determine which of our parts belong on a timeline
		partType& part = *it;
		for (partType::format_iterator it2 = part.format().begin(); it2 != part.format().end(); it2++) {
			formatType& format = *it2;
			if (format.start().present() && (format.duration().present() || format.end().present())) {
				formatType::start_type &start = format.start().get();
				// sensible values are present!
				mxfPosition formatStart;
				mxfLength formatDuration;
				if (start.editUnitNumber().present()) {
					formatStart = start.editUnitNumber().get();
				} else if (start.normalPlayTime().present()) {
					// convert a duration
					mxfRational d = convert_rational(start.normalPlayTime().get());
					formatStart = (d.numerator * overallFrameRate.numerator) / (d.denominator * overallFrameRate.denominator);
				} else {
					// convert a time code
					bmx::Timecode tc;
					bmx::parse_timecode(start.timecode().get().c_str(), overallFrameRate, &tc);
					formatStart = tc.GetOffset();
				}
				if (format.duration().present()) {
					formatType::duration_type &dur = format.duration().get();
					if (dur.editUnitNumber().present()) {
						formatDuration = dur.editUnitNumber().get();
					} else if (dur.normalPlayTime().present()) {
						// convert a duration
						mxfRational d = convert_rational(dur.normalPlayTime().get());
						formatDuration = (d.numerator * overallFrameRate.numerator) / (d.denominator * overallFrameRate.denominator);
					} else {
						// convert a time code
						bmx::Timecode tc;
						bmx::parse_timecode(dur.timecode().get().c_str(), overallFrameRate, &tc);
						formatDuration = tc.GetOffset();
					}
				} else {
					formatType::end_type &end = format.end().get();
					if (end.editUnitNumber().present()) {
						formatDuration = end.editUnitNumber().get() - formatStart;
					} else if (end.normalPlayTime().present()) {
						// convert a duration
						mxfRational d = convert_rational(end.normalPlayTime().get());
						formatStart = (d.numerator * overallFrameRate.numerator) / (d.denominator * overallFrameRate.denominator) - formatStart;
					} else {
						// convert a time code
						bmx::Timecode tc;
						bmx::parse_timecode(end.timecode().get().c_str(), overallFrameRate, &tc);
						formatDuration = tc.GetOffset() - formatStart;
					}
				}
				if (formatStart < partStart) partStart = formatStart;
				if (formatStart + formatDuration > partEnd) partEnd = formatStart + formatDuration;
			}
		}

		if (partStart != 0x7FFFFFFFFFFFFFFF && partEnd != 0) {
			// this goes onto the timeline!
			obj->setpartStartEditUnitNumber(partStart);
			obj->setpartDurationEditUnitNumber(partEnd - partStart);
			timelineParts.push_back(obj);
		}
	}
	dest->setpart(vec_parts); 
}

} // namespace EBUCore
} // namespace EBUSDK
