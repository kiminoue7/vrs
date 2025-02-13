// Copyright (c) Meta Platforms, Inc. and affiliates.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <map>
#include <string>

#include "ForwardDefinitions.h"
#include "WriteFileHandler.h"

namespace vrs {

class FileHandler;

/// \brief Helper functions to read & write description records.
namespace DescriptionRecord {

/// Description record format version. @internal
enum {
  kLegacyDescriptionFormatVersion = 1, ///< legacy description record format, json based.
  kDescriptionFormatVersion = 2 ///< current description record format.
};

/// Write a description record, including both the record's header and the record's body.
/// @internal
/// @param file: File to write to, at the position where the description record should be written.
/// @param streamTags: Tags for each stream in the file.
/// @param fileTags: Tags for the file.
/// @param outPreviousRecordSize: Reference set to the size of the written description record.
/// @return 0 if all went well, or some file system error.
int writeDescriptionRecord(
    WriteFileHandler& file,
    const std::map<StreamId, const StreamTags*>& streamTags,
    const std::map<std::string, std::string>& fileTags,
    uint32_t& outPreviousRecordSize);

/// Read a description record, including both the record's header and the record's body.
/// @internal
/// @param file: File to read from, at the position where the description record should be read.
/// @param recordHeaderSize: Size of record header.
/// @param outDescriptionRecordSize: Reference to be set to description record's size.
/// @param outStreamTags: Reference to be set to the stream tags.
/// @param outFileTags: Reference to be set to file's tags.
/// @return 0 if all went well, or some file system error.
int readDescriptionRecord(
    FileHandler& file,
    uint32_t recordHeaderSize,
    uint32_t& outDescriptionRecordSize,
    std::map<StreamId, StreamTags>& outStreamTags,
    std::map<std::string, std::string>& outFileTags);

/// Tags may need to be upgraded/cleaned-up.
/// Currently, this process consists simply of making sure the original stream's name saved
/// in VRS tags are stripped of a potential instance number, which used to be included.
/// This clean-up is required for checksums compares to work as expected.
/// @param streamTags: tags of a stream that has been read from disk, and needs to be upgraded.
void upgradeStreamTags(StreamTags& streamTags);

} // namespace DescriptionRecord

} // namespace vrs
