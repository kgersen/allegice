cmake_minimum_required(VERSION 3.16)
project(imgui_web)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# --- Fetch ImGui only ---
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        docking
)
FetchContent_MakeAvailable(imgui)

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

# --- Main executable ---
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

# --- Emscripten flags ---
if (EMSCRIPTEN)
    set(EM_FLAGS
        "-sUSE_SDL=3"          # Use the Emscripten SDL3 port
        "-sWASM=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sFULL_ES3=1"
        "-sUSE_WEBGL2=1"
    )

    string(JOIN " " EM_FLAGS_STR ${EM_FLAGS})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        SUFFIX ".html"
        LINK_FLAGS "${EM_FLAGS_STR}"
    )

    # SDL3 port headers need to be available at compile time too
    target_compile_options(${PROJECT_NAME} PRIVATE "-sUSE_SDL=3")
    target_compile_options(imgui PRIVATE "-sUSE_SDL=3")
endif()