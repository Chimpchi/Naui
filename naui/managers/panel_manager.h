#pragma once
#include <imgui.h>
#include <vector>

typedef void (*NauiPanelCallback)(struct NauiPanel* panel);

enum NauiPanelFlags : uint32_t
{
	NauiPanelFlags_None 			    = 0,
	NauiPanelFlags_Panel			    = 1 << 0,
	NauiPanelFlags_MenuBar           = 1 << 1,
	NauiPanelFlags_Popup			    = 1 << 2,
	NauiPanelFlags_Modal             = 1 << 3,
	NauiPanelFlags_HiddenFromMenu    = 1 << 4
};

struct NauiPanel
{
    const char* title;
	const char* category;
    bool is_visible;
	uint32_t panel_flags;
    ImGuiWindowFlags window_flags;
    ImGuiDockNodeFlags dock_flags;
    NauiPanelCallback render_callback;
	NauiPanelCallback init_callback;
};

std::vector<NauiPanel>& panels();

void naui_panel_register(const char* title, NauiPanelFlags panel_flags, NauiPanelCallback render_callback, NauiPanelCallback init_callback);
void naui_panel_init_all();
void naui_panel_render_all();
void naui_panel_show(const char* title, bool visible = true);
NauiPanel* naui_panel_get(const char* title);

// Registers a panel at static initialization time.
#define NAUI_REGISTER_PANEL(TITLE, PANEL_FLAGS, RENDER_FUNC, INIT_FUNC) \
    static void __naui_register_##RENDER_FUNC(void) { \
        naui_panel_register(TITLE, PANEL_FLAGS, RENDER_FUNC, INIT_FUNC); \
    } \
    struct __NauiPanelRegistrar_##RENDER_FUNC { \
        __NauiPanelRegistrar_##RENDER_FUNC() { __naui_register_##RENDER_FUNC(); } \
    }; \
    static __NauiPanelRegistrar_##RENDER_FUNC __naui_panel_registrar_##RENDER_FUNC;