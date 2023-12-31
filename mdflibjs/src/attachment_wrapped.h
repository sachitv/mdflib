/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/iattachment.h>

#include <string>

#include "metadata_wrapped.h"

namespace mdflibjs {
class AttachmentWrapped {
 private:
  mdf::IAttachment* attachment_{};

 public:
  AttachmentWrapped(mdf::IAttachment* attachment) : attachment_(attachment) {
    if (attachment == nullptr) {
      throw std::runtime_error("MdfAttachmentWrapperInit failed");
    }
  }
  AttachmentWrapped(const mdf::IAttachment* attachment)
      : AttachmentWrapped(const_cast<mdf::IAttachment*>(attachment)) {}

  int64_t GetIndex() const { return attachment_->Index(); }
  uint16_t GetCreatorIndex() const { return attachment_->CreatorIndex(); }
  void SetCreatorIndex(uint16_t index) { attachment_->CreatorIndex(index); }
  bool GetEmbedded() const { return attachment_->IsEmbedded(); }
  void SetEmbedded(bool embedded) { attachment_->IsEmbedded(embedded); }
  bool GetCompressed() const { return attachment_->IsCompressed(); }
  void SetCompressed(bool compressed) { attachment_->IsCompressed(compressed); }
  std::string GetMd5() { return attachment_->Md5().value_or(""); }
  std::string GetFileName() const { return attachment_->FileName(); }
  void SetFileName(const std::string& name) { attachment_->FileName(name); }
  std::string GetFileType() const { return attachment_->FileType(); }
  void SetFileType(const std::string& type) { attachment_->FileType(type); }
  MetadataWrapped GetMetaData() const { return attachment_->MetaData(); }
  MetadataWrapped CreateMetaData() { return attachment_->CreateMetaData(); }
  mdf::IAttachment* GetAttachment() const { return attachment_; }
};
}  // namespace mdflibjs