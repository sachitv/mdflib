/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/ichannel.h>

#include <stdexcept>
#include <string>

#include "channel_conversion_wrapped.h"
#include "metadata_wrapped.h"
#include "source_information_wrapped.h"

namespace mdflibjs {
class ChannelWrapped {
 private:
  mdf::IChannel* channel_{};

 public:
  explicit ChannelWrapped(mdf::IChannel* channel) : channel_(channel) {
    if (channel == nullptr) throw std::runtime_error("MdfChannelInit failed");
  }
  explicit ChannelWrapped(const mdf::IChannel* channel)
      : ChannelWrapped(const_cast<mdf::IChannel*>(channel)) {}
  mdf::IChannel* GetChannel() const { return channel_; }
  int64_t GetIndex() const { return channel_->Index(); }
  std::string GetName() const { return channel_->Name(); }
  void SetName(const std::string& name) { channel_->Name(name); }
  std::string GetDisplayName() const { return channel_->DisplayName(); }
  void SetDisplayName(const std::string& name) { channel_->DisplayName(name); }
  std::string GetDescription() const { return channel_->Description(); }
  void SetDescription(const std::string& desc) { channel_->Description(desc); }
  bool IsUnitUsed() { return channel_->IsUnitValid(); }
  std::string GetUnit() const { return channel_->Unit(); }
  void SetUnit(const std::string& unit) { channel_->Unit(unit); }
  mdf::ChannelType GetType() const { return channel_->Type(); }
  void SetType(mdf::ChannelType type) { channel_->Type(type); }
  mdf::ChannelSyncType GetSync() const { return channel_->Sync(); }
  void SetSync(mdf::ChannelSyncType type) { channel_->Sync(type); }
  mdf::ChannelDataType GetDataType() const { return channel_->DataType(); }
  void SetDataType(mdf::ChannelDataType type) { channel_->DataType(type); }
  uint32_t GetFlags() const { return channel_->Flags(); }
  void SetFlags(uint32_t flags) { channel_->Flags(flags); }
  uint64_t GetDataBytes() const { return channel_->DataBytes(); }
  void SetDataBytes(uint64_t bytes) { channel_->DataBytes(bytes); }
  bool IsPrecisionUsed() { return channel_->IsDecimalUsed(); }
  uint8_t GetPrecision() const { return channel_->Decimals(); }
  bool IsRangeUsed() { return channel_->Range().has_value(); }
  double GetRangeMin() const { return channel_->Range()->first; }
  double GetRangeMax() const { return channel_->Range()->second; }
  void SetRange(double min, double max) { channel_->Range(min, max); }
  bool IsLimitUsed() { return channel_->Limit().has_value(); }
  double GetLimitMin() const { return channel_->Limit()->first; }
  double GetLimitMax() const { return channel_->Limit()->second; }
  void SetLimit(double min, double max) { channel_->Limit(min, max); }
  bool IsExtLimitUsed() { return channel_->ExtLimit().has_value(); }
  double GetExtLimitMin() const { return channel_->ExtLimit()->first; }
  double GetExtLimitMax() const { return channel_->ExtLimit()->second; }
  void SetExtLimit(double min, double max) { channel_->ExtLimit(min, max); }
  double GetSamplingRate() const { return channel_->SamplingRate(); }
  uint64_t GetVlsdRecordId() const { return channel_->VlsdRecordId(); }
  void SetVlsdRecordId(uint64_t record_id) {
    channel_->VlsdRecordId(record_id);
  }
  uint32_t GetBitCount() const { return channel_->BitCount(); }
  void SetBitCount(uint32_t bits) { channel_->BitCount(bits); }
  uint16_t GetBitOffset() const { return channel_->BitOffset(); }
  void SetBitOffset(uint16_t bits) { channel_->BitOffset(bits); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(channel_->MetaData());
  }
  const SourceInformationWrapped GetSourceInformation() const {
    return SourceInformationWrapped(channel_->SourceInformation());
  }
  const ChannelConversionWrapped GetChannelConversion() const {
    return ChannelConversionWrapped(channel_->ChannelConversion());
  }
  std::vector<ChannelWrapped> GetChannelCompositions() {
    std::vector<ChannelWrapped> result;
    for (const auto& channel : channel_->ChannelCompositions()) {
      result.emplace_back(ChannelWrapped(channel));
    }
    return result;
  }
  MetadataWrapped CreateMetaData() { return MetadataWrapped(channel_->CreateMetaData()); }
  SourceInformationWrapped CreateSourceInformation() {
    return SourceInformationWrapped(channel_->CreateSourceInformation());
  }
  ChannelConversionWrapped CreateChannelConversion() {
    return ChannelConversionWrapped(channel_->CreateChannelConversion());
  }
  ChannelWrapped CreateChannelComposition() {
    return ChannelWrapped(channel_->CreateChannelComposition());
  }
  void SetChannelValue(const int64_t value, bool valid = true) {
    channel_->SetChannelValue(value, valid);
  }
  void SetChannelValue(const uint64_t value, bool valid = true) {
    channel_->SetChannelValue(value, valid);
  }
  void SetChannelValue(const double value, bool valid = true) {
    channel_->SetChannelValue(value, valid);
  }
  void SetChannelValue(const std::string& value, bool valid = true) {
    channel_->SetChannelValue(value, valid);
  }
  void SetChannelValue(std::vector<uint8_t> value, bool valid = true) {
    channel_->SetChannelValue(value, valid);
  }
};
}  // namespace mdflibjs
