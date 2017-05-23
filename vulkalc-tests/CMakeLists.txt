project(vulkalc-tests)
add_executable(vulkalc-test Test.cpp catch.hpp)
target_link_libraries(vulkalc-test vulkalc)