# IGCLib is a C++/CLI project
add_library(IGCLib SHARED
    AssemblyInfo.cpp
    IGCProxy.cpp
    Stdafx.cpp
    igclib.h
    IGCProxy.h
    resource.h
    igcstatic.h
    Alleg/constants.h
    Alleg/igc_static_types.h
    Alleg/igc_types.h
    Alleg/mask.h
    Alleg/vector.h
    app.rc
)

# Set to Unicode as per vcxproj
add_definitions(-D_UNICODE -DUNICODE)

# C++/CLI specific flags
if(MSVC)
    target_compile_options(IGCLib PRIVATE /clr)
    set_target_properties(IGCLib PROPERTIES 
        COMMON_LANGUAGE_RUNTIME "" # standard /clr
        LINK_FLAGS "/clr"
        VS_DOTNET_REFERENCES "System;System.Drawing;System.Data;System.Xml"
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
    )
endif()

target_include_directories(IGCLib PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Alleg
)

# Precompiled headers
target_precompile_headers(IGCLib PRIVATE igcstatic.h)
