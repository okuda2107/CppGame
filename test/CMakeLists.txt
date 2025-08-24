# temp

cmake_minimum_required(VERSION 3.14)

project(test)

add_subdirectory("${CMAKE_SOURCE_DIR}/../exlibs/googletest-1.17.0" "${CMAKE_SOURCE_DIR}/../exlibs/googletest-1.17.0/build")

enable_testing()

add_executable(myTest test.cpp)

target_link_libraries(myTest GTest::gtest_main)

include(GoogleTest)

gtest_discover_tests(myTest)
