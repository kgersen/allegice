#pragma once

#include "stdafx.h"
#include "corestruct.h"
#include "IGCCore.h"

// Forward declare ImGui types so we don't need to include imgui.h everywhere if possible
namespace ImGui { }

class CICEDlg
{
public:
    CICEDlg();
    ~CICEDlg();

    void RenderImGui();

private:
    void LoadCore(const char* filepath);
    void SaveCore(const char* filepath);

    CString sVersion;
    CString sTitle;
    CString cArtPath;
    CString sCorename;
    CString sCorepath;

    PtrCore pigccore;
};
