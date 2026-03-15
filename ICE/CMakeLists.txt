set(CMAKE_MFC_FLAG 1) # Set to 1 for static linking, 2 for shared linking

# Add definitions for MultiByte character set
add_definitions(-D_MBCS)

set(ICE_SOURCES
    BMPMDLButton.cpp
    ChaffDlg.cpp
    CivDlg.cpp
    ConstantsDlg.cpp
    DevelDlg.cpp
    DroneDlg.cpp
    ICE.cpp
    ICEDlg.cpp
    IGCCore.cpp
    IGCCoreIO.cpp
    MDLView.cpp
    MineDlg.cpp
    MissileDlg.cpp
    PartDlg.cpp
    ProbeDlg.cpp
    ProjectileDlg.cpp
    ShipDlg.cpp
    StationDlg.cpp
    stdafx.cpp
    TreasureDlg.cpp
    VersionApp.cpp
    External/BitmapGlue.cpp
    External/MDLFile.cpp
    ICE.rc
)

set(ICE_HEADERS
    BMPMDLButton.h
    ChaffDlg.h
    CivDlg.h
    ConstantsDlg.h
    corestruct.h
    DevelDlg.h
    DroneDlg.h
    ICE.h
    ICEDlg.h
    MDLView.h
    MineDlg.h
    MissileDlg.h
    PartDlg.h
    ProbeDlg.h
    ProjectileDlg.h
    Resource.h
    ShipDlg.h
    StationDlg.h
    stdafx.h
    TreasureDlg.h
    VersionApp.h
    External/BitmapGlue.h
    External/MDLFile.h
)

add_executable(ICE WIN32 ${ICE_SOURCES} ${ICE_HEADERS})

target_include_directories(ICE PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/External/FreeImage/Dist
)

target_link_libraries(ICE PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/External/FreeImage/Dist/FreeImage.lib
)

# Precompiled headers
target_precompile_headers(ICE PRIVATE stdafx.h)

# Set subsystem to Windows
set_target_properties(ICE PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Copy FreeImage.dll to the output directory
add_custom_command(TARGET ICE POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/External/FreeImage/Dist/FreeImage.dll"
    $<TARGET_FILE_DIR:ICE>
)

add_subdirectory(IGCLib)
