/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/idatagroup.h>

#include <stdexcept>
#include <string>

#include "channel_group_wrapped.h"
#include "channel_wrapped.h"
#include "metadata_wrapped.h"

namespace mdflibjs {
class DataGroupWrapped {
 private:
  mdf::IDataGroup* group_{};

 public:
  DataGroupWrapped(mdf::IDataGroup* group) : group_(group) {
    if (group == nullptr) {
      throw std::runtime_error("DataGroupWrappedInit failed");
    }
  }
  DataGroupWrapped(const mdf::IDataGroup* group)
      : DataGroupWrapped(const_cast<mdf::IDataGroup*>(group)) {}
  mdf::IDataGroup* GetDataGroup() const { return group_; }
  int64_t GetIndex() const { return group_->Index(); }
  std::string GetDescription() const { return group_->Description(); }
  uint8_t GetRecordIdSize() const { return group_->RecordIdSize(); }
  const MetadataWrapped GetMetaData() const {
    return MetadataWrapped(group_->MetaData());
  }
  std::vector<ChannelGroupWrapped> GetChannelGroups() const {
    std::vector<ChannelGroupWrapped> result;
    for (auto& channel_group : group_->ChannelGroups()) {
      result.push_back(ChannelGroupWrapped(channel_group));
    }
    return result;
  }
  bool IsRead() { return group_->IsRead(); }
  MetadataWrapped CreateMetaData() {
    return MetadataWrapped(group_->CreateMetaData());
  }
  ChannelGroupWrapped CreateChannelGroup() {
    return ChannelGroupWrapped(group_->CreateChannelGroup());
  }
  const ChannelGroupWrapped FindParentChannelGroup(ChannelWrapped channel) {
    return ChannelGroupWrapped(
        group_->FindParentChannelGroup(*channel.GetChannel()));
  }
  void ResetSample() {
    // Early exit.
    if (group_ == nullptr) {
      return;
    }

    for (const auto* channel_group : group_->ChannelGroups()) {
      if (channel_group != nullptr) {
        channel_group->ResetSampleCounter();
      }
    }
  }
};
}  // namespace mdflibjs