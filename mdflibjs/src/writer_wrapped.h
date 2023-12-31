/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/mdffactory.h>
#include <mdf/mdfwriter.h>

#include <memory>
#include <string>

#include "channel_group_wrapped.h"
#include "data_group_wrapped.h"
#include "file_wrapped.h"
#include "header_wrapped.h"

namespace mdflibjs {
class WriterWrapped {
 private:
  // This owns this instance, but we use a shared_ptr since embind requires this
  // to be copy constructible.
  std::shared_ptr<mdf::MdfWriter> writer_{};

 public:
  WriterWrapped(mdf::MdfWriterType type, const std::string& filename)
      : writer_(mdf::MdfFactory::CreateMdfWriterEx(type)) {
    if (writer_ == nullptr) {
      throw std::runtime_error("Writer initialization failed");
    }
    writer_->Init(filename);
  }
  FileWrapped GetFile() const { return FileWrapped(writer_->GetFile()); }
  HeaderWrapped GetHeader() const {
    return HeaderWrapped(writer_->Header());
  }
  bool IsFileNew() const { return writer_->IsFileNew(); }
  bool GetCompressData() const { return writer_->CompressData(); }
  void SetCompressData(bool compress) { writer_->CompressData(compress); }
  double GetPreTrigTime() const { return writer_->PreTrigTime(); }
  void SetPreTrigTime(double pre_trig_time) {
    writer_->PreTrigTime(pre_trig_time);
  }
  uint64_t GetStartTime() const { return writer_->StartTime(); }
  uint64_t GetStopTime() const { return writer_->StopTime(); }
  mdf::MdfBusType GetBusType() const { return writer_->BusType(); }
  void SetBusType(mdf::MdfBusType type) { writer_->BusType(type); }
  mdf::MdfStorageType GetStorageType() const { return writer_->StorageType(); }
  void SetStorageType(mdf::MdfStorageType type) { writer_->StorageType(type); }
  uint32_t GetMaxLength() const { return writer_->MaxLength(); }
  void SetMaxLength(uint32_t length) { writer_->MaxLength(length); }
  DataGroupWrapped CreateDataGroup() {
    return DataGroupWrapped(writer_->CreateDataGroup());
  }
  bool InitMeasurement() { return writer_->InitMeasurement(); }
  void SaveSample(ChannelGroupWrapped group, uint64_t time) {
    writer_->SaveSample(*group.GetChannelGroup(), time);
  }
  void StartMeasurement(uint64_t start_time) {
    writer_->StartMeasurement(start_time);
  }
  void StopMeasurement(uint64_t stop_time) {
    writer_->StopMeasurement(stop_time);
  }
  bool FinalizeMeasurement() { return writer_->FinalizeMeasurement(); }
};
}  // namespace mdflibjs