/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <string>

#include "mdf/ichannelconversion.h"

#include "metadata_wrapped.h"

namespace mdflibjs {
class ChannelConversionWrapped {
 private:
  mdf::IChannelConversion* conversion_{};

 public:
  ChannelConversionWrapped(mdf::IChannelConversion* conversion)
      : conversion_(conversion) {
    if (conversion == nullptr) {
      throw std::runtime_error("MdfChannelConversionInit failed");
    }
  }
  ChannelConversionWrapped(const mdf::IChannelConversion* conversion)
      : ChannelConversionWrapped(const_cast<mdf::IChannelConversion*>(conversion)) {
  }
  int64_t GetIndex() const { 
    return conversion_->Index();
  }
  std::string GetName() const {
    return conversion_->Name();
  }
  void SetName(const std::string&  name) {
    conversion_->Name(name);
  }
  std::string GetDescription() const {
    return conversion_->Description();
  }
  void SetDescription(const std::string&  desc) {
    conversion_->Description(desc);
  }
  std::string GetUnit() const {
    return conversion_->Unit();
  }
  void SetUnit(const std::string&  unit) {
    conversion_->Unit(unit);
  }
  mdf::ConversionType GetType() const {
    return conversion_->Type();
  }
  void SetType(mdf::ConversionType type) {
    conversion_->Type(type);
  }
  bool IsPrecisionUsed() {
    return conversion_->IsDecimalUsed();
  }
  uint8_t GetPrecision() const {
    return conversion_->Decimals();
  }
  bool IsRangeUsed() { 
    return conversion_->Range().has_value();
    }
  double GetRangeMin() const {
    return conversion_->Range()->first;
  }
  double GetRangeMax() const {
    return conversion_->Range()->second;
  }
  void SetRange(double min, double max) {
    conversion_->Range(min, max);
  }
  uint16_t GetFlags() const { 
    return conversion_->Flags(); 
  }
  const ChannelConversionWrapped GetInverse() const {
    return conversion_->Inverse();
  }
  const MetadataWrapped GetMetadata() const {
    return MetadataWrapped(conversion_->MetaData());
  }
  std::string GetReference(uint16_t index) const {
    return conversion_->Reference(index);
  }
  void SetReference(uint16_t index, const std::string&  ref) {
    conversion_->Reference(index, ref);
  }
  double GetParameter(uint16_t index) const {
    return conversion_->Parameter(index);
  }
  uint64_t GetParameterUint(uint16_t index) const {
    return conversion_->ParameterUint(index);
  }
  void SetParameter(uint16_t index, double param) {
    conversion_->Parameter(index, param);
  }
  void SetParameter(uint16_t index, uint64_t param) {
    conversion_->ParameterUint(index, param);
  }
  ChannelConversionWrapped CreateInverse() {
    return ChannelConversionWrapped(conversion_->CreateInverse());
  }
};
}  // namespace mdflibjs