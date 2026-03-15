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

include(FetchContent)

# Fetch GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.90.1
)
FetchContent_Populate(imgui)

# Common include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ICE)

add_subdirectory(ICE)
# add_subdirectory(AME)