#include "arena.h"

internal Arena arena_init(u64 size)
{
    // TODO(al): Replace a call to malloc(...) with something like os_state->alloc();
    // But to do that we will need to pass a pointer to the OsState as a parameter to this function
    // or to use global_os_state variable.
    // But, for now we don't have a 
    Arena result = {};
    result.storage  = malloc(size);
    result.size     = size;
    result.capacity = size;
    result.at       = result.storage;
    return(result);
}

internal void *arena_alloc(Arena *arena, u64 size, u64 alignment)
{
    void *chunk = 0;
#if 0
    // TODO(al): Let's pretend that we don't know about the alignment at all!!!
    if(((char *)m_at + size) < ((char *)m_storage + m_capacity))
    {
        m_at   = (void *)((char *)m_at + size);
        m_size = m_size + size;
    }
#endif
    return(chunk);
}
