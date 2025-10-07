#pragma once
#include <string>
#include <vector>

void naui_save_layout(const char* name);
bool naui_load_layout(const char* name);
bool naui_remove_layout(const char* name);
bool naui_layout_has_header(const char* name, const char* header);
bool naui_layout_is_immutable(const char* name);
std::vector<std::string> naui_list_layouts(const char* filename);

void naui_layout_request_save(const char* name);
void naui_layout_request_load(const char* name);
void naui_layout_clear_requests();
void naui_layout_process_requests();