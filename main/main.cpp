#include "platform/platform.h"
#include "platform/event.h"
#include "platform/event_types.h"

#include <imgui.h>

#include <iostream>
#include <filesystem>

int main(const int argc, const char **argv)
{
    UphPlatformCreateInfo create_info = { 1920, 1080, "Naui" };

    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.IniFilename = nullptr;

    //uph_json_load_theme("themes/Default.json");
    uph_platform_initialize(&create_info);
    //uph_load_layout("layouts/Default");
	//uph_project_init();

	//std::vector<std::filesystem::path> recovery_candidates = uph_project_check_recovery();
	// if(!recovery_candidates.empty())
	// {
	// 	uph_panel_show("Recover Project");
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
    uph_event_connect(UphSystemEventCode::Quit, [&](void *data) { is_running = false; });
    uph_event_connect(UphSystemEventCode::FileDropped, [&](void *data) { });

	//uph_panel_init_all();

    while (is_running)
    {
        uph_platform_begin();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
        //uph_panel_render_all();
        ImGui::Render();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        uph_platform_end();
		//uph_layout_process_requests();
    }

	//uph_project_shutdown();
    uph_platform_shutdown();
    ImGui::DestroyContext();
    return 0;
}