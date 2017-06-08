#
# The MIT License (MIT)
#
# Copyright (c) 2017 Lev Sizov
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

project(vulkalc-tests)
set(CMAKE_CXX_STANDARD 11)

#discovering GPUs
if (WIN32)
    execute_process(COMMAND wmic path win32_VideoController get name
            OUTPUT_VARIABLE GPUS)
    if (${GPUS} MATCHES "Name(.+\n)+")
        message("At least one GPU exists, enabling GPU-dependent tests")
        set(GPU_EXISTS 1)
    endif ()
else ()
    execute_process(COMMAND lspci
            OUTPUT_VARIABLE GPUS)
    if (${GPUS} MATCHES ".*(VGA|3D|2D)+.*")
        message("At least one GPU exists, enabling GPU-dependent tests")
        set(GPU_EXISTS 1)
    endif ()
endif (WIN32)

if (${GPU_EXISTS} EQUAL 1)
    add_definitions("-DGPU_EXISTS")
endif ()

include_directories(../src/include)
if (WIN32)
    include_directories($ENV{VULKAN_SDK}/Include/)
elseif (UNIX)
    include_directories($ENV{VULKAN_SDK}/include/)
endif ()
add_executable(vulkalc-test catch.hpp Test.cpp ApplicationTest.cpp ExceptionsTest.cpp UtilitiesTest.cpp)
target_link_libraries(vulkalc-test vulkalc)