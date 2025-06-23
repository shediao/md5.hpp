cmake_minimum_required(VERSION 3.15)
project(
  md5
  VERSION "0.1"
  LANGUAGES CXX)

set("PROJECT_DESCRIPTION"
    "A header-only lightweight C++ command line option parser")
set("PROJECT_HOMEPAGE_URL" "https://github.com/shediao/md5.hpp")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  option(MD5_BUILD_TESTS "Set to ON to build tests" ON)
else()
  option(MD5_BUILD_TESTS "Set to OFF to build tests" OFF)
endif()

add_library(md5 INTERFACE)

target_include_directories(
  md5 INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>)

add_library(md5::md5 ALIAS md5)

if(MD5_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

install(
  TARGETS md5
  EXPORT md5-targets
  INCLUDES
  DESTINATION include)

install(
  DIRECTORY include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp")

install(
  EXPORT md5-targets
  FILE md5-targets.cmake
  NAMESPACE md5::
  DESTINATION lib/cmake/md5)
