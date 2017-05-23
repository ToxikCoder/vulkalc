project(vulkalc-library)
set (CMAKE_CXX_STANDARD 11)

set(HEADER_FILES include/library.h)
set(SOURCE_FILES library.cpp)
if(${CMAKE_GENERATOR} MATCHES "^Win64$")
    #x86-64 windows generator
    #TODO add include directories and libraries
elseif(${CMAKE_GENERATOR} MATCHES "^Makefiles$")
    #unix generator
    #TODO add include directories and libraries
elseif(${CMAKE_GENERATOR} STREQUAL "Visual Studio 14 2015 Win64")
endif()
if(VULKALC_BUILD_STATIC)
    add_library(vulkalc STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(vulkalc SHARED ${SOURCE_FILES} ${HEADER_FILES})
endif(VULKALC_BUILD_STATIC)
