cmake_minimum_required(VERSION 2.8.7)
project(vulkalc)

set (CMAKE_CXX_STANDARD 11)

set(HEADER_FILES include/library.h)
set(SOURCE_FILES src/library.cpp)

add_subdirectory(vulkalc-tests)
add_subdirectory(vulkalc-tools)

add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})