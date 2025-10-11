#include "panel_manager.h"

#include <ds/arena.h>

#include <unordered_map>
#include <vector>
#include <string>
#include <cstring>

struct NauiPanelLayerRegistry
{
    size_t size;
    NauiPanelType type;
    NauiPanelFn create;
    NauiPanelFn render;
};

static std::unordered_map<std::string, NauiPanelLayerRegistry> panel_layers;
static std::vector<NauiPanelInstance> panels;

static NauiArena arena;

void naui_panel_manager_initialize(void)
{
    naui_create_arena(arena, NAUI_MAX_PANEL_SCRATCH_SIZE);
}

void naui_panel_manager_shutdown(void)
{
    naui_destroy_arena(arena);
}

void naui_panel_manager_render(void)
{
    for (NauiPanelInstance &panel : panels)
    {
        if (!panel.is_open)
            continue;
        switch (panel.type)
        {
        case NauiPanelType_Panel:
            ImGui::PushID(panel.type);
            ImGui::SetNextWindowSize(panel.default_size, ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSizeConstraints(panel.min_size, panel.max_size);
            if (ImGui::Begin(panel.title, &panel.is_open, panel.window_flags) && panel.render)
                panel.render(panel);
            ImGui::End();
            ImGui::PopID();
            break;
        case NauiPanelType_Popup:
            ImGui::OpenPopup(panel.title);
            if (ImGui::BeginPopup(panel.title, panel.window_flags) && panel.render)
            {
                panel.render(panel);
                ImGui::EndPopup();
            }
            break;
        case NauiPanelType_Modal:
            ImGui::OpenPopup(panel.title);
            if (ImGui::BeginPopupModal(panel.title, &panel.is_open, panel.window_flags) && panel.render)
            {
                panel.render(panel);
                ImGui::EndPopup();
            }
            break;
        }
    }
}

void naui_register_panel_layer(const char *layer, NauiPanelType type, NauiPanelFn create, NauiPanelFn render, size_t data_size)
{
    panel_layers[layer] = {
        .size = data_size,
        .type = type,
        .create = create,
        .render = render
    };
}

NauiPanelInstance &naui_create_panel(const char *layer, const char *title)
{
    const NauiPanelLayerRegistry &const panel_layer = panel_layers[layer];
    NauiPanelInstance panel = {
        .type = panel_layer.type,
        .title = title,
        .layer = layer,
        .create = panel_layer.create,
        .render = panel_layer.render
    };
    if (panel_layer.size != 0)
    {
        panel.data = (void*)naui_arena_alloc(arena, panel_layer.size);
        memset(panel.data, 0, panel_layer.size);
    }
    if (panel_layer.create)
        panel_layer.create(panel);
    panels.push_back(panel);
    return panel;
}

NauiPanelInstance &naui_get_first_panel_of_layer(const char *layer)
{
    for (NauiPanelInstance &panel : panels)
        if (strcmp(panel.layer, layer) == 0)
            return panel;
}

std::vector<NauiPanelInstance*> &naui_get_all_panels_of_layer(const char *layer)
{
    static std::vector<NauiPanelInstance*> result;
    result.clear();
    for (NauiPanelInstance &panel : panels)
        if (strcmp(panel.layer, layer) == 0)
            result.push_back(&panel);
    return result;
}