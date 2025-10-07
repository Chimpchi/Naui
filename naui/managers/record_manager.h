#pragma once
#include <stdbool.h>

enum NauiRecordType 
{
    NauiRecordType_None,
    NauiRecordType_Layout,
    NauiRecordType_Panel_Visibility,
    NauiRecordType_Project_Property,
    NauiRecordType_Audio_Graph,
};

void naui_record_mark(NauiRecordType type, const char* subject, const char* before, const char* after);
bool naui_record_is_dirty(void);
void naui_record_clear(void);
int  naui_record_count(void);
NauiRecordType naui_record_type_at(int index);
const char*   naui_record_subject_at(int index);