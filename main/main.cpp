#include "platform/platform.h"
#include "platform/event.h"
#include "platform/event_types.h"

#include "theme_loader.h"

#include "asset_manager.h"
#include <panel_manager.h>

#include <iostream>
#include <filesystem>

void render(void)
{
    naui_platform_begin();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport();
    naui_panel_manager_render();
    ImGui::Render();
    naui_platform_end();
}

int main(const int argc, const char **argv)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    style.FramePadding = ImVec2(8.0f, 8.0f);
    style.FrameRounding = 6.0f;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    naui_load_theme_from_json("Themes/Default.json");
    naui_platform_initialize();

    ImFontConfig config;
    config.RasterizerMultiply = 2.0f;
    io.Fonts->AddFontFromFileTTF("Fonts/Nunito.ttf", 18.0f, &config);

    bool is_running = true;
    naui_event_connect(NauiSystemEventCode_Quit, [&](void *data) { is_running = false; });
    naui_event_connect(NauiSystemEventCode_FileDropped, [&](void *data) { });

    naui_asset_manager_initialize();
    naui_panel_manager_initialize();

    naui_register_panel_layer("basic", NauiPanelType_Panel, nullptr, [](NauiPanelInstance &panel) {
        ImGui::Button("Hello World!");
    });

    struct TestPanelData
    {
        int counter = 0;
    };

    naui_register_panel_layer("complex", NauiPanelType_Panel,
    [](NauiPanelInstance &panel) // On Create
    {
        TestPanelData *data = (TestPanelData*)panel.data;
    },
    [](NauiPanelInstance &panel) // On Render
    {
        TestPanelData *data = (TestPanelData*)panel.data;
        ImGui::Text("Counter = %d", data->counter);
        if (ImGui::Button("Add")) data->counter++;
    },
    sizeof(TestPanelData));

    naui_create_panel("basic", "Test");
    naui_create_panel("basic", "Test2");
    naui_create_panel("complex", "Test3");

    while (is_running)
        render();

    naui_panel_manager_shutdown();
    naui_asset_manager_shutdown();

    naui_platform_shutdown();
    ImGui::DestroyContext();
    return 0;
}