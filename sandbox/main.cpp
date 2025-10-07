#include "platform/platform.h"
#include "platform/event.h"
#include "platform/event_types.h"

#include <imgui.h>

#include <iostream>
#include <filesystem>

int main(const int argc, const char **argv)
{
    NauiPlatformCreateInfo create_info = { 1920, 1080, "Naui" };

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;

    //naui_json_load_theme("themes/Default.json");
    naui_platform_initialize(&create_info);
    //naui_load_layout("layouts/Default");
	//naui_project_init();

	//std::vector<std::filesystem::path> recovery_candidates = naui_project_check_recovery();
	// if(!recovery_candidates.empty())
	// {
	// 	naui_panel_show("Recover Project");
	// }

    static const ImWchar icon_ranges[]{0xf000, 0xf3ff, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3;
    icons_config.OversampleV = 3;
    io.Fonts->AddFontDefault();
    //ImFont *icon_font = io.Fonts->AddFontFromMemoryCompressedTTF((void*)font_awesome_data, font_awesome_size, 16.0f, &icons_config, icon_ranges);

    bool is_running = true;
    naui_event_connect(NauiSystemEventCode::Quit, [&](void *data) { is_running = false; });
    naui_event_connect(NauiSystemEventCode::FileDropped, [&](void *data) { });

	//naui_panel_init_all();

    while (is_running)
    {
        naui_platform_begin();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
        //naui_panel_render_all();
        ImGui::Render();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        naui_platform_end();
		//naui_layout_process_requests();
    }

	//naui_project_shutdown();
    naui_platform_shutdown();
    ImGui::DestroyContext();
    return 0;
}