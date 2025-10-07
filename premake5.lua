workspace "Naui"
    configurations { "Release" }
    startproject "Naui"

project "UVI"
    kind "StaticLib"
    architecture "x64"
    language "C++"
    cppdialect "C++20"
    files {
        "uvi/**.h",
        "uvi/**.cpp"
    }
    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

project "Naui"
    kind "ConsoleApp"
    architecture "x64"
    language "C++"
	cppdialect "C++20"
    files {
        "main/**.h",
        "main/**.cpp",
        "vendor/imgui/**.h",
        "vendor/imgui/**.cpp"
    }

    includedirs {
        "main",
        "uvi",
        "vendor",
        "vendor/imgui",
        "vendor/mINI",
        "vendor/nlohmann"
    }

    filter { "configurations:Release" }
        defines { "NDEBUG" }
        optimize "On"

    filter "system:windows"
        removefiles {
            "vendor/imgui/imgui_impl_sdl2.cpp",
            "vendor/imgui/imgui_impl_sdl2.h",
            "vendor/imgui/imgui_impl_opengl3_loader.cpp",
            "vendor/imgui/imgui_impl_opengl3.h",
            "vendor/imgui/imgui_impl_opengl3.cpp"
        }

    filter "system:linux"
        removefiles {
            "vendor/imgui/imgui_impl_win32.cpp",
            "vendor/imgui/imgui_impl_win32.h",
            "vendor/imgui/imgui_impl_dx11.cpp",
            "vendor/imgui/imgui_impl_dx11.h"
        }
        links { "SDL2", "GL", "dl", "m" }