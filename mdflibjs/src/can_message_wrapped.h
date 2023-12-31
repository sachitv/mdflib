/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <stdexcept>
#include <vector>

#include <mdf/canmessage.h>

namespace mdflibjs {
class CanMessageWrapped {
 private:
  mdf::CanMessage* const can_{};

 public:
  CanMessageWrapped(mdf::CanMessage* can) : can_(can) {
    if (can == nullptr) {
      throw std::runtime_error("CanMessageWrapped failed");
    }
  }

  uint32_t GetMessageId() const { return can_->MessageId(); };
  void SetMessageId(uint32_t message_id) { can_->MessageId(message_id); };
  uint32_t GetCanId() const { return can_->CanId(); };
  void SetExtendedId(bool extended_id) {
    can_->ExtendedId(extended_id);
  };
  bool GetExtendedId() const { return can_->ExtendedId(); };
  uint8_t GetDlc() const { return can_->Dlc(); };
  void SetDlc(uint8_t dlc) { can_->Dlc(dlc); };
  uint32_t GetDataLength() const { return can_->DataLength(); };
  void SetDataLength(uint32_t data_length) {
    can_->DataLength(data_length);
  };
  std::vector<uint8_t> GetDataBytes() const {
    return can_->DataBytes();
  };
  void SetDataBytes(std::vector<uint8_t> data_bytes) {
    can_->DataBytes(data_bytes);
  };
  uint64_t GetDataIndex() const { return can_->DataIndex(); };
  void SetDataIndex(const uint64_t index) {
    can_->DataIndex(index);
  };
  bool GetDir() const { return can_->Dir(); };
  void SetDir(const bool transmit) { can_->Dir(transmit); };
  bool GetSrr() const { return can_->Srr(); };
  void SetSrr(const bool srr) { can_->Srr(srr); };
  bool GetEdl() const { return can_->Edl(); };
  void SetEdl(const bool edl) { can_->Edl(edl); };
  bool GetBrs() const { return can_->Brs(); };
  void SetBrs(const bool brs) { can_->Brs(brs); };
  bool GetEsi() const { return can_->Esi(); };
  void SetEsi(const bool esi) { can_->Esi(esi); };
  bool GetRtr() const { return can_->Rtr(); };
  void SetRtr(const bool rtr) { can_->Rtr(rtr); };
  bool GetWakeUp() const { return can_->WakeUp(); };
  void SetWakeUp(const bool wake_up) { can_->WakeUp(wake_up); };
  bool GetSingleWire() const { return can_->SingleWire(); };
  void SetSingleWire(const bool single_wire) {
    can_->SingleWire(single_wire);
  };
  uint8_t GetBusChannel() const { return can_->BusChannel(); };
  void SetBusChannel(const uint8_t channel) {
    can_->BusChannel(channel);
  };
  uint8_t GetBitPosition() const { return can_->BitPosition(); };
  void SetBitPosition(const uint8_t position) {
    can_->BitPosition(position);
  };
  mdf::CanErrorType GetErrorType() const { return can_->ErrorType(); };
  void SetErrorType(const mdf::CanErrorType error_type) {
    can_->ErrorType(error_type);
  };
  void Reset() {
    can_->Reset();
  }
};
}  // namespace mdflibjs
