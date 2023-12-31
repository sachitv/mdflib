/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/ifilehistory.h>

#include <stdexcept>
#include <string>

#include "metadata_wrapped.h"

namespace mdflibjs {
class FileHistoryWrapped {
 private:
  mdf::IFileHistory* history_{};

 public:
  FileHistoryWrapped(mdf::IFileHistory* history) : history_(history) {
    if (history == nullptr)
    {
      throw std::runtime_error("MdfFileHistoryInit failed");
    }
  }
  FileHistoryWrapped(const mdf::IFileHistory* history)
      : FileHistoryWrapped(const_cast<mdf::IFileHistory*>(history)) {}
  int64_t GetIndex() const { return history_->Index(); }
  uint64_t GetTime() const { return history_->Time(); }
  void SetTime(uint64_t time) { history_->Time(time); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(history_->MetaData());
  }
  std::string GetDescription() const {
    return history_->Description();
  }
  void SetDescription(const std::string& desc) {
    history_->Description(desc);
  }
  std::string GetToolName() const {
    return history_->ToolName();
  }
  void SetToolName(const std::string& name) {
    return history_->ToolName(name);
  }
  std::string GetToolVendor() const {
    return history_->ToolVendor();
  }
  void SetToolVendor(const std::string& vendor) {
    history_->ToolVendor(vendor);
  }
  std::string GetToolVersion() const {
    return history_->ToolVersion();
  }
  void SetToolVersion(const std::string& version) {
    history_->ToolVersion(version);
  }
  std::string GetUserName() const {
    return history_->UserName();
  }
  void SetUserName(const std::string& user) {
    history_->UserName(user);
  }
};
}  // namespace mdflibjs
