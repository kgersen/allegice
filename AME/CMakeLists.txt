set(CMAKE_MFC_FLAG 1)
add_definitions(-D_MBCS)

add_executable(AME WIN32)

target_sources(AME PRIVATE
    AGM.cpp
    stdafx.cpp
    AGM.rc
)

# Add more sources
target_sources(AME PRIVATE
    ../ICE/IGCCore.cpp
    2DMap.cpp
    AlephDlg.cpp
    BaseDlg.cpp
    BitmapGlue.cpp
    BMPMDLButton.cpp
    ColorButton.cpp
    GetNumDlg.cpp
    IGCMap.cpp
    MAPDlg.cpp
    MDLFile.cpp
    RandomDlg.cpp
    RockDlg.cpp
    RocksLayoutDlg.cpp
    RockTpl.cpp
    RockTplDlg.cpp
    SectDlg.cpp
    SectWnd.cpp
)

target_sources(AME PRIVATE
    ../ICE/corestruct.h
    2DMap.h
    AGM.h
    AlephDlg.h
    BaseDlg.h
    BitmapGlue.h
    BMPMDLButton.h
    ColorButton.h
    GetNumDlg.h
    IGCMap.h
    MAPDlg.h
    mapstruct.h
    MDLFile.h
    RandomDlg.h
    resource.h
    RockDlg.h
    RocksLayoutDlg.h
    RockTpl.h
    RockTplDlg.h
    SectDlg.h
    SectWnd.h
    stdafx.h
)

target_include_directories(AME PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../ICE
)

