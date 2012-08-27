
#include <libMXF++/MXF.h>

#include <xercesc/dom/DOMDocument.hpp>

/**
*	EBU MXF SDK main namespace for EBUCore functionality.
*/
namespace EBUCore
{
	mxfpp::Identification* GenerateEBUCoreIdentificationSet(mxfpp::HeaderMetadata *destination);
	mxfpp::DMFramework* Process(const char* location, mxfpp::HeaderMetadata *destination, mxfpp::Identification *identificationToAppend = NULL);

	void FindAndSerializeEBUCore(mxfpp::HeaderMetadata *metadata, const char* outputfilename);
	void RegisterMetadataExtensionsforEBUCore(mxfpp::DataModel *data_model);
	void RegisterFrameworkObjectFactoriesforEBUCore(mxfpp::HeaderMetadata *metadata);
	void InsertEBUCoreFramework(mxfpp::HeaderMetadata *header_metadata, mxfpp::DMFramework *framework, mxfpp::Identification *identificationToAppend = NULL);

	uint64_t BufferIndex(mxfpp::File* mFile, mxfpp::Partition* partition, bmx::ByteArray& index_bytes, uint32_t* index_length);
	uint64_t WriteMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);
	uint64_t WriteMetadataToFile(mxfpp::File* mFile, mxfpp::HeaderMetadata *mHeaderMetadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);

	class MXFFileDarkSerializer {
	public:
		virtual uint64_t WriteToMXFFile(mxfpp::File *f) = 0;
		virtual ~MXFFileDarkSerializer() {};
	};

	uint64_t WriteDarkMetadataToMemoryFile(mxfpp::File* mFile, MXFMemoryFile **destMemFile, MXFFileDarkSerializer& metadata, uint64_t metadata_read_position, uint64_t metadata_write_position, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);
	uint64_t WriteDarkMetadataToFile(mxfpp::File* mFile, MXFFileDarkSerializer& metadata, uint64_t metadata_read_position, uint64_t metadata_write_position, bool shiftFileBytesIfNeeded, mxfpp::Partition* metadataDestitionPartition, mxfpp::Partition* metadataSourcePartition);

	int64_t FindLastPartitionFill(mxfpp::File* mFile, mxfpp::Partition* partition, int64_t* partitionSectionOffset, int64_t *extractedFileSize = NULL);
	void ShiftBytesInFile(mxfpp::File* mFile, int64_t shiftPosition, int64_t shiftOffset);

	enum ProgressCallbackLevel {
		FATAL,
		ERROR,
		WARN,
		INFO,
		DEBUG,
		TRACE
	};

	enum MetadataKind {
		KLV_ENCODED,
		DARK,
		SIDECAR
	};

	/**
	*	Embed EBUCore metadata into an MXF file.
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param metadataLocation The location of the EBUCore XML metadata document file. This file is parsed using the Xerces-C++ XML parser. 
		The document is assumed to conform to the EBUCore XML schema and is not explicitly validated.
		@param mxfLocation The location of the MXF file in which to embed the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		@param optWriteDarkMetadata When true, forces the SDK to serialize the EBUCore document as 'dark' metadata into the header metadata of the MXF file.
		@param optNoIdentification When true, forces the SDK not to write an additional MXF metadata Identification set to identify the SDK as source of metadata updates.
		@param optForceHeader When true, forces the SDK to write the EBUCore metadata into the header partition, potentially forcing a rewrite of the entire MXF file. 
		In normal operation, the SDK attempts to write the EBUCore metadata into the footer partition, marking the header (and potential body) partitions that contain metadata as
		open and incomplete. This way only the footer paritition and the (small) partition packs must be updated.
	*/
	void EmbedEBUCoreMetadata(	const char* metadataLocation, 
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false);

	/**
	*	Embed EBUCore metadata into an MXF file.\n
		This variant of __EmbedEBUCoreMetadata__ accepts a processed XML document, in the form of a Xerces-C++ XML DOM representation. 
		This function can hence be used when the caller wishes to manipulate the EBUCore metadata first, 
		before embedding it in the MXF file and without having to write changes to a physical XML file first.
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param metadataDocument A parsed EBUCore XML metadata document, in the form of the DOM representation generated by the Xerces-C++ XML parser. 
		The document is assumed to conform to the EBUCore XML schema and is not explicitly validated.
		@param metadataLocation The logical location of the metadata document, as it will be embedded in the KLV EBUCore metadata. 
		As in this form the __metadataDocument__ doesn't provide an indication of the physical source location of the document, 
		it is be provided separately here. When irrelevant, an empty string "" can be provided.
		@param mxfLocation The location of the MXF file in which to embed the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
		@param optWriteDarkMetadata When true, forces the SDK to serialize the EBUCore document as 'dark' metadata into the header metadata of the MXF file.
		@param optNoIdentification When true, forces the SDK not to write an additional MXF metadata Identification set to identify the SDK as source of metadata updates.
		@param optForceHeader When true, forces the SDK to write the EBUCore metadata into the header partition, potentially forcing a rewrite of the entire MXF file. 
		In normal operation, the SDK attempts to write the EBUCore metadata into the footer partition, marking the header (and potential body) partitions that contain metadata as
		open and incomplete. This way only the footer paritition and the (small) partition packs must be updated.
	*/
	void EmbedEBUCoreMetadata(	xercesc::DOMDocument& metadataDocument, 
							const char* metadataLocation,
							const char* mxfLocation, 
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...),
							MetadataKind optWaytoWrite = KLV_ENCODED,
							bool optNoIdentification = false, bool optForceHeader = false);

	/**
	*	Extract EBUCore metadata from an MXF file.\n
		The SDK consecutively tries to extract the metadata in three ways; from KLV-encoded EBUCore metadata sets, 
		from a sidecar file referenced by the MXF file's metadata, or as 'dark' metadata from a KLV set identified by the appropriate key.\n
		This variant of __ExtractEBUCoreMetadata__ returns a Xerces-C++ XML DOM data structure that can 
		be processed and transformed by the caller, before e.g., being written out to disk.
		@return Returns a reference to a Xerces-C++ XML DOM document representation that conforms to the EBUCore XML schema.
		@param mxfLocation The location of the MXF file in which to extract the EBUCore metadata.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
	*/
	xercesc::DOMDocument& ExtractEBUCoreMetadata(
							const char* mxfLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));
	
	/**
	*	Extract EBUCore metadata from an MXF file.\n
		The SDK consecutively tries to extract the metadata in three ways; from KLV-encoded EBUCore metadata sets, 
		from a sidecar file referenced by the MXF file's metadata, or as 'dark' metadata from a KLV set identified by the appropriate key.\n
		@return Has no return value, but throws an exception when irregularities occur. The caller is informed of any progress by means of the __progress_callback__ argument.
		@param mxfLocation The location of the MXF file in which to extract the EBUCore metadata.
		@param metadataLocation The location of the EBUCore XML metadata document file destination. The XML document written conforms to the EBUCore XML schema.
		@param progress_callback A function that is called with updated progress concerning the embedding process. 
		The function is called with the overall progress of the operation in __progress__,  a __message__ that describes the updated status, 
		and the name of the internal __function__ to which the progress update relates (which can be used for debugging purposes).
	*/
	void ExtractEBUCoreMetadata(
							const char* mxfLocation,
							const char* metadataLocation,
							void (*progress_callback)(float progress, ProgressCallbackLevel level, const char *function, const char *msg_format, ...));

}