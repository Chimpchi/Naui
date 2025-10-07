#include "project_manager.h"
//#include "project_serializer.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>

#define naui_DIRTY_FOLDER ".dirty"

NauiProjectContext g_project_context = {};

inline std::filesystem::path naui_temp_file_path()
{
	return std::filesystem::temp_directory_path() / "Nauionic";
}

static std::string naui_generate_unique_name() 
{
    auto ts = std::chrono::system_clock::now().time_since_epoch().count();
    return "untitled-" + std::to_string(ts);
}

void naui_project_init() 
{
    auto scratch_base = naui_temp_file_path();
    std::filesystem::create_directories(scratch_base);

    auto unique = naui_generate_unique_name();
    g_project_context.root = scratch_base / unique;
	std::filesystem::path work_dir = g_project_context.root / "workspace";
    std::filesystem::create_directories(g_project_context.root);
    std::filesystem::create_directories(work_dir);
	std::filesystem::create_directories(work_dir / "samples");
	std::filesystem::create_directories(work_dir / "mixers");
	
    g_project_context.is_scratch = true;
	g_project_context.is_dirty = false;
}

void naui_project_shutdown() 
{
    if (!g_project_context.is_scratch)
		return;
        
    std::error_code error_code;
    std::filesystem::remove_all(g_project_context.root, error_code);
}

void naui_project_save_as(const std::filesystem::path& dest) 
{
    std::filesystem::create_directories(dest.parent_path());
    std::filesystem::rename(g_project_context.root, dest);

    g_project_context.root = dest;
    g_project_context.is_scratch = false;
	//naui_project_serializer_save_json(dest, "project-data.json");
}

void naui_project_load(const std::filesystem::path& path) 
{
	if (path.empty()) 
		return;

	//naui_project_serializer_load_json(path);
    g_project_context.root = path;
    g_project_context.is_scratch = false;
}

void naui_project_set_dirty(bool dirty)
{
	if(g_project_context.is_dirty == dirty)
		return;

	auto marker = g_project_context.root / naui_DIRTY_FOLDER;
	g_project_context.is_dirty = dirty;

    if (dirty)
		std::ofstream(marker).close();
    else 
	{
		std::error_code error_code;
        std::filesystem::remove(marker, error_code);	// Possibly set the is dirty flag to false if we can't write the marker folder
    }
	
}

bool naui_project_is_dirty()
{
	return g_project_context.is_dirty;
}

std::vector<std::filesystem::path> naui_project_check_recovery() {
    std::vector<std::filesystem::path> candidates;
    auto scratch_base = naui_temp_file_path();

	if(!std::filesystem::exists(scratch_base))
		return candidates;

	for(auto& entry : std::filesystem::directory_iterator(scratch_base))
	{
		if(!entry.is_directory())
			continue;

		if(std::filesystem::exists(entry.path() / naui_DIRTY_FOLDER))
			candidates.push_back(entry.path());
	}

	return candidates;
}

void naui_project_load_recovery()
{
	auto candidates = naui_project_check_recovery();
	if(candidates.size() <= 0)
		return;

	naui_project_load(candidates[0]);
}

void naui_project_clear_recovery()
{
    try 
	{
        auto candidates = naui_project_check_recovery();
        for (auto& path : candidates) 
		{
            if (std::filesystem::exists(path))
                std::filesystem::remove_all(path);

        }
    } catch (const std::exception& e) 
	{
        std::cerr << "Failed to clear recovery folders: " << e.what() << "\n";
    }
}