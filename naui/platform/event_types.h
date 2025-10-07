#pragma once

#include "input.h"

struct NauiQuitEvent { };
struct NauiKeyEvent { NauiKey key; };
struct NauiCharEvent { char ch; };
struct NauiFileDropEvent { const char *path; };