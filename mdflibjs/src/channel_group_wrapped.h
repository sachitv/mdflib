/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <string>
#include <mdf/ichannelgroup.h>

#include "channel_wrapped.h"
#include "metadata_wrapped.h"
#include "source_information_wrapped.h"

namespace mdflibjs {
class ChannelGroupWrapped {
 private:
  mdf::IChannelGroup* group_{};

 public:
  ChannelGroupWrapped(mdf::IChannelGroup* group) : group_(group) {
    if (group == nullptr) {
      throw std::runtime_error("MdfChannelGroupInit failed");
    }
  }
  ChannelGroupWrapped(const mdf::IChannelGroup* group)
      : ChannelGroupWrapped(const_cast<mdf::IChannelGroup*>(group)) {}
  mdf::IChannelGroup* GetChannelGroup() const { return group_; }
  int64_t GetIndex() const { return group_->Index(); }
  uint64_t GetRecordId() const { return group_->RecordId(); }
  std::string GetName() const { return group_->Name(); }
  void SetName(const std::string& name) { group_->Name(name); }
  std::string GetDescription() const { return group_->Description(); }
  void SetDescription(const std::string& desc) { group_->Description(desc); }
  uint64_t GetNofSamples() const { return group_->NofSamples(); }
  void SetNofSamples(uint64_t samples) { group_->NofSamples(samples); }
  uint16_t GetFlags() const { return group_->Flags(); }
  void SetFlags(uint16_t flags) { return group_->Flags(flags); }
  wchar_t GetPathSeparator() const { return group_->PathSeparator(); }
  void SetPathSeparator(wchar_t sep) { group_->PathSeparator(sep); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(group_->MetaData());
  }
  std::vector<ChannelWrapped> GetChannels() const {
    std::vector<ChannelWrapped> result;
    for (auto& channel : group_->Channels()) {
      result.push_back(ChannelWrapped(channel));
    }
    return result;
  }
  const SourceInformationWrapped GetSourceInformation() const {
    return SourceInformationWrapped(group_->SourceInformation());
  }
  const ChannelWrapped GetXChannel(ChannelWrapped ref_channel) {
    return ChannelWrapped(group_->GetXChannel(*ref_channel.GetChannel()));
  }
  MetadataWrapped CreateMetaData() {
    return MetadataWrapped(group_->CreateMetaData());
  }
  ChannelWrapped CreateChannel() {
    return ChannelWrapped(group_->CreateChannel());
  }
  SourceInformationWrapped CreateSourceInformation() {
    return SourceInformationWrapped(group_->CreateSourceInformation());
  }
};
}  // namespace mdflibjs