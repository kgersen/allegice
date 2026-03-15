#include "stdafx.h"
#include "ICEDlg.h"
#include "imgui.h"

CICEDlg::CICEDlg()
{
    sTitle = "AllegICE (ImGui)";
    sVersion = "1.0";
    pigccore = nullptr;
}

CICEDlg::~CICEDlg()
{
    if (pigccore) {
        delete pigccore;
    }
}

void CICEDlg::LoadCore(const char* filepath)
{
    if (pigccore) {
        delete pigccore;
        pigccore = nullptr;
    }

    pigccore = new CIGCCore;
    if (pigccore->ReadFromFile(filepath)) {
        sCorename = filepath;
        sCorepath = filepath;
    } else {
        delete pigccore;
        pigccore = nullptr;
    }
}

void CICEDlg::SaveCore(const char* filepath)
{
    if (pigccore) {
        pigccore->SaveToFile(filepath);
    }
}

void CICEDlg::RenderImGui()
{
    ImGui::Begin("Main UI");

    ImGui::Text("AllegICE Core Editor");
    ImGui::Separator();

    static char corePathBuffer[512] = "";
    ImGui::InputText("Core File", corePathBuffer, sizeof(corePathBuffer));

    if (ImGui::Button("Load Core")) {
        LoadCore(corePathBuffer);
    }

    if (pigccore) {
        ImGui::TextColored(ImVec4(0,1,0,1), "Core loaded: %s", (const char*)sCorename);
        
        if (ImGui::Button("Save Core")) {
            SaveCore(corePathBuffer);
        }
    } else {
        ImGui::TextColored(ImVec4(1,0,0,1), "No core loaded.");
    }

    ImGui::End();
}
