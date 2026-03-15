cmake_minimum_required(VERSION 3.16)

project(AllegICE)
message("CMake version: ${CMAKE_VERSION}")

# Global compiler options
if(MSVC)
    add_compile_options(/W3 /EHsc)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
    
    # Use static CRT to match CMAKE_MFC_FLAG 1 (static MFC linking)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Common include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ICE)

add_subdirectory(ICE)
add_subdirectory(AME)