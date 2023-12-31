/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/ichannelobserver.h>

#include <memory>
#include <stdexcept>
#include <string>
// Some of the methods used here are declared in this header.
// This should probably be refactored.
#include <mdf/mdfreader.h>

#include "channel_group_wrapped.h"
#include "channel_wrapped.h"
#include "data_group_wrapped.h"

namespace mdflibjs {
class ChannelObserverWrapped {
 private:
  // This one actually owns the object for a change.
  // It's a shared ptr though since embind requires types be copyable.
  std::shared_ptr<mdf::IChannelObserver> observer_{};

 public:
  ChannelObserverWrapped(mdf::IChannelObserver* observer)
      : observer_(observer) {
    if (observer == nullptr) {
      throw std::runtime_error("ChannelObserverWrapped failed");
    }
  }
  ChannelObserverWrapped(const mdf::IChannelObserver* observer)
      : ChannelObserverWrapped(const_cast<mdf::IChannelObserver*>(observer)) {}
  ChannelObserverWrapped(DataGroupWrapped data_group,
                         ChannelGroupWrapped channel_group,
                         ChannelWrapped channel)
      : observer_((mdf::CreateChannelObserver(*data_group.GetDataGroup(),
                                              *channel_group.GetChannelGroup(),
                                              *channel.GetChannel()))) {}
  ChannelObserverWrapped(DataGroupWrapped data_group,
                         const std::string& channel_name)
      : observer_(mdf::CreateChannelObserver(*data_group.GetDataGroup(),
                                             channel_name)) {}
  int64_t GetNofSamples() const { return observer_->NofSamples(); }
  std::string GetName() const { return observer_->Name(); }
  std::string GetUnit() const { return observer_->Unit(); }
  const ChannelWrapped GetChannel() const {
    return ChannelWrapped(&observer_->Channel());
  }
  bool IsMaster() const { return observer_->IsMaster(); }
  bool HasChannelValueInt64(uint64_t sample) const {
    int64_t value;
    return observer_->GetChannelValue(sample, value);
  }
  bool hasChannelValueUint64(uint64_t sample) const {
    uint64_t value;
    return observer_->GetChannelValue(sample, value);
  }
  bool HasChannelValueDouble(uint64_t sample) const {
    double value;
    return observer_->GetChannelValue(sample, value);
  }
  bool HasChannelValueString(uint64_t sample) const {
    std::string value;
    return observer_->GetChannelValue(sample, value);
  }
  bool HasChannelValueUint8Vector(uint64_t sample) const {
    std::vector<uint8_t> value;
    return observer_->GetChannelValue(sample, value);
  }
  bool HasEngValueUint64(uint64_t sample) const {
    int64_t value;
    return observer_->GetEngValue(sample, value);
  }
  bool HasEngValueInt64(uint64_t sample) const {
    uint64_t value;
    return observer_->GetEngValue(sample, value);
  }
  bool HasEngValueDouble(uint64_t sample) const {
    double value;
    return observer_->GetEngValue(sample, value);
  }
  bool HasEngValueString(uint64_t sample) const {
    std::string value;
    return observer_->GetEngValue(sample, value);
  }
  bool HasEngValueUint8Vector(uint64_t sample) const {
    std::vector<uint8_t> value{};
    // Ref `MdfChannelObserver::GetChannelValueAsArray`
    // "Note that engineering value cannot be byte arrays so I assume"
    // "that it was the observer value that was requested."
    return observer_->GetChannelValue(sample, value);
  }
  int64_t GetChannelValueInt64(uint64_t sample) const {
    int64_t value{};
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetChannelValue failed for int64_t, to avoid this call "
          "HasChannelValue first");
    }
    return value;
  }
  uint64_t GetChannelValueUint64(uint64_t sample) const {
    uint64_t value{};
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetChannelValue failed for uint64_t, to avoid this call "
          "HasChannelValue first");
    }
    return value;
  }
  double GetChannelValueDouble(uint64_t sample) const {
    double value;
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetChannelValue failed for double, to avoid this call "
          "HasChannelValue first");
    }
    return value;
  }

  std::string GetChannelValueString(uint64_t sample) const {
    std::string value;
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetChannelValue failed for std::string, to avoid this call "
          "HasChannelValue first");
    }
    return value;
  }

  std::vector<uint8_t> GetChannelValueUint8Vector(uint64_t sample) const {
    std::vector<uint8_t> value;
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetChannelValue failed for std::vector<uint8_t>, to avoid this call "
          "HasChannelValue first");
    }
    return value;
  }

  int64_t GetEngValueInt64(uint64_t sample) const {
    int64_t value;
    if (!observer_->GetEngValue(sample, value)) {
      throw std::runtime_error(
          "GetEngValue failed for int64_t, to avoid this call HasEngValue "
          "first");
    }
    return value;
  }

  uint64_t GetEngValueUint64(uint64_t sample) const {
    uint64_t value;
    if (!observer_->GetEngValue(sample, value)) {
      throw std::runtime_error(
          "GetEngValue failed for uint64_t, to avoid this call HasEngValue "
          "first");
    }
    return value;
  }

  double GetEngValueDouble(uint64_t sample) const {
    double value;
    if (!observer_->GetEngValue(sample, value)) {
      throw std::runtime_error(
          "GetEngValue failed for double, to avoid this call HasEngValue "
          "first");
    }
    return value;
  }

  std::string GetEngValueString(uint64_t sample) const {
    std::string value;
    if (!observer_->GetEngValue(sample, value)) {
      throw std::runtime_error(
          "GetEngValue failed for std::string, to avoid this call HasEngValue "
          "first");
    }
    return value;
  }

  std::vector<uint8_t> GetEngValueUint8Vector(uint64_t sample) const {
    std::vector<uint8_t> value;
    // Ref `MdfChannelObserver::GetChannelValueAsArray`
    // "Note that engineering value cannot be byte arrays so I assume"
    // "that it was the observer value that was requested."
    if (!observer_->GetChannelValue(sample, value)) {
      throw std::runtime_error(
          "GetEngValue failed for std::vector<uint8_t>, to avoid this call "
          "HasEngValue first");
    }
    return value;
  }
};

std::vector<ChannelObserverWrapped> CreateChannelObserverForChannelGroup(
    DataGroupWrapped data_group, ChannelGroupWrapped channel_group) {
  size_t count = channel_group.GetChannelGroup()->Channels().size();
  if (count <= 0) return {};

  mdf::ChannelObserverList observer_list;
  mdf::CreateChannelObserverForChannelGroup(*data_group.GetDataGroup(),
                                            *channel_group.GetChannelGroup(),
                                            observer_list);

  std::vector<ChannelObserverWrapped> result;
  for (auto& observer : observer_list) {
    result.push_back(ChannelObserverWrapped(observer.release()));
  }
  return result;
};
}  // namespace mdflibjs