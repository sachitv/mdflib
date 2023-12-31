/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/mdffile.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "attachment_wrapped.h"
#include "data_group_wrapped.h"
#include "header_wrapped.h"

namespace mdflibjs {
class FileWrapped {
 private:
  mdf::MdfFile* file_;

 public:
  FileWrapped(mdf::MdfFile* file) : file_(file) {
    if (file == nullptr) {
      throw std::runtime_error("MdfFileInit failed");
    }
  }
  FileWrapped(const mdf::MdfFile* file)
      : FileWrapped(const_cast<mdf::MdfFile*>(file)) {}
  std::string GetName() const { return file_->Name(); }
  void SetName(const std::string& name) { file_->Name(name); }
  std::string GetFileName() const { return file_->FileName(); }
  void SetFileName(const std::string& filename) { file_->FileName(filename); }
  std::string GetVersion() const { return file_->Version(); }
  int GetMainVersion() const { return file_->MainVersion(); }
  int GetMinorVersion() const { return file_->MinorVersion(); }
  void SetMinorVersion(int minor) { file_->MinorVersion(minor); }
  std::string GetProgramId() const { return file_->ProgramId(); }
  void SetProgramId(const std::string& program_id) {
    file_->ProgramId(program_id);
  }
  bool GetFinalized(uint16_t standard_flags, uint16_t custom_flags) {
    return file_->IsFinalized(standard_flags, custom_flags);
  }
  HeaderWrapped GetHeader() const { return HeaderWrapped(file_->Header()); }
  bool GetIsMdf4() { return file_->IsMdf4(); }
  std::vector<AttachmentWrapped> GetAttachments() const {
    mdf::AttachmentList attachments;
    file_->Attachments(attachments);

    std::vector<AttachmentWrapped> result;
    for (const auto& attachment : attachments) {
      result.emplace_back(AttachmentWrapped(attachment));
    }
    return result;
  }
  std::vector<DataGroupWrapped> GetDataGroups() const {
    mdf::DataGroupList data_groups;
    file_->DataGroups(data_groups);

    std::vector<DataGroupWrapped> result;
    for (const auto& data_group : data_groups) {
      result.emplace_back(DataGroupWrapped(data_group));
    }
    return result;
  }
  AttachmentWrapped CreateAttachment() {
    return AttachmentWrapped(file_->CreateAttachment());
  }
  DataGroupWrapped CreateDataGroup() {
    return DataGroupWrapped(file_->CreateDataGroup());
  }
};
}  // namespace mdflibjs