#pragma once

#include "input.h"

struct NauiQuitEvent { };
struct NauiKeyEvent { NauiKey key; };
struct NauiCharEvent { char ch; };
struct NauiFileDropEvent { const char *path; };
struct NauiResizeEvent { uint32_t width; uint32_t height; };