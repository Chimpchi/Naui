#pragma once

#include "base.h"

#include <functional>

typedef std::function<void(void *data)> NauiEvent;

enum class NauiSystemEventCode : uint8_t
{
    Quit,
    KeyPressed,
    KeyReleased,
    Char,
    FileDropped,
    MAX
};

void naui_event_connect(const NauiSystemEventCode code, NauiEvent on_event);
void naui_event_call(const NauiSystemEventCode code, void *data);