/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/iheader.h>

#include <stdexcept>
#include <string>

#include "attachment_wrapped.h"
#include "data_group_wrapped.h"
#include "event_wrapped.h"
#include "file_history_wrapped.h"
#include "metadata_wrapped.h"

namespace mdflibjs {
class HeaderWrapped {
 private:
  mdf::IHeader* header_;

 public:
  HeaderWrapped(mdf::IHeader* header) : header_(header) {
    if (header == nullptr) {
      throw std::runtime_error("MdfHeaderInit failed");
    }
  }
  HeaderWrapped(const mdf::IHeader* header)
      : HeaderWrapped(const_cast<mdf::IHeader*>(header)) {}
  int64_t GetIndex() const { return header_->Index(); }
  std::string GetDescription() const { return header_->Description(); }
  void SetDescription(const std::string& desc) { header_->Description(desc); }
  std::string GetAuthor() const { return header_->Author(); }
  void SetAuthor(const std::string& author) { header_->Author(author); }
  std::string GetDepartment() const { return header_->Department(); }
  void SetDepartment(const std::string& department) {
    header_->Department(department);
  }
  std::string GetProject() const { return header_->Project(); }
  void SetProject(const std::string& project) { header_->Project(project); }
  std::string GetSubject() const { return header_->Subject(); }
  void SetSubject(const std::string& subject) { header_->Subject(subject); }
  std::string GetMeasurementId() const { return header_->MeasurementId(); }
  void SetMeasurementId(const std::string& uuid) {
    header_->MeasurementId(uuid);
  }
  std::string GetRecorderId() const { return header_->RecorderId(); }
  void SetRecorderId(const std::string& uuid) { header_->RecorderId(uuid); }
  int64_t GetRecorderIndex() const { return header_->RecorderIndex(); }
  void SetRecorderIndex(int64_t index) { header_->RecorderIndex(index); }
  uint64_t GetStartTime() const { return header_->StartTime(); }
  void SetStartTime(uint64_t time) { header_->StartTime(time); }
  bool IsStartAngleUsed() { return header_->StartAngle().has_value(); }
  double GetStartAngle() const { return header_->StartAngle().value_or(0.0); }
  void SetStartAngle(double angle) { header_->StartAngle(angle); }
  bool IsStartDistanceUsed() { return header_->StartDistance().has_value(); }
  double GetStartDistance() const {
    return header_->StartDistance().value_or(0.0);
  }
  void SetStartDistance(double distance) { header_->StartDistance(distance); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(header_->MetaData());
  }
  std::vector<AttachmentWrapped> GetAttachments() const {
    std::vector<AttachmentWrapped> result;
    for (auto& attachment : header_->Attachments()) {
      result.emplace_back(AttachmentWrapped(attachment));
    }
    return result;
  }
  std::vector<FileHistoryWrapped> GetFileHistorys() const {
    std::vector<FileHistoryWrapped> result;
    for (auto& history : header_->FileHistories()) {
      result.emplace_back(FileHistoryWrapped(history));
    }
    return result;
  }
  std::vector<EventWrapped> GetEvents() const {
    std::vector<EventWrapped> result;
    for (auto& event : header_->Events()) {
      result.emplace_back(EventWrapped(event));
    }
    return result;
  }
  std::vector<DataGroupWrapped> GetDataGroups() const {
    std::vector<DataGroupWrapped> result;
    for (auto& group : header_->DataGroups()) {
      result.emplace_back(DataGroupWrapped(group));
    }
    return result;
  }
  AttachmentWrapped CreateAttachment() {
    return AttachmentWrapped(header_->CreateAttachment());
  }
  FileHistoryWrapped CreateFileHistory() {
    return FileHistoryWrapped(header_->CreateFileHistory());
  }
  EventWrapped CreateEvent() { return EventWrapped(header_->CreateEvent()); }
  DataGroupWrapped CreateDataGroup() {
    return DataGroupWrapped(header_->CreateDataGroup());
  }
};
}  // namespace mdflibjs