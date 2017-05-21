set(HEADER_FILES include/ include/device_info.h)
set(SOURCE_FILES src/ src/device_info.cpp)

add_executable(vulkalc-tools ${SOURCE_FILES} ${HEADER_FILES})