/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/etag.h>
#include <mdf/imetadata.h>

#include <vector>

namespace mdflibjs {
class MetadataWrapped {
 private:
  mdf::IMetaData* metadata_{};

 public:
  MetadataWrapped(mdf::IMetaData* metadata) : metadata_(metadata) {
    if (metadata == nullptr) {
      throw std::runtime_error("MdfMetaDataInit failed");
    }
  }
  MetadataWrapped(const mdf::IMetaData* metadata)
      : MetadataWrapped(const_cast<mdf::IMetaData*>(metadata)) {}

  std::string GetPropertyAsString(const std::string& tag) {
    return metadata_->StringProperty(tag);
  }
  void SetPropertyAsString(const std::string& tag, const std::string& value) {
    metadata_->StringProperty(tag, value);
  }
  double GetPropertyAsDouble(const std::string& tag) {
    return metadata_->FloatProperty(tag);
  }
  void SetPropertyAsDouble(const std::string& tag, double value) {
    metadata_->FloatProperty(tag, value);
  }
  void SetCommonProperty(const mdf::ETag& tag) {
    metadata_->CommonProperty(tag);
  }
  mdf::ETag GetCommonProperty(const std::string& name) {
    return metadata_->CommonProperty(name);
  }
  void SetCommonProperties(std::vector<mdf::ETag> common_properties) {
    metadata_->CommonProperties(common_properties);
  }
  std::vector<mdf::ETag> GetCommonProperties() const {
    return metadata_->CommonProperties();
  }
  std::vector<mdf::ETag> GetProperties() const {
    return metadata_->Properties();
  }
  std::string GetXmlSnippet() const { return metadata_->XmlSnippet(); }
  void SetXmlSnippet(const std::string& xml) { metadata_->XmlSnippet(xml); }
};
}  // namespace mdflibjs