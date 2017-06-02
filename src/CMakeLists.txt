#
# MIT License
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

project(vulkalc)
set(CMAKE_CXX_STANDARD 11)

#treat all warnings as errors
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
elseif (${CMAKE_GENERATOR} MATCHES "Microsoft")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
endif (CMAKE_COMPILER_IS_GNUCXX)

include_directories($ENV{VULKAN_SDK}/Include/vulkan)

set(SOURCE_FILES Application.cpp VulkanInfo.cpp Configurator.cpp Configuration.cpp Exceptions.cpp)
set(HEADER_FILES include/Application.hpp include/Configurator.hpp include/Export.hpp
        include/InformationProvider.hpp include/RAII.hpp include/Verifier.hpp include/VulkanInfo.hpp
        include/Configuration.hpp include/Utilities.h include/Exceptions.h)

if (ARCH_I386)
    if (WIN32)
        find_library(VULKAN NAMES vulkan-1 PATHS $ENV{VULKAN_SDK}/Lib32)
    elseif (UNIX)
        find_library(VULKAN NAMES vulkan PATHS $ENV{VULKAN_SDK}/lib32)
    endif (WIN32)
elseif (ARCH_AMD64)
    if (WIN32)
        find_library(VULKAN NAMES vulkan-1 PATHS $ENV{VULKAN_SDK}/Lib)
    elseif (UNIX)
        find_library(VULKAN NAMES vulkan PATHS $ENV{VULKAN_SDK}/lib)
    endif (WIN32)
else ()
    message("Attempting to find Vulkan library")
    find_library(VULKAN vulkan)
endif ()

if (VULKALC_BUILD_STATIC)
    add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})
else ()
    add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})
endif (VULKALC_BUILD_STATIC)

target_link_libraries(vulkalc ${VULKAN})
#TODO cmake install build artifacts and shaders