#
# MIT License
#
# Copyright (c) 2017 Lev Sizov a.k.a "ToxikCoder"
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required(VERSION 2.8.7)
project(vulkalc-library)

if (NOT EXISTS "$ENV{VULKAN_SDK}")
    message(FATAL_ERROR "Vulkalc requires Vulkan SDK installed.")
endif (NOT EXISTS "$ENV{VULKAN_SDK}")

#detecting system architecture
enable_language(C)
try_run(run_result_unused
        compile_result_unused
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/detect_arch.c
        COMPILE_OUTPUT_VARIABLE CARCH)
string(REGEX MATCH "cmake_ARCH ([a-zA-Z0-9_]+)" CARCH "${CARCH}")
string(REPLACE "cmake_ARCH " "" CARCH "${CARCH}")
if (${CARCH} STREQUAL "i386")
    set(ARCH_I386 "" INTERNAL)
elseif (${CARCH} STREQUAL "amd64")
    set(ARCH_AMD64 "" INTERNAL)
else ()
    message(WARNING "Failed to detect system architecture")
    set(ARCH_UNKNOWN "" INTERNAL)
endif ()

option(VULKALC_BUILD_VULKALC "Build Vulkalc library" 1)
option(VULKALC_BUILD_STATIC "Static or dynamic library to make" 1)
option(VULKALCTEST_INCLUDE_TESTS "Include Vulkalc tests" 1)
option(VULKALCTOOLS_INCLUDE_TOOLS "Include Vulkalc tools" 1)
option(VULKALCDOC_GENERATE_DOC "Generate documentation" 1)
option(VULKALCDOC_GENERATE_HTML "Generate HTML documentation" 1)
option(VULKALCDOC_GENERATE_PDF "Generate PDF documentation" 0)
option(VULKALCDOC_GENERATE_LATEX "Generate LaTeX documentation" 0)
option(VULKALCDOC_GENERATE_MAN "Generate man pages with documentation" 0)
option(VULKALCDOC_GENERATE_RTF "Generate RTF file with documentation" 0)

enable_language(CXX)

if (VULKALC_BUILD_VULKALC)
    add_subdirectory(src)
endif (VULKALC_BUILD_VULKALC)
if (VULKALCTEST_INCLUDE_TESTS)
    add_subdirectory(vulkalc-tests)
endif (VULKALCTEST_INCLUDE_TESTS)
if (VULKALCTOOLS_INCLUDE_TOOLS)
    add_subdirectory(vulkalc-tools)
endif (VULKALCTOOLS_INCLUDE_TOOLS)
if (VULKALCDOC_GENERATE_DOC)
    add_subdirectory(doc)
endif (VULKALCDOC_GENERATE_DOC)


