#pragma once

#include <filesystem>
#include "base.h"

typedef void *NauiLibrary;
typedef void *NauiProcAddress;

struct NauiPlatformCreateInfo
{
    uint32_t width, height;
    const char *title;
};

struct NauiChildWindowCreateInfo
{
    uint32_t width, height;
    const char *title;
};

struct NauiChildWindow
{
    void *handle;
};

NAUI_API void naui_platform_initialize(const NauiPlatformCreateInfo *create_info);
NAUI_API void naui_platform_shutdown(void);

NAUI_API void naui_platform_begin(void);
NAUI_API void naui_platform_end(void);

NAUI_API NauiChildWindow naui_create_child_window(const NauiChildWindowCreateInfo *create_info);
NAUI_API void naui_destroy_child_window(const NauiChildWindow *window);

NAUI_API double naui_get_time(void);

NAUI_API NauiLibrary naui_load_library(const char *path);
NAUI_API void naui_unload_library(NauiLibrary library);
NAUI_API NauiProcAddress naui_get_proc_address(NauiLibrary library, const char *name);
NAUI_API std::filesystem::path naui_open_file_dialog(const wchar_t* filter, const wchar_t* title);
NAUI_API std::filesystem::path naui_save_file_dialog(const wchar_t* filter, const wchar_t* title);