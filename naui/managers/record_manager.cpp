#include "record_manager.h"
#include "project_manager.h"
#include <vector>
#include <string>

struct NauiRecordEvent 
{
    NauiRecordType type;
    const char* subject;
    const char* before;
    const char* after;
};

static std::vector<NauiRecordEvent> g_events;

void naui_record_mark(NauiRecordType type, const char* subject, const char* before, const char* after) 
{
    naui_project_set_dirty(true);
    NauiRecordEvent evt;
    evt.type    = type;
    evt.subject = subject ? subject : "";
    evt.before  = before  ? before  : "";
    evt.after   = after   ? after   : "";

    g_events.push_back(std::move(evt));

}

bool naui_record_is_dirty(void) 
{
    return naui_project_is_dirty();
}

void naui_record_clear(void) 
{
    naui_project_set_dirty(false);
    g_events.clear();
}

int naui_record_count(void) 
{
    return (int) g_events.size();
}

NauiRecordType naui_record_type_at(int index) 
{
    if (index < 0 || index >= (int) g_events.size())
        return NauiRecordType_None;

    return g_events[index].type;
}

const char* naui_record_subject_at(int index) 
{
    if (index < 0 || index >= (int) g_events.size())
        return "";

    return g_events[index].subject;
}