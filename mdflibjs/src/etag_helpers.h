/*
 * Copyright 2023 Simplxs
 * SPDX-License-Identifier: MIT
 */
#pragma once
#include <string>
#include <stdexcept>

#include <mdf/etag.h>

namespace mdflibjs {
using mdf::ETag;

void ETag_SetNumberValue(ETag& tag, const double value) {
    tag.Value(value);
}
double ETag_GetNumberValue(const ETag& tag) {
    return tag.Value<bool>();
}

void ETag_SetBoolValue(ETag& tag, const bool value) {
    tag.Value(value);
}
bool ETag_GetBoolValue(const ETag& tag) {
    return tag.Value<bool>();
}

void ETag_SetStringValue(ETag& tag, const std::string& value) {
    tag.Value(value);
}
std::string ETag_GetStringValue(const ETag& tag) {
    return tag.Value<std::string>();
}
}  // namespace mdflibjs