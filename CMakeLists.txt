cmake_minimum_required(VERSION 3.26)
project(labwork9_Denis224466)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_subdirectory(lib)
add_subdirectory(bin)
enable_testing()
add_subdirectory(tests)