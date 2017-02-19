cmake_minimum_required(VERSION 2.8.7)
project(vulkalc)

macro(use_cxx11)
    if (CMAKE_VERSION VERSION_LESS "3.1")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
         else()
            set (CMAKE_CXX_FLAGS "--std=std++11 ${CMAKE_CXX_FLAGS}")
        endif ()
    else ()
        set (CMAKE_CXX_STANDARD 11)
    endif ()
endmacro(use_cxx11)

use_cxx11()

set(HEADER_FILES include/library.h)
set(SOURCE_FILES source/library.cpp)

add_subdirectory(vulkalc-tests)

add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})