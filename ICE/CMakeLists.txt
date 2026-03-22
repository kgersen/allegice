# Add definitions for MultiByte character set
add_definitions(-D_MBCS)
project(ICE)

set(ICE_SOURCES
#    BMPMDLButton.cpp
#    ChaffDlg.cpp
#    CivDlg.cpp
#    ConstantsDlg.cpp
#    DevelDlg.cpp
#    DroneDlg.cpp
    ICE.cpp
    ICEDlg.cpp
    IGCCore.cpp
    IGCCoreIO.cpp
    MDLView.cpp
#    MineDlg.cpp
#    MissileDlg.cpp
#    PartDlg.cpp
#    ProbeDlg.cpp
#    ProjectileDlg.cpp
#    ShipDlg.cpp
#    StationDlg.cpp
    stdafx.cpp
#    TreasureDlg.cpp
#    VersionApp.cpp
    External/BitmapGlue.cpp
    External/MDLFile.cpp
    ICE.rc
)

set(ICE_HEADERS
#    BMPMDLButton.h
#    ChaffDlg.h
#    CivDlg.h
#    ConstantsDlg.h
    corestruct.h
#    DevelDlg.h
#    DroneDlg.h
    ICE.h
    ICEDlg.h
    MDLView.h
#    MineDlg.h
#    MissileDlg.h
#    PartDlg.h
#    ProbeDlg.h
#    ProjectileDlg.h
    Resource.h
#    ShipDlg.h
#    StationDlg.h
    stdafx.h
#    TreasureDlg.h
#    VersionApp.h
    External/BitmapGlue.h
    External/MDLFile.h
)

add_executable(${PROJECT_NAME}  ${ICE_SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/IGCLib
    ${CMAKE_CURRENT_SOURCE_DIR}/External/FreeImage/Dist
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(${PROJECT_NAME} PRIVATE IGCLib)
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

