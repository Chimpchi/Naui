#pragma once
#include <filesystem>
#include <stdbool.h>

struct NauiProjectContext 
{
    std::filesystem::path root;
    bool is_scratch;
	bool is_dirty;
};

extern NauiProjectContext g_project_context;

void naui_project_init();
void naui_project_shutdown();

void naui_project_save_as(const std::filesystem::path& dest);
void naui_project_load(const std::filesystem::path& path);
void naui_project_set_dirty(bool dirty);
bool naui_project_is_dirty();
std::vector<std::filesystem::path> naui_project_check_recovery();
void naui_project_load_recovery();
void naui_project_clear_recovery();

inline const std::filesystem::path& naui_project_root() { return g_project_context.root; }