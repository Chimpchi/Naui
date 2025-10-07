workspace "Naui"
    configurations { "Release" }
    startproject "Sandbox"

project "Naui"
    kind "SharedLib"
    language "C++"
	cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}"

    architecture "x64"

    files {
        "naui/**.h",
        "naui/**.cpp",
        "vendor/imgui/**.h",
        "vendor/imgui/**.cpp"
    }

    includedirs {
        "naui",
        "vendor",
        "vendor/imgui",
        "vendor/mINI",
        "vendor/nlohmann"
    }

    defines { "NDEBUG", "IMGUI_BUILD_DLL", "NAUI_EXPORT" }
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

project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}"

    architecture "x64"

    files {
        "sandbox/**.h",
        "sandbox/**.cpp"
    }
    includedirs {
        "naui",
        "vendor",
        "vendor/imgui",
        "vendor/nlohmann"
    }

    links { "Naui" }

    optimize "On"

    filter { "configurations:Release" }
        defines { "NDEBUG" }
