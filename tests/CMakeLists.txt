# Copyright (c) 2013-2015, EPFL/Blue Brain Project
#                          Daniel Nachbaur <daniel.nachbaur@epfl.ch>
#
# This file is part of Brion <https://github.com/BlueBrain/Brion>
#
# Change this number when adding tests to force a CMake run: 1

if(NOT BBPTESTDATA_FOUND)
  if(ENABLE_COVERAGE)
    message(FATAL_ERROR "Coverage report generation requires test data")
  endif()
  return()
endif()

configure_file(paths.h.in ${PROJECT_BINARY_DIR}/tests/paths.h)
include_directories(${PROJECT_BINARY_DIR}/tests)

set(TEST_LIBRARIES ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} Brain Brion BBPTestData)
if(LUNCHBOX_USE_SKV)
  common_package(skv REQUIRED)
  include_directories(${SKV_INCLUDE_DIRS})
  list(APPEND TEST_LIBRARIES fxlogger)
endif()
include(CommonCTest)
