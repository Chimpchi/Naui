#pragma once
#include "../panels/panel_manager.h"
#include <vector>
#include <imgui.h>
#include <string>
#include <unordered_map>

typedef void (*NauiShortcutEvent)(NauiShortcut shortcut);

struct NauiShortcut
{
    std::string action;
    std::vector<ImGuiKey> keys;
    NauiShortcutEvent callback;
};

void shortcut_register_global(const char* action, const std::vector<ImGuiKey>& keys);
void shortcut_register_local(NauiPanel* panel, const char* action, const std::vector<ImGuiKey>& keys);

bool shortcut_combo_triggered(const std::vector<int>& keys);

extern std::vector<NauiShortcut> g_shortcuts;