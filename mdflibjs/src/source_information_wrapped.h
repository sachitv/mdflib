/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/isourceinformation.h>

#include <stdexcept>
#include <string>

#include "metadata_wrapped.h"

namespace mdflibjs {
class SourceInformationWrapped {
 private:
  mdf::ISourceInformation* source_information_{};

 public:
  SourceInformationWrapped(mdf::ISourceInformation* sourceInformation)
      : source_information_(sourceInformation) {
    if (sourceInformation == nullptr)
      throw std::runtime_error("MdfSourceInformationInit failed");
  }
  SourceInformationWrapped(const mdf::ISourceInformation* sourceInformation)
      : SourceInformationWrapped(
            const_cast<mdf::ISourceInformation*>(sourceInformation)) {}
  int64_t GetIndex() const { return source_information_->Index(); }
  std::string GetName() const { return source_information_->Name(); }
  void SetName(const std::string& name) { source_information_->Name(name); }
  std::string GetDescription() const {
    return source_information_->Description();
  }
  void SetDescription(const std::string& desc) {
    source_information_->Description(desc);
  }
  std::string GetPath() const { return source_information_->Path(); }
  void SetPath(const std::string& path) { source_information_->Path(path); }
  mdf::SourceType GetType() const { return source_information_->Type(); }
  void SetType(mdf::SourceType type) { source_information_->Type(type); }
  mdf::BusType GetBus() const { return source_information_->Bus(); }
  void SetBus(mdf::BusType bus) { source_information_->Bus(bus); }
  uint8_t GetFlags() const { return source_information_->Flags(); }
  void SetFlags(uint8_t flags) { source_information_->Flags(flags); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(source_information_->MetaData());
  }
  MetadataWrapped CreateMetaData() {
    return MetadataWrapped(source_information_->CreateMetaData());
  }
};
}  // namespace mdflibjs