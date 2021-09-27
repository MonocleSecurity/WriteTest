cmake_minimum_required(VERSION 3.10)

project(WriteToDisk)

add_library(helper STATIC helper.hpp helper.cpp)

add_executable(ofstream ofstream.cpp)
target_link_libraries(ofstream helper)

add_executable(fopen fopen.cpp)
target_link_libraries(fopen helper)

add_executable(openflags openflags.cpp)
target_link_libraries(openflags helper)

add_executable(open open.cpp)
target_link_libraries(open helper)
