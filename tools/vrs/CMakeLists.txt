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

file(GLOB VRS_UTIL_SRCS *.cpp *.h)
add_executable(vrs ${VRS_UTIL_SRCS})
target_include_directories(vrs
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(vrs
  PUBLIC
    vrslib
    vrs_utils
    vrs_utils_cli
    Fmt::Fmt
    Png::Png
    Jpeg::Jpeg
    vrs_logging
)

if (UNIT_TESTS)
  enable_testing()

  add_executable(test_vrscli
    VrsCommand.cpp
    test/VrsAppTest.cpp
    test/VrsProcess.h
    test/VrsCommandTest.cpp
  )
  target_include_directories(test_vrscli
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/..
  )
  target_link_libraries(test_vrscli
      PUBLIC
        vrs_os
        vrs_test_helpers
        vrs_utils
        vrs_utils_cli
        vrs_oss_testdatadir
        GTest::Main
  )
  add_dependencies(test_vrscli vrs)

  gtest_discover_tests(test_vrscli)
endif()
