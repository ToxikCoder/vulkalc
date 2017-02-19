cmake_minimum_required(VERSION 3.6)
project(vulkalc)

add_definitions(-std=c++11)

set(HEADER_FILES include/library.h)
set(SOURCE_FILES source/library.cpp)

add_subdirectory(vulkalc-tests)

add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})