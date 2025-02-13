# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_subdirectory(converters)
add_subdirectory(xxhash)
add_subdirectory(cli)

file (GLOB VRS_UTILS_SRCS *.cpp *.h *.hpp)
# Remove fb-only source files (if there is still any lying around)
file(GLOB VRS_UTILS_FB_SRCS *_fb\.cpp *_fb\.h)
if (VRS_UTILS_FB_SRCS)
  list(REMOVE_ITEM VRS_UTILS_SRCS ${VRS_UTILS_FB_SRCS})
endif()

add_library(vrs_utils STATIC ${VRS_UTILS_SRCS})
target_link_libraries(vrs_utils
  PUBLIC
    vrslib
    vrs_helpers
    vrs_utils_converters
    Cereal::Cereal
    Fmt::Fmt
    Jpeg::Jpeg
    Png::Png
)
target_include_directories(vrs_utils PUBLIC ${VRS_SOURCE_DIR})
