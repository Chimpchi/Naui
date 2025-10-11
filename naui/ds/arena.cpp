#include "arena.h"
#include <cstdlib>

void naui_create_arena(NauiArena &arena, size_t size)
{
    arena.buffer = (unsigned char*)malloc(size);
    arena.size = size;
    arena.pos = 0;
}

void naui_destroy_arena(NauiArena &arena)
{
    free((void*)arena.buffer);
}

void* naui_arena_alloc(NauiArena &arena, size_t size)
{
    if (arena.pos + size > arena.size)
        return NULL;
    void* ptr = arena.buffer + arena.pos;
    arena.pos += size;
    return ptr;
}

void naui_arena_reset(NauiArena &arena)
{
    arena.pos = 0;
}