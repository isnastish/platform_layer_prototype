#ifndef ARENA_H
#include "types.h"

struct Arena
{
    void *at;
    void *storage;
    u64   capacity;
    u64   size;
};

internal Arena arena_init(u64 size);
internal void *arena_alloc(Arena *arena, u64 size, u64 alignment);

#define ARENA_H
#endif //ARENA_H
