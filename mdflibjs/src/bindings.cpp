#include <emscripten/bind.h>

#include "attachment_wrapped.h"
#include "can_message_wrapped.h"
#include "channel_conversion_wrapped.h"
#include "channel_group_wrapped.h"
#include "channel_observer_wrapped.h"
#include "channel_wrapped.h"
#include "data_group_wrapped.h"
#include "etag_helpers.h"
#include "event_wrapped.h"
#include "file_history_wrapped.h"
#include "file_wrapped.h"
#include "header_wrapped.h"
#include "metadata_wrapped.h"
#include "reader_wrapped.h"
#include "source_information_wrapped.h"
#include "writer_wrapped.h"

using namespace emscripten;
using namespace mdflibjs;

// Binding code
EMSCRIPTEN_BINDINGS(mdflibjs) {
  using mdf::BusType;
  using mdf::CanErrorType;
  using mdf::ChannelDataType;
  using mdf::ChannelSyncType;
  using mdf::ChannelType;
  using mdf::ConversionType;
  using mdf::ETag;
  using mdf::ETagDataType;
  using mdf::EventCause;
  using mdf::EventType;
  using mdf::MdfBusType;
  using mdf::MdfWriterType;
  using mdf::RangeType;
  using mdf::SourceType;
  using mdf::SyncType;

  // This is common for a lot of interfaces.
  register_vector<uint8_t>("Uint8Vector");

  // Bind the CanErrorType enum
  enum_<CanErrorType>("CanErrorType")
      .value("UNKNOWN_ERROR", CanErrorType::UNKNOWN_ERROR)
      .value("BIT_ERROR", CanErrorType::BIT_ERROR)
      .value("FORM_ERROR", CanErrorType::FORM_ERROR)
      .value("BIT_STUFFING_ERROR", CanErrorType::BIT_STUFFING_ERROR)
      .value("CRC_ERROR", CanErrorType::CRC_ERROR)
      .value("ACK_ERROR", CanErrorType::ACK_ERROR);

  class_<CanMessageWrapped>("CanMessage")
      .function("getMessageId", &CanMessageWrapped::GetMessageId)
      .function("setMessageId", &CanMessageWrapped::SetMessageId)
      .function("getCanId", &CanMessageWrapped::GetCanId)
      .function("setExtendedId", &CanMessageWrapped::SetExtendedId)
      .function("getExtendedId", &CanMessageWrapped::GetExtendedId)
      .function("getDlc", &CanMessageWrapped::GetDlc)
      .function("setDlc", &CanMessageWrapped::SetDlc)
      .function("getDataLength", &CanMessageWrapped::GetDataLength)
      .function("setDataLength", &CanMessageWrapped::SetDataLength)
      .function("getDataBytes", &CanMessageWrapped::GetDataBytes)
      .function("setDataBytes", &CanMessageWrapped::SetDataBytes,
                allow_raw_pointers())
      .function("getDataIndex", &CanMessageWrapped::GetDataIndex)
      .function("setDataIndex", &CanMessageWrapped::SetDataIndex)
      .function("getDir", &CanMessageWrapped::GetDir)
      .function("setDir", &CanMessageWrapped::SetDir)
      .function("getSrr", &CanMessageWrapped::GetSrr)
      .function("setSrr", &CanMessageWrapped::SetSrr)
      .function("getEdl", &CanMessageWrapped::GetEdl)
      .function("setEdl", &CanMessageWrapped::SetEdl)
      .function("getBrs", &CanMessageWrapped::GetBrs)
      .function("setBrs", &CanMessageWrapped::SetBrs)
      .function("getEsi", &CanMessageWrapped::GetEsi)
      .function("setEsi", &CanMessageWrapped::SetEsi)
      .function("getRtr", &CanMessageWrapped::GetRtr)
      .function("setRtr", &CanMessageWrapped::SetRtr)
      .function("getWakeUp", &CanMessageWrapped::GetWakeUp)
      .function("setWakeUp", &CanMessageWrapped::SetWakeUp)
      .function("getSingleWire", &CanMessageWrapped::GetSingleWire)
      .function("setSingleWire", &CanMessageWrapped::SetSingleWire)
      .function("getBusChannel", &CanMessageWrapped::GetBusChannel)
      .function("setBusChannel", &CanMessageWrapped::SetBusChannel)
      .function("getBitPosition", &CanMessageWrapped::GetBitPosition)
      .function("setBitPosition", &CanMessageWrapped::SetBitPosition)
      .function("getErrorType", &CanMessageWrapped::GetErrorType)
      .function("setErrorType", &CanMessageWrapped::SetErrorType)
      .function("reset", &CanMessageWrapped::Reset);

  enum_<ETagDataType>("ETagDataType")
      .value("StringType", ETagDataType::StringType)
      .value("DecimalType", ETagDataType::DecimalType)
      .value("IntegerType", ETagDataType::IntegerType)
      .value("FloatType", ETagDataType::FloatType)
      .value("BooleanType", ETagDataType::BooleanType)
      .value("DateType", ETagDataType::DateType)
      .value("TimeType", ETagDataType::TimeType)
      .value("DateTimeType", ETagDataType::DateTimeType);

  class_<ETag>("ETag")
      .constructor<>()
      .function("setName",
                select_overload<void(const std::string&)>(&ETag::Name))
      .function("getName",
                select_overload<const std::string&() const>(&ETag::Name))
      .function("setDescription",
                select_overload<void(const std::string&)>(&ETag::Description))
      .function("getDescription",
                select_overload<const std::string&() const>(&ETag::Description))
      .function("setUnit",
                select_overload<void(const std::string&)>(&ETag::Unit))
      .function("getUnit",
                select_overload<const std::string&() const>(&ETag::Unit))
      .function("setUnitRef",
                select_overload<void(const std::string&)>(&ETag::UnitRef))
      .function("getUnitRef",
                select_overload<const std::string&() const>(&ETag::UnitRef))
      .function("setDataType",
                select_overload<void(ETagDataType)>(&ETag::DataType))
      .function("getDataType",
                select_overload<ETagDataType() const>(&ETag::DataType))
      .function("setType",
                select_overload<void(const std::string&)>(&ETag::Type))
      .function("getType",
                select_overload<const std::string&() const>(&ETag::Type))
      .function("setLanguage",
                select_overload<void(const std::string&)>(&ETag::Language))
      .function("getLanguage",
                select_overload<const std::string&() const>(&ETag::Language))
      .function("setReadOnly", select_overload<void(bool)>(&ETag::ReadOnly))
      .function("isReadOnly", select_overload<bool() const>(&ETag::ReadOnly))
      .function("setCreatorIndex",
                select_overload<void(int)>(&ETag::CreatorIndex))
      .function("getCreatorIndex",
                select_overload<int() const>(&ETag::CreatorIndex))
      .function("setNumberValue", &ETag_SetNumberValue)
      .function("setBooleanValue", &ETag_SetBoolValue)
      .function("setStringValue", &ETag_SetStringValue)
      .function("getNumberValue", &ETag_GetNumberValue)
      .function("getBooleanValue", &ETag_GetBoolValue)
      .function("getStringValue", &ETag_GetStringValue)
      // Add bindings for other types like int, float, etc.
      .function("addTag", &ETag::AddTag)
      .function(
          "getTreeList",
          select_overload<const std::vector<ETag>&() const>(&ETag::TreeList));
  register_vector<mdf::ETag>("std::vector<ETag>");

  class_<MetadataWrapped>("Metadata")
      .function("getPropertyAsString", &MetadataWrapped::GetPropertyAsString)
      .function("setPropertyAsString", &MetadataWrapped::SetPropertyAsString)
      .function("getPropertyAsDouble", &MetadataWrapped::GetPropertyAsDouble)
      .function("setPropertyAsDouble", &MetadataWrapped::SetPropertyAsDouble)
      .function("setCommonProperty", &MetadataWrapped::SetCommonProperty)
      .function("getCommonProperty", &MetadataWrapped::GetCommonProperty)
      .function("setCommonProperties", &MetadataWrapped::SetCommonProperties)
      .function("getCommonProperties", &MetadataWrapped::GetCommonProperties)
      .function("getProperties", &MetadataWrapped::GetProperties)
      .function("getXmlSnippet", &MetadataWrapped::GetXmlSnippet)
      .function("setXmlSnippet", &MetadataWrapped::SetXmlSnippet);
  register_vector<MetadataWrapped>("std::vector<Metadata>");

  class_<AttachmentWrapped>("Attachment")
      .function("getIndex", &AttachmentWrapped::GetIndex)
      .function("getCreatorIndex", &AttachmentWrapped::GetCreatorIndex)
      .function("setCreatorIndex", &AttachmentWrapped::SetCreatorIndex)
      .function("getEmbedded", &AttachmentWrapped::GetEmbedded)
      .function("setEmbedded", &AttachmentWrapped::SetEmbedded)
      .function("getCompressed", &AttachmentWrapped::GetCompressed)
      .function("setCompressed", &AttachmentWrapped::SetCompressed)
      .function("getMd5", &AttachmentWrapped::GetMd5)
      .function("getFileName", &AttachmentWrapped::GetFileName)
      .function("setFileName", &AttachmentWrapped::SetFileName)
      .function("getFileType", &AttachmentWrapped::GetFileType)
      .function("setFileType", &AttachmentWrapped::SetFileType)
      .function("getMetaData", &AttachmentWrapped::GetMetaData)
      .function("createMetaData", &AttachmentWrapped::CreateMetaData);
  register_vector<AttachmentWrapped>("std::vector<Attachment>");

  enum_<EventType>("EventType")
      .value("RecordingPeriod", EventType::RecordingPeriod)
      .value("RecordingInterrupt", EventType::RecordingInterrupt)
      .value("AcquisitionInterrupt", EventType::AcquisitionInterrupt)
      .value("StartRecording", EventType::StartRecording)
      .value("StopRecording", EventType::StopRecording)
      .value("Trigger", EventType::Trigger)
      .value("Marker", EventType::Marker);

  enum_<SyncType>("SyncType")
      .value("SyncTime", SyncType::SyncTime)
      .value("SyncAngle", SyncType::SyncAngle)
      .value("SyncDistance", SyncType::SyncDistance)
      .value("SyncIndex", SyncType::SyncIndex);

  enum_<RangeType>("RangeType")
      .value("RangePoint", RangeType::RangePoint)
      .value("RangeStart", RangeType::RangeStart)
      .value("RangeEnd", RangeType::RangeEnd);

  enum_<EventCause>("EventCause")
      .value("CauseOther", EventCause::CauseOther)
      .value("CauseError", EventCause::CauseError)
      .value("CauseTool", EventCause::CauseTool)
      .value("CauseScript", EventCause::CauseScript)
      .value("CauseUser", EventCause::CauseUser);

  class_<EventWrapped>("Event")
      .function("getIndex", &EventWrapped::GetIndex)
      .function("getName", &EventWrapped::GetName)
      .function("setName", &EventWrapped::SetName)
      .function("getDescription", &EventWrapped::GetDescription)
      .function("setDescription", &EventWrapped::SetDescription)
      .function("getGroupName", &EventWrapped::GetGroupName)
      .function("setGroupName", &EventWrapped::SetGroupName)
      .function("getType", &EventWrapped::GetType)
      .function("setType", &EventWrapped::SetType)
      .function("getSync", &EventWrapped::GetSync)
      .function("setSync", &EventWrapped::SetSync)
      .function("getRange", &EventWrapped::GetRange)
      .function("setRange", &EventWrapped::SetRange)
      .function("getCause", &EventWrapped::GetCause)
      .function("setCause", &EventWrapped::SetCause)
      .function("getCreatorIndex", &EventWrapped::GetCreatorIndex)
      .function("setCreatorIndex", &EventWrapped::SetCreatorIndex)
      .function("getSyncValue", &EventWrapped::GetSyncValue)
      .function("setSyncValue", &EventWrapped::SetSyncValue)
      .function("setSyncFactor", &EventWrapped::SetSyncFactor)
      .function("getParentEvent", &EventWrapped::GetParentEvent)
      .function("setParentEvent", &EventWrapped::SetParentEvent)
      .function("getRangeEvent", &EventWrapped::GetRangeEvent)
      .function("setRangeEvent", &EventWrapped::SetRangeEvent)
      .function("getAttachments", &EventWrapped::GetAttachments)
      .function("getPreTrig", &EventWrapped::GetPreTrig)
      .function("setPreTrig", &EventWrapped::SetPreTrig)
      .function("getPostTrig", &EventWrapped::GetPostTrig)
      .function("setPostTrig", &EventWrapped::SetPostTrig)
      .function("getMetaData", &EventWrapped::GetMetaData)
      .function("addAttachment", &EventWrapped::AddAttachment);
  register_vector<EventWrapped>("std::vector<Event>");

  enum_<SourceType>("SourceType")
      .value("Other", SourceType::Other)
      .value("Ecu", SourceType::Ecu)
      .value("Bus", SourceType::Bus)
      .value("IoDevice", SourceType::IoDevice)
      .value("Tool", SourceType::Tool)
      .value("User", SourceType::User);

  enum_<BusType>("BusType")
      .value("None", BusType::None)
      .value("Other", BusType::Other)
      .value("Can", BusType::Can)
      .value("Lin", BusType::Lin)
      .value("Most", BusType::Most)
      .value("FlexRay", BusType::FlexRay)
      .value("Kline", BusType::Kline)
      .value("Ethernet", BusType::Ethernet)
      .value("Usb", BusType::Usb);

  constant("SiFlag_Simulated", mdf::SiFlag::Simulated);

  class_<SourceInformationWrapped>("SourceInformation")
      .function("getIndex", &SourceInformationWrapped::GetIndex)
      .function("getName", &SourceInformationWrapped::GetName)
      .function("setName", &SourceInformationWrapped::SetName)
      .function("getDescription", &SourceInformationWrapped::GetDescription)
      .function("setDescription", &SourceInformationWrapped::SetDescription)
      .function("getPath", &SourceInformationWrapped::GetPath)
      .function("setPath", &SourceInformationWrapped::SetPath)
      .function("getType", &SourceInformationWrapped::GetType)
      .function("setType", &SourceInformationWrapped::SetType)
      .function("getBus", &SourceInformationWrapped::GetBus)
      .function("setBus", &SourceInformationWrapped::SetBus)
      .function("getFlags", &SourceInformationWrapped::GetFlags)
      .function("setFlags", &SourceInformationWrapped::SetFlags)
      .function("getMetaData", &SourceInformationWrapped::GetMetaData)
      .function("createMetaData", &SourceInformationWrapped::CreateMetaData);
  register_vector<SourceInformationWrapped>("std::vector<SourceInformation>");

  enum_<ConversionType>("ConversionType")
      .value("NoConversion", ConversionType::NoConversion)
      .value("Linear", ConversionType::Linear)
      .value("Rational", ConversionType::Rational)
      .value("Algebraic", ConversionType::Algebraic)
      .value("ValueToValueInterpolation",
             ConversionType::ValueToValueInterpolation)
      .value("ValueToValue", ConversionType::ValueToValue)
      .value("ValueRangeToValue", ConversionType::ValueRangeToValue)
      .value("ValueToText", ConversionType::ValueToText)
      .value("ValueRangeToText", ConversionType::ValueRangeToText)
      .value("TextToValue", ConversionType::TextToValue)
      .value("TextToTranslation", ConversionType::TextToTranslation)
      .value("BitfieldToText", ConversionType::BitfieldToText)
      .value("Polynomial", ConversionType::Polynomial)
      .value("Exponential", ConversionType::Exponential)
      .value("Logarithmic", ConversionType::Logarithmic)
      .value("DateConversion", ConversionType::DateConversion)
      .value("TimeConversion", ConversionType::TimeConversion);

  constant("CcFlag_PrecisionValid", mdf::CcFlag::PrecisionValid);
  constant("CcFlag_RangeValid", mdf::CcFlag::RangeValid);
  constant("CcFlag_StatusString", mdf::CcFlag::StatusString);

  class_<ChannelConversionWrapped>("ChannelConversion")
      .function("getIndex", &ChannelConversionWrapped::GetIndex)
      .function("getName", &ChannelConversionWrapped::GetName)
      .function("setName", &ChannelConversionWrapped::SetName)
      .function("getDescription", &ChannelConversionWrapped::GetDescription)
      .function("setDescription", &ChannelConversionWrapped::SetDescription)
      .function("getUnit", &ChannelConversionWrapped::GetUnit)
      .function("setUnit", &ChannelConversionWrapped::SetUnit)
      .function("getType", &ChannelConversionWrapped::GetType)
      .function("setType", &ChannelConversionWrapped::SetType)
      .function("isPrecisionUsed", &ChannelConversionWrapped::IsPrecisionUsed)
      .function("getPrecision", &ChannelConversionWrapped::GetPrecision)
      .function("isRangeUsed", &ChannelConversionWrapped::IsRangeUsed)
      .function("getRangeMin", &ChannelConversionWrapped::GetRangeMin)
      .function("getRangeMax", &ChannelConversionWrapped::GetRangeMax)
      .function("setRange", &ChannelConversionWrapped::SetRange)
      .function("getFlags", &ChannelConversionWrapped::GetFlags)
      .function("getInverse", &ChannelConversionWrapped::GetInverse)
      .function("getMetadata", &ChannelConversionWrapped::GetMetadata)
      .function("getReference", &ChannelConversionWrapped::GetReference)
      .function("setReference", &ChannelConversionWrapped::SetReference)
      .function("getParameter", &ChannelConversionWrapped::GetParameter)
      .function("getParameterUint", &ChannelConversionWrapped::GetParameterUint)
      .function("setParameter", select_overload<void(uint16_t, double)>(
                                    &ChannelConversionWrapped::SetParameter))
      .function("setParameterUint",
                select_overload<void(uint16_t, uint64_t)>(
                    &ChannelConversionWrapped::SetParameter))
      .function("createInverse", &ChannelConversionWrapped::CreateInverse);

  register_vector<ChannelConversionWrapped>("std::vector<ChannelConversion>");

  enum_<ChannelType>("ChannelType")
      .value("FixedLength", ChannelType::FixedLength)
      .value("VariableLength", ChannelType::VariableLength)
      .value("Master", ChannelType::Master)
      .value("VirtualMaster", ChannelType::VirtualMaster)
      .value("Sync", ChannelType::Sync)
      .value("MaxLength", ChannelType::MaxLength)
      .value("VirtualData", ChannelType::VirtualData);

  enum_<ChannelSyncType>("ChannelSyncType")
      .value("None", ChannelSyncType::None)
      .value("Time", ChannelSyncType::Time)
      .value("Angle", ChannelSyncType::Angle)
      .value("Distance", ChannelSyncType::Distance)
      .value("Index", ChannelSyncType::Index);

  enum_<ChannelDataType>("ChannelDataType")
      .value("UnsignedIntegerLe", ChannelDataType::UnsignedIntegerLe)
      .value("UnsignedIntegerBe", ChannelDataType::UnsignedIntegerBe)
      .value("SignedIntegerLe", ChannelDataType::SignedIntegerLe)
      .value("SignedIntegerBe", ChannelDataType::SignedIntegerBe)
      .value("FloatLe", ChannelDataType::FloatLe)
      .value("FloatBe", ChannelDataType::FloatBe)
      .value("StringAscii", ChannelDataType::StringAscii)
      .value("StringUTF8", ChannelDataType::StringUTF8)
      .value("StringUTF16Le", ChannelDataType::StringUTF16Le)
      .value("StringUTF16Be", ChannelDataType::StringUTF16Be)
      .value("ByteArray", ChannelDataType::ByteArray)
      .value("MimeSample", ChannelDataType::MimeSample)
      .value("MimeStream", ChannelDataType::MimeStream)
      .value("CanOpenDate", ChannelDataType::CanOpenDate)
      .value("CanOpenTime", ChannelDataType::CanOpenTime)
      .value("ComplexLe", ChannelDataType::ComplexLe)
      .value("ComplexBe", ChannelDataType::ComplexBe);

  constant("CnFlag_AllValuesInvalid", mdf::CnFlag::AllValuesInvalid);
  constant("CnFlag_InvalidValid", mdf::CnFlag::InvalidValid);
  constant("CnFlag_PrecisionValid", mdf::CnFlag::PrecisionValid);
  constant("CnFlag_RangeValid", mdf::CnFlag::RangeValid);
  constant("CnFlag_LimitValid", mdf::CnFlag::LimitValid);
  constant("CnFlag_ExtendedLimitValid", mdf::CnFlag::ExtendedLimitValid);
  constant("CnFlag_Discrete", mdf::CnFlag::Discrete);
  constant("CnFlag_Calibration", mdf::CnFlag::Calibration);
  constant("CnFlag_Calculated", mdf::CnFlag::Calculated);
  constant("CnFlag_Virtual", mdf::CnFlag::Virtual);
  constant("CnFlag_BusEvent", mdf::CnFlag::BusEvent);
  constant("CnFlag_StrictlyMonotonous", mdf::CnFlag::StrictlyMonotonous);
  constant("CnFlag_DefaultX", mdf::CnFlag::DefaultX);
  constant("CnFlag_EventSignal", mdf::CnFlag::EventSignal);
  constant("CnFlag_VlsdDataStream", mdf::CnFlag::VlsdDataStream);

  class_<ChannelWrapped>("Channel")
      .function("getIndex", &ChannelWrapped::GetIndex)
      .function("getName", &ChannelWrapped::GetName)
      .function("setName", &ChannelWrapped::SetName)
      .function("getDisplayName", &ChannelWrapped::GetDisplayName)
      .function("setDisplayName", &ChannelWrapped::SetDisplayName)
      .function("getDescription", &ChannelWrapped::GetDescription)
      .function("setDescription", &ChannelWrapped::SetDescription)
      .function("isUnitUsed", &ChannelWrapped::IsUnitUsed)
      .function("getUnit", &ChannelWrapped::GetUnit)
      .function("setUnit", &ChannelWrapped::SetUnit)
      .function("getType", &ChannelWrapped::GetType)
      .function("setType", &ChannelWrapped::SetType)
      .function("getSync", &ChannelWrapped::GetSync)
      .function("setSync", &ChannelWrapped::SetSync)
      .function("getDataType", &ChannelWrapped::GetDataType)
      .function("setDataType", &ChannelWrapped::SetDataType)
      .function("getFlags", &ChannelWrapped::GetFlags)
      .function("setFlags", &ChannelWrapped::SetFlags)
      .function("getDataBytes", &ChannelWrapped::GetDataBytes)
      .function("setDataBytes", &ChannelWrapped::SetDataBytes)
      .function("isPrecisionUsed", &ChannelWrapped::IsPrecisionUsed)
      .function("getPrecision", &ChannelWrapped::GetPrecision)
      .function("isRangeUsed", &ChannelWrapped::IsRangeUsed)
      .function("getRangeMin", &ChannelWrapped::GetRangeMin)
      .function("getRangeMax", &ChannelWrapped::GetRangeMax)
      .function("setRange", &ChannelWrapped::SetRange)
      .function("isLimitUsed", &ChannelWrapped::IsLimitUsed)
      .function("getLimitMin", &ChannelWrapped::GetLimitMin)
      .function("getLimitMax", &ChannelWrapped::GetLimitMax)
      .function("setLimit", &ChannelWrapped::SetLimit)
      .function("isExtLimitUsed", &ChannelWrapped::IsExtLimitUsed)
      .function("getExtLimitMin", &ChannelWrapped::GetExtLimitMin)
      .function("getExtLimitMax", &ChannelWrapped::GetExtLimitMax)
      .function("setExtLimit", &ChannelWrapped::SetExtLimit)
      .function("getSamplingRate", &ChannelWrapped::GetSamplingRate)
      .function("getVlsdRecordId", &ChannelWrapped::GetVlsdRecordId)
      .function("setVlsdRecordId", &ChannelWrapped::SetVlsdRecordId)
      .function("getBitCount", &ChannelWrapped::GetBitCount)
      .function("setBitCount", &ChannelWrapped::SetBitCount)
      .function("getBitOffset", &ChannelWrapped::GetBitOffset)
      .function("setBitOffset", &ChannelWrapped::SetBitOffset)
      .function("getMetaData", &ChannelWrapped::GetMetaData)
      .function("getSourceInformation", &ChannelWrapped::GetSourceInformation)
      .function("getChannelConversion", &ChannelWrapped::GetChannelConversion)
      .function("getChannelCompositions",
                &ChannelWrapped::GetChannelCompositions)
      .function("createMetaData", &ChannelWrapped::CreateMetaData)
      .function("createSourceInformation",
                &ChannelWrapped::CreateSourceInformation)
      .function("createChannelConversion",
                &ChannelWrapped::CreateChannelConversion)
      .function("createChannelComposition",
                &ChannelWrapped::CreateChannelComposition)
      .function("setChannelValueInt64",
                select_overload<void(const int64_t, bool)>(
                    &ChannelWrapped::SetChannelValue))
      .function("setChannelValueUint64",
                select_overload<void(const uint64_t, bool)>(
                    &ChannelWrapped::SetChannelValue))
      .function("setChannelValueDouble",
                select_overload<void(const double, bool)>(
                    &ChannelWrapped::SetChannelValue))
      .function("setChannelValueString",
                select_overload<void(const std::string&, bool)>(
                    &ChannelWrapped::SetChannelValue))
      .function("setChannelValueVector",
                select_overload<void(std::vector<uint8_t>, bool)>(
                    &ChannelWrapped::SetChannelValue));

  register_vector<ChannelWrapped>("std::vector<Channel>");

  constant("CgFlag_VlsdChannel", mdf::CgFlag::VlsdChannel);
  constant("CgFlag_BusEvent", mdf::CgFlag::BusEvent);
  constant("CgFlag_PlainBusEvent", mdf::CgFlag::PlainBusEvent);
  constant("CgFlag_RemoteMaster", mdf::CgFlag::RemoteMaster);
  constant("CgFlag_EventSignal", mdf::CgFlag::EventSignal);

  class_<ChannelGroupWrapped>("ChannelGroup")
      .function("getIndex", &ChannelGroupWrapped::GetIndex)
      .function("getRecordId", &ChannelGroupWrapped::GetRecordId)
      .function("getName", &ChannelGroupWrapped::GetName)
      .function("setName", &ChannelGroupWrapped::SetName)
      .function("getDescription", &ChannelGroupWrapped::GetDescription)
      .function("setDescription", &ChannelGroupWrapped::SetDescription)
      .function("getNofSamples", &ChannelGroupWrapped::GetNofSamples)
      .function("setNofSamples", &ChannelGroupWrapped::SetNofSamples)
      .function("getFlags", &ChannelGroupWrapped::GetFlags)
      .function("setFlags", &ChannelGroupWrapped::SetFlags)
      .function("getPathSeparator", &ChannelGroupWrapped::GetPathSeparator)
      .function("setPathSeparator", &ChannelGroupWrapped::SetPathSeparator)
      .function("getMetaData", &ChannelGroupWrapped::GetMetaData)
      .function("getChannels", &ChannelGroupWrapped::GetChannels)
      .function("getSourceInformation",
                &ChannelGroupWrapped::GetSourceInformation)
      .function("getXChannel", &ChannelGroupWrapped::GetXChannel)
      .function("createMetaData", &ChannelGroupWrapped::CreateMetaData)
      .function("createChannel", &ChannelGroupWrapped::CreateChannel)
      .function("createSourceInformation",
                &ChannelGroupWrapped::CreateSourceInformation);

  register_vector<ChannelGroupWrapped>("std::vector<ChannelGroup>");

  class_<DataGroupWrapped>("DataGroup")
      .function("getIndex", &DataGroupWrapped::GetIndex)
      .function("getDescription", &DataGroupWrapped::GetDescription)
      .function("getRecordIdSize", &DataGroupWrapped::GetRecordIdSize)
      .function("getMetaData", &DataGroupWrapped::GetMetaData)
      .function("getChannelGroups", &DataGroupWrapped::GetChannelGroups)
      .function("isRead", &DataGroupWrapped::IsRead)
      .function("createMetaData", &DataGroupWrapped::CreateMetaData)
      .function("createChannelGroup", &DataGroupWrapped::CreateChannelGroup)
      .function("findParentChannelGroup",
                &DataGroupWrapped::FindParentChannelGroup)
      .function("resetSample", &DataGroupWrapped::ResetSample);

  register_vector<DataGroupWrapped>("std::vector<DataGroup>");

  class_<ChannelObserverWrapped>("ChannelObserver")
      .constructor<DataGroupWrapped, ChannelGroupWrapped, ChannelWrapped>()
      .constructor<DataGroupWrapped, const std::string&>()
      .function("GetNofSamples", &ChannelObserverWrapped::GetNofSamples)
      .function("GetName", &ChannelObserverWrapped::GetName)
      .function("GetUnit", &ChannelObserverWrapped::GetUnit)
      .function("GetChannel", &ChannelObserverWrapped::GetChannel)
      .function("IsMaster", &ChannelObserverWrapped::IsMaster)
      .function("HasChannelValueInt64",
                &ChannelObserverWrapped::HasChannelValueInt64)
      .function("hasChannelValueUint64",
                &ChannelObserverWrapped::hasChannelValueUint64)
      .function("HasChannelValueDouble",
                &ChannelObserverWrapped::HasChannelValueDouble)
      .function("HasChannelValueString",
                &ChannelObserverWrapped::HasChannelValueString)
      .function("HasChannelValueUint8Vector",
                &ChannelObserverWrapped::HasChannelValueUint8Vector)
      .function("HasEngValueUint64", &ChannelObserverWrapped::HasEngValueUint64)
      .function("HasEngValueInt64", &ChannelObserverWrapped::HasEngValueInt64)
      .function("HasEngValueDouble", &ChannelObserverWrapped::HasEngValueDouble)
      .function("HasEngValueString", &ChannelObserverWrapped::HasEngValueString)
      .function("HasEngValueUint8Vector",
                &ChannelObserverWrapped::HasEngValueUint8Vector)
      .function("GetChannelValueInt64",
                &ChannelObserverWrapped::GetChannelValueInt64)
      .function("GetChannelValueUint64",
                &ChannelObserverWrapped::GetChannelValueUint64)
      .function("GetChannelValueDouble",
                &ChannelObserverWrapped::GetChannelValueDouble)
      .function("GetChannelValueString",
                &ChannelObserverWrapped::GetChannelValueString)
      .function("GetChannelValueUint8Vector",
                &ChannelObserverWrapped::GetChannelValueUint8Vector)
      .function("GetEngValueInt64", &ChannelObserverWrapped::GetEngValueInt64)
      .function("GetEngValueUint64", &ChannelObserverWrapped::GetEngValueUint64)
      .function("GetEngValueDouble", &ChannelObserverWrapped::GetEngValueDouble)
      .function("GetEngValueString", &ChannelObserverWrapped::GetEngValueString)
      .function("GetEngValueUint8Vector",
                &ChannelObserverWrapped::GetEngValueUint8Vector);

  register_vector<ChannelObserverWrapped>("std::vector<ChannelObserver>");
  function("createChannelObserverForChannelGroup",
           &CreateChannelObserverForChannelGroup);

  class_<FileHistoryWrapped>("FileHistory")
      .function("getIndex", &FileHistoryWrapped::GetIndex)
      .function("getTime", &FileHistoryWrapped::GetTime)
      .function("setTime", &FileHistoryWrapped::SetTime)
      .function("getMetaData", &FileHistoryWrapped::GetMetaData)
      .function("getDescription", &FileHistoryWrapped::GetDescription)
      .function("setDescription", &FileHistoryWrapped::SetDescription)
      .function("getToolName", &FileHistoryWrapped::GetToolName)
      .function("setToolName", &FileHistoryWrapped::SetToolName)
      .function("getToolVendor", &FileHistoryWrapped::GetToolVendor)
      .function("setToolVendor", &FileHistoryWrapped::SetToolVendor)
      .function("getToolVersion", &FileHistoryWrapped::GetToolVersion)
      .function("setToolVersion", &FileHistoryWrapped::SetToolVersion)
      .function("getUserName", &FileHistoryWrapped::GetUserName)
      .function("setUserName", &FileHistoryWrapped::SetUserName);
  register_vector<FileHistoryWrapped>("std::vector<FileHistory>");

  class_<HeaderWrapped>("Header")
      .function("getIndex", &HeaderWrapped::GetIndex)
      .function("getDescription", &HeaderWrapped::GetDescription)
      .function("setDescription", &HeaderWrapped::SetDescription)
      .function("getAuthor", &HeaderWrapped::GetAuthor)
      .function("setAuthor", &HeaderWrapped::SetAuthor)
      .function("getDepartment", &HeaderWrapped::GetDepartment)
      .function("setDepartment", &HeaderWrapped::SetDepartment)
      .function("getProject", &HeaderWrapped::GetProject)
      .function("setProject", &HeaderWrapped::SetProject)
      .function("getSubject", &HeaderWrapped::GetSubject)
      .function("setSubject", &HeaderWrapped::SetSubject)
      .function("getMeasurementId", &HeaderWrapped::GetMeasurementId)
      .function("setMeasurementId", &HeaderWrapped::SetMeasurementId)
      .function("getRecorderId", &HeaderWrapped::GetRecorderId)
      .function("setRecorderId", &HeaderWrapped::SetRecorderId)
      .function("getRecorderIndex", &HeaderWrapped::GetRecorderIndex)
      .function("setRecorderIndex", &HeaderWrapped::SetRecorderIndex)
      .function("getStartTime", &HeaderWrapped::GetStartTime)
      .function("setStartTime", &HeaderWrapped::SetStartTime)
      .function("isStartAngleUsed", &HeaderWrapped::IsStartAngleUsed)
      .function("getStartAngle", &HeaderWrapped::GetStartAngle)
      .function("setStartAngle", &HeaderWrapped::SetStartAngle)
      .function("isStartDistanceUsed", &HeaderWrapped::IsStartDistanceUsed)
      .function("getStartDistance", &HeaderWrapped::GetStartDistance)
      .function("setStartDistance", &HeaderWrapped::SetStartDistance)
      .function("getMetaData", &HeaderWrapped::GetMetaData)
      .function("getAttachments", &HeaderWrapped::GetAttachments)
      .function("getFileHistorys", &HeaderWrapped::GetFileHistorys)
      .function("getEvents", &HeaderWrapped::GetEvents)
      .function("getDataGroups", &HeaderWrapped::GetDataGroups)
      .function("createAttachment", &HeaderWrapped::CreateAttachment)
      .function("createFileHistory", &HeaderWrapped::CreateFileHistory)
      .function("createEvent", &HeaderWrapped::CreateEvent)
      .function("createDataGroup", &HeaderWrapped::CreateDataGroup);

  class_<FileWrapped>("File")
      .function("getName", &FileWrapped::GetName)
      .function("setName", &FileWrapped::SetName)
      .function("getFileName", &FileWrapped::GetFileName)
      .function("setFileName", &FileWrapped::SetFileName)
      .function("getVersion", &FileWrapped::GetVersion)
      .function("getMainVersion", &FileWrapped::GetMainVersion)
      .function("getMinorVersion", &FileWrapped::GetMinorVersion)
      .function("setMinorVersion", &FileWrapped::SetMinorVersion)
      .function("getProgramId", &FileWrapped::GetProgramId)
      .function("setProgramId", &FileWrapped::SetProgramId)
      .function("getFinalized", &FileWrapped::GetFinalized)
      .function("getHeader", &FileWrapped::GetHeader)
      .function("getIsMdf4", &FileWrapped::GetIsMdf4)
      .function("getAttachments", &FileWrapped::GetAttachments)
      .function("getDataGroups", &FileWrapped::GetDataGroups)
      .function("createAttachment", &FileWrapped::CreateAttachment)
      .function("createDataGroup", &FileWrapped::CreateDataGroup);

  class_<ReaderWrapped>("Reader")
      .constructor<const std::string&>()
      .function("getIndex", &ReaderWrapped::GetIndex)
      .function("isOk", &ReaderWrapped::IsOk)
      .function("getFile", &ReaderWrapped::GetFile)
      .function("getHeader", &ReaderWrapped::GetHeader)
      .function("getDataGroup", &ReaderWrapped::GetDataGroup)
      .function("open", &ReaderWrapped::Open)
      .function("close", &ReaderWrapped::Close)
      .function("readHeader", &ReaderWrapped::ReadHeader)
      .function("readMeasurementInfo", &ReaderWrapped::ReadMeasurementInfo)
      .function("readEverythingButData", &ReaderWrapped::ReadEverythingButData)
      .function("readData", &ReaderWrapped::ReadData);

  enum_<MdfWriterType>("MdfWriterType")
      .value("Mdf3Basic", MdfWriterType::Mdf3Basic)
      .value("Mdf4Basic", MdfWriterType::Mdf4Basic)
      .value("MdfBusLogger", MdfWriterType::MdfBusLogger);

  enum_<MdfBusType>("MdfBusType")
      .value("CAN", MdfBusType::CAN)
      .value("LIN", MdfBusType::LIN)
      .value("FlexRay", MdfBusType::FlexRay)
      .value("MOST", MdfBusType::MOST)
      .value("Ethernet", MdfBusType::Ethernet)
      .value("UNKNOWN", MdfBusType::UNKNOWN);

  class_<WriterWrapped>("Writer")
      .constructor<mdf::MdfWriterType, const std::string&>()
      .function("getFile", &WriterWrapped::GetFile)
      .function("getHeader", &WriterWrapped::GetHeader)
      .function("isFileNew", &WriterWrapped::IsFileNew)
      .function("getCompressData", &WriterWrapped::GetCompressData)
      .function("setCompressData", &WriterWrapped::SetCompressData)
      .function("getPreTrigTime", &WriterWrapped::GetPreTrigTime)
      .function("setPreTrigTime", &WriterWrapped::SetPreTrigTime)
      .function("getStartTime", &WriterWrapped::GetStartTime)
      .function("getStopTime", &WriterWrapped::GetStopTime)
      .function("getBusType", &WriterWrapped::GetBusType)
      .function("setBusType", &WriterWrapped::SetBusType)
      .function("getStorageType", &WriterWrapped::GetStorageType)
      .function("setStorageType", &WriterWrapped::SetStorageType)
      .function("getMaxLength", &WriterWrapped::GetMaxLength)
      .function("setMaxLength", &WriterWrapped::SetMaxLength)
      .function("createDataGroup", &WriterWrapped::CreateDataGroup)
      .function("initMeasurement", &WriterWrapped::InitMeasurement)
      .function("saveSample", &WriterWrapped::SaveSample)
      .function("startMeasurement", &WriterWrapped::StartMeasurement)
      .function("stopMeasurement", &WriterWrapped::StopMeasurement)
      .function("finalizeMeasurement", &WriterWrapped::FinalizeMeasurement);
}
