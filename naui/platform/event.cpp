#include "event.h"

static NauiEvent registered_events[(uint8_t)NauiSystemEventCode_MAX] = { nullptr };

void naui_event_connect(NauiSystemEventCode code, NauiEvent on_event)
{
    registered_events[(uint8_t)code] = on_event;
}

void naui_event_call(NauiSystemEventCode code, void *data)
{
    if (registered_events[(uint8_t)code])
        registered_events[(uint8_t)code](data);
}