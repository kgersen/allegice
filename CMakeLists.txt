CMAKE_MINIMUM_REQUIRED(VERSION 3.26)

set(ZIG_TARGET x86-windows-gnu)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/zig-toolchain.cmake)

PROJECT(AME)

add_subdirectory(AME)