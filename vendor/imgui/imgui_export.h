#pragma once

#if defined(IMGUI_BUILD_DLL)
    #define IMGUI_API __declspec(dllexport)
#elif defined(IMGUI_USE_DLL)
    #define IMGUI_API __declspec(dllimport)
#else
    #define IMGUI_API
#endif