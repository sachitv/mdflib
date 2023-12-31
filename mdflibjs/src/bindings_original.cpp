#include <emscripten/bind.h>

#include <mdf/canmessage.h>
#include <mdf/cryptoutil.h>
#include <mdf/etag.h>
#include <mdf/iattachment.h>
#include <mdf/iblock.h>

using namespace emscripten;
using namespace mdf;

// Wrappers for ETag
void ETag_SetNumberValue(ETag& tag, const double value) {
    tag.Value(value);
}
double ETag_GetNumberValue(const ETag& tag) {
    return tag.Value<bool>();
}

void ETag_SetBoolValue(ETag& tag, const bool value) {
    tag.Value(value);
}
bool ETag_GetBoolValue(const ETag& tag) {
    return tag.Value<bool>();
}

void ETag_SetStringValue(ETag& tag, const std::string& value) {
    tag.Value(value);
}
std::string ETag_GetStringValue(const ETag& tag) {
    return tag.Value<std::string>();
}

// Wrapper for the IAttachment interface
// struct IAttachmentWrapper : public wrapper<IAttachment> {
//     EMSCRIPTEN_WRAPPER(IAttachmentWrapper);

//     void CreatorIndex(uint16_t creator) override {
//         return call<void>("CreatorIndex", creator);
//     }

//     uint16_t CreatorIndex() const override {
//         return call<uint16_t>("CreatorIndex");
//     }

//     void IsEmbedded(bool embed) override {
//         return call<void>("IsEmbedded", embed);
//     }

//     bool IsEmbedded() const override {
//         return call<bool>("IsEmbedded");
//     }

//     void IsCompressed(bool compress) override {
//         return call<void>("IsCompressed", compress);
//     }

//     bool IsCompressed() const override {
//         return call<bool>("IsCompressed");
//     }

//     std::optional<std::string> Md5() const override {
//         return call<std::optional<std::string>>("Md5");
//     }

//     void FileName(const std::string& filename) override {
//         return call<void>("FileName", filename);
//     }

//     const std::string& FileName() const override {
//         return call<const std::string&>("FileName");
//     }

//     void FileType(const std::string& file_type) override {
//         return call<void>("FileType", file_type);
//     }

//     const std::string& FileType() const override {
//         return call<const std::string&>("FileType");
//     }

//     IMetaData* CreateMetaData() override {
//         throw std::runtime_error("Not implemented since abstract base class + pointer return type is currently unsupported");
//     }

//     IMetaData* MetaData() const override {
//         throw std::runtime_error("Not implemented since abstract base class + pointer return type is currently unsupported");
//     }

//     int64_t Index() const override {
//         return call<int64_t>("Index");
//     }

//     std::string BlockType() const override {
//         return call<std::string>("BlockType");
//     }
// };

// Binding code
EMSCRIPTEN_BINDINGS(mdflibjs) {
  // canmessage.h bindings.

  // Bind the CanErrorType enum
  enum_<CanErrorType>("CanErrorType")
      .value("UNKNOWN_ERROR", CanErrorType::UNKNOWN_ERROR)
      .value("BIT_ERROR", CanErrorType::BIT_ERROR)
      .value("FORM_ERROR", CanErrorType::FORM_ERROR)
      .value("BIT_STUFFING_ERROR", CanErrorType::BIT_STUFFING_ERROR)
      .value("CRC_ERROR", CanErrorType::CRC_ERROR)
      .value("ACK_ERROR", CanErrorType::ACK_ERROR);

  // Bind the MessageType enum
  enum_<MessageType>("MessageType")
      .value("CAN_DataFrame", MessageType::CAN_DataFrame)
      .value("CAN_RemoteFrame", MessageType::CAN_RemoteFrame)
      .value("CAN_ErrorFrame", MessageType::CAN_ErrorFrame)
      .value("CAN_OverloadFrame", MessageType::CAN_OverloadFrame);

  // Bind the CanMessage class
  class_<CanMessage>("CanMessage")
      .constructor<>()
      // Setters with select_overload
      .function("setMessageId",
                select_overload<void(uint32_t)>(&CanMessage::MessageId))
      .function("setExtendedId",
                select_overload<void(bool)>(&CanMessage::ExtendedId))
      .function("setDlc", select_overload<void(uint8_t)>(&CanMessage::Dlc))
      .function("setDataLength",
                select_overload<void(size_t)>(&CanMessage::DataLength))
      .function("setDataBytes",
                select_overload<void(const std::vector<uint8_t>&)>(
                    &CanMessage::DataBytes))
      .function("setDataIndex",
                select_overload<void(uint64_t)>(&CanMessage::DataIndex))
      .function("setDir", select_overload<void(bool)>(&CanMessage::Dir))
      .function("setSrr", select_overload<void(bool)>(&CanMessage::Srr))
      .function("setEdl", select_overload<void(bool)>(&CanMessage::Edl))
      .function("setBrs", select_overload<void(bool)>(&CanMessage::Brs))
      .function("setEsi", select_overload<void(bool)>(&CanMessage::Esi))
      .function("setRtr", select_overload<void(bool)>(&CanMessage::Rtr))
      .function("setWakeUp", select_overload<void(bool)>(&CanMessage::WakeUp))
      .function("setSingleWire",
                select_overload<void(bool)>(&CanMessage::SingleWire))
      .function("setBusChannel",
                select_overload<void(uint8_t)>(&CanMessage::BusChannel))
      .function("setBitPosition",
                select_overload<void(uint8_t)>(&CanMessage::BitPosition))
      .function("setErrorType",
                select_overload<void(CanErrorType)>(&CanMessage::ErrorType))
      // Getters with select_overload
      .function("getMessageId",
                select_overload<uint32_t() const>(&CanMessage::MessageId))
      .function("getCanId",
                select_overload<uint32_t() const>(&CanMessage::CanId))
      .function("isExtendedId",
                select_overload<bool() const>(&CanMessage::ExtendedId))
      .function("getDlc", select_overload<uint8_t() const>(&CanMessage::Dlc))
      .function("getDataLength",
                select_overload<size_t() const>(&CanMessage::DataLength))
      .function("getDataBytes",
                select_overload<const std::vector<uint8_t>&() const>(
                    &CanMessage::DataBytes))
      .function("getDataIndex",
                select_overload<uint64_t() const>(&CanMessage::DataIndex))
      .function("getDir", select_overload<bool() const>(&CanMessage::Dir))
      .function("getSrr", select_overload<bool() const>(&CanMessage::Srr))
      .function("getEdl", select_overload<bool() const>(&CanMessage::Edl))
      .function("getBrs", select_overload<bool() const>(&CanMessage::Brs))
      .function("getEsi", select_overload<bool() const>(&CanMessage::Esi))
      .function("getRtr", select_overload<bool() const>(&CanMessage::Rtr))
      .function("getWakeUp", select_overload<bool() const>(&CanMessage::WakeUp))
      .function("isSingleWire",
                select_overload<bool() const>(&CanMessage::SingleWire))
      .function("getBusChannel",
                select_overload<uint8_t() const>(&CanMessage::BusChannel))
      .function("getBitPosition",
                select_overload<uint8_t() const>(&CanMessage::BitPosition))
      .function("getErrorType",
                select_overload<CanErrorType() const>(&CanMessage::ErrorType))
      // Other methods
      .class_function("dlcToLength", &CanMessage::DlcToLength)
      .function("reset", &CanMessage::Reset);

    // cryptoutil bindings.
    function("CreateMd5FileString", &CreateMd5FileString);

     class_<ETag>("ETag")
        .constructor<>()
        .function("setName", select_overload<void(const std::string&)>(&ETag::Name))
        .function("getName", select_overload<const std::string&() const>(&ETag::Name))
        .function("setDescription", select_overload<void(const std::string&)>(&ETag::Description))
        .function("getDescription", select_overload<const std::string&() const>(&ETag::Description))
        .function("setUnit", select_overload<void(const std::string&)>(&ETag::Unit))
        .function("getUnit", select_overload<const std::string&() const>(&ETag::Unit))
        .function("setUnitRef", select_overload<void(const std::string&)>(&ETag::UnitRef))
        .function("getUnitRef", select_overload<const std::string&() const>(&ETag::UnitRef))
        .function("setDataType", select_overload<void(ETagDataType)>(&ETag::DataType))
        .function("getDataType", select_overload<ETagDataType() const>(&ETag::DataType))
        .function("setType", select_overload<void(const std::string&)>(&ETag::Type))
        .function("getType", select_overload<const std::string&() const>(&ETag::Type))
        .function("setLanguage", select_overload<void(const std::string&)>(&ETag::Language))
        .function("getLanguage", select_overload<const std::string&() const>(&ETag::Language))
        .function("setReadOnly", select_overload<void(bool)>(&ETag::ReadOnly))
        .function("isReadOnly", select_overload<bool() const>(&ETag::ReadOnly))
        .function("setCreatorIndex", select_overload<void(int)>(&ETag::CreatorIndex))
        .function("getCreatorIndex", select_overload<int() const>(&ETag::CreatorIndex))
        .function("setNumberValue", &ETag_SetNumberValue)
        .function("setBooleanValue", &ETag_SetBoolValue)
        .function("setStringValue", &ETag_SetStringValue)
        .function("getNumberValue", &ETag_GetNumberValue)
        .function("getBooleanValue", &ETag_GetBoolValue)
        .function("getStringValue", &ETag_GetStringValue)
        // Add bindings for other types like int, float, etc.
        .function("addTag", &ETag::AddTag)
        .function("getTreeList", select_overload<const std::vector<ETag>&() const>(&ETag::TreeList));

    // Bind the ETagDataType enum
    enum_<ETagDataType>("ETagDataType")
        .value("StringType", ETagDataType::StringType)
        .value("DecimalType", ETagDataType::DecimalType)
        .value("IntegerType", ETagDataType::IntegerType)
        .value("FloatType", ETagDataType::FloatType)
        .value("BooleanType", ETagDataType::BooleanType)
        .value("DateType", ETagDataType::DateType)
        .value("TimeType", ETagDataType::TimeType)
        .value("DateTimeType", ETagDataType::DateTimeType);

    // For this class we don't allow subclassing since it's not needed.
    class_<IAttachment>("IAttachment")
        .function("creatorIndex", select_overload<void(uint16_t)>(&IAttachment::CreatorIndex), pure_virtual())
        .function("getCreatorIndex", select_overload<uint16_t() const>(&IAttachment::CreatorIndex), pure_virtual())
        .function("isEmbedded", select_overload<void(bool)>(&IAttachment::IsEmbedded), pure_virtual())
        .function("isEmbedded", select_overload<bool() const>(&IAttachment::IsEmbedded), pure_virtual())
        .function("IsCompressed", select_overload<void(bool)>(&IAttachment::IsCompressed), pure_virtual())
        .function("isCompressed", select_overload<bool() const>(&IAttachment::IsCompressed), pure_virtual())
        .function("getMd5", &IAttachment::Md5, pure_virtual())
        .function("fileName", select_overload<void(const std::string&)>(&IAttachment::FileName), pure_virtual())
        .function("getFileName", select_overload<const std::string&() const>(&IAttachment::FileName), pure_virtual())
        .function("fileType", select_overload<void(const std::string&)>(&IAttachment::FileType), pure_virtual())
        .function("getFileType", select_overload<const std::string&() const>(&IAttachment::FileType), pure_virtual())
        .function("createMetaData", &IAttachment::CreateMetaData, allow_raw_pointer<ret_val>(), pure_virtual())
        .function("getMetaData", &IAttachment::MetaData, allow_raw_pointer<ret_val>(), pure_virtual())
        .function("index", &IAttachment::Index, pure_virtual())
        .function("blockType", &IAttachment::BlockType, pure_virtual());

  // Bind other classes and functions as needed
}
