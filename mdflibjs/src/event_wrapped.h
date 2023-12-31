/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/ievent.h>

#include <stdexcept>
#include <string>

#include "attachment_wrapped.h"
#include "metadata_wrapped.h"

namespace mdflibjs {
class EventWrapped {
 private:
  mdf::IEvent* event_{};

 public:
  EventWrapped(mdf::IEvent* event) : event_(event) {
    if (event == nullptr) {
      throw std::runtime_error("EventWrapped failed");
    }
  }
  EventWrapped(const mdf::IEvent* event) : EventWrapped(const_cast<mdf::IEvent*>(event)) {}
  int64_t GetIndex() const { return event_->Index(); }
  std::string GetName() const { return event_->Name(); }
  void SetName(const std::string& name) { event_->Name(name); }
  std::string GetDescription() const { return event_->Description(); }
  void SetDescription(const std::string& desc) { event_->Description(desc); }
  std::string GetGroupName() const { return event_->GroupName(); }
  void SetGroupName(const std::string& group) {
    return event_->GroupName(group);
  }
  mdf::EventType GetType() const { return event_->Type(); }
  void SetType(mdf::EventType type) { event_->Type(type); }
  mdf::SyncType GetSync() const { return event_->Sync(); }
  void SetSync(mdf::SyncType type) { event_->Sync(type); }
  mdf::RangeType GetRange() const { return event_->Range(); }
  void SetRange(mdf::RangeType type) { return event_->Range(type); }
  mdf::EventCause GetCause() const { return event_->Cause(); }
  void SetCause(mdf::EventCause cause) { event_->Cause(cause); }
  int64_t GetCreatorIndex() const { return event_->CreatorIndex(); }
  void SetCreatorIndex(int64_t index) { event_->CreatorIndex(index); }
  int64_t GetSyncValue() const { return event_->SyncValue(); }
  void SetSyncValue(int64_t value) { return event_->SyncValue(value); }
  void SetSyncFactor(double factor) { event_->SyncFactor(factor); }
  const EventWrapped GetParentEvent() const {
    return EventWrapped(event_->ParentEvent());
  }
  void SetParentEvent(EventWrapped parent) {
    event_->ParentEvent(parent.GetEvent());
  }
  const EventWrapped GetRangeEvent() const {
    return EventWrapped(event_->RangeEvent());
  }
  void SetRangeEvent(EventWrapped range) {
    event_->RangeEvent(range.GetEvent());
  }
  std::vector<AttachmentWrapped> GetAttachments() const {
    std::vector<AttachmentWrapped> result;
    for (const auto& attachment : event_->Attachments()) {
      result.emplace_back(attachment);
    }
    return result;
  }
  double GetPreTrig() const { return event_->PreTrig(); }
  void SetPreTrig(double time) { event_->PreTrig(time); }
  double GetPostTrig() const { return event_->PostTrig(); }
  void SetPostTrig(double time) { event_->PostTrig(time); }
  const MetadataWrapped GetMetaData() const { return event_->MetaData(); }
  void AddAttachment(const AttachmentWrapped attachment) {
    return event_->AddAttachment(attachment.GetAttachment());
  }

  mdf::IEvent* GetEvent() const { return event_; }
};
}  // namespace mdflibjs