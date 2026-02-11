#include "pool.h"

void pool_init(pool_t* pool, OamState* oam, SpriteSize size, SpriteColorFormat format) {
    pool->oam = oam;
    pool->size = size;
    pool->format = format;

    pool->freed_top = MAX_POOL;
    for (int i = 0; i < MAX_POOL; i++) {
        pool->pool[i] = oamAllocateGfx(pool->oam, pool->size, pool->format);
        pool->freed[i] = i;
    }
}

void* pool_alloc(pool_t* pool, u16 size) {
    u16 idx = pool->freed[--pool->freed_top];
    return pool->pool[idx];
}

void pool_free(pool_t* pool, u16 idx) {
    pool->freed[pool->freed_top++] = idx;
}
