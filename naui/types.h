#pragma once
#include <cstdint>

struct WindowHandle{ uint64_t id; };
struct NauiPanelHanle{ uint64_t id; };
struct NauiDataHandle { uint64_t id; };

typedef uint16_t NauiPanelType;
enum NauiPanelType
{
	NauiPanelType_Panel		= 0,
	NauiPanelType_MenuBar	= 1 << 0,
	NauiPanelType_Popup		= 1 << 1,
	NauiPanelType_Modal		= 1 << 2,
	NauiPanelType_ToolTip	= 1 << 3,
	NauiPanelType_Viewport	= 1 << 4
};

typedef uint32_t NauiPanelFlags;
enum NauiPanelFlags
{
	NauiPanelFlags_None					= 0,
	NauiPanelFlags_Dockable				= 1 << 0,	// can be docked in containers
	NauiPanelFlags_Floating				= 1 << 1,	// can be moved within window
	NauiPanelFlags_Resizeable			= 1 << 2,
	NauiPanelFlags_Closeable			= 1 << 3,
	NauiPanelFlags_NoDecoration			= 1 << 4,
	NauiPanelFlags_Focusable			= 1 << 5,
	NauiPanelFlags_Sticky				= 1 << 6,	// persists across layout changes
	NauiPanelFlags_Anchored				= 1 << 7,	// positioned relative to a target rect
	NauiPanelFlags_NoSavedSettings		= 1 << 8,
	NauiPanelFlags_CrossWindowDocking	= 1 << 9,
	NauiPanelFlags_NoScroll				= 1 << 10,
	NauiPanelFlags_NoCollapse			= 1 << 11,
	NauiPanelFlags_NoBackground			= 1 << 12,
	NauiPanelFlags_HorizontalScrollbar	= 1 << 13,
	NauiPanelFlags_VerticalScrollbar	= 1 << 14
};

struct NauiPanelContext
{
	WindowHandle window;
	NauiPanelHanle panel;
	NauiDataHandle data;
	NauiPanelType type;
	NauiPanelFlags flags;
	const char* identity;
	const char* title;
	int x, y;
	int width, height;
	bool initialized;
};

struct NauiPanelVTable
{
	void (*on_init)(NauiPanelContext* ctx);
	void (*on_before_render)(NauiPanelContext* ctx);
	void (*on_render)(NauiPanelContext* ctx);
	void (*on_destroy)(NauiPanelContext* ctx);
};