cmake_minimum_required(VERSION 3.16)

project(AllegICE)
message("CMake version: ${CMAKE_VERSION}")

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Fetch ImGui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking #v1.90.1
)
FetchContent_MakeAvailable(imgui)

# Fetch FreeImage
FetchContent_Declare(
    FreeImage
    GIT_REPOSITORY https://github.com/danoli3/FreeImage.git
    GIT_TAG        3.19.10
)
FetchContent_MakeAvailable(FreeImage)

# --- ImGui target ---
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

# Common include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ICE)

add_subdirectory(ICE)
# add_subdirectory(AME)