cmake_minimum_required(VERSION 3.19)
project("finedex-sosd" VERSION 1.0
    DESCRIPTION "A header only cmake/c++ library that exposes FINEdex for use in SOSD. See README for more information"
    HOMEPAGE_URL "https://github.com/DominikHorn/FINEdex-sosd"
    LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_sources(${PROJECT_NAME} INTERFACE finedex.hpp include/)

# Add example code only if this repo is not included by a root project via
get_directory_property(hasParent PARENT_DIRECTORY)
if (NOT hasParent)
  add_subdirectory(src)
endif()