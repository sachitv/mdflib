/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <mdf/mdfreader.h>

#include <memory>
#include <string>

#include "data_group_wrapped.h"
#include "file_wrapped.h"
#include "header_wrapped.h"

namespace mdflibjs {
class ReaderWrapped {
 private:
  // This owns this instance, but we use a shared_ptr since embind requires this
  // to be copy constructible.
  std::shared_ptr<mdf::MdfReader> reader_;

 public:
  ReaderWrapped(const std::string& filename)
      : reader_(std::make_shared<mdf::MdfReader>(filename)) {
    if (reader_ == nullptr) {
      throw std::runtime_error("Reader initialization failed");
    }
  }
  int64_t GetIndex() const { return reader_->Index(); }
  bool IsOk() { return reader_->IsOk(); }
  const FileWrapped GetFile() const { return FileWrapped(reader_->GetFile()); }
  HeaderWrapped GetHeader() const {
    return HeaderWrapped(reader_->GetHeader());
  }
  const DataGroupWrapped GetDataGroup(size_t index) {
    return DataGroupWrapped(reader_->GetDataGroup(index));
  }
  bool Open() { return reader_->Open(); }
  void Close() { reader_->Close(); }
  bool ReadHeader() { return reader_->ReadHeader(); }
  bool ReadMeasurementInfo() { return reader_->ReadMeasurementInfo(); }
  bool ReadEverythingButData() { return reader_->ReadEverythingButData(); }
  bool ReadData(DataGroupWrapped group) {
    return reader_->ReadData(*group.GetDataGroup());
  }
};
}  // namespace mdflibjs
