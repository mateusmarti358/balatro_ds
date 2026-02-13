#include "pool.h"

void pool_init(pool_t* pool, OamState* oam, SpriteSize size, SpriteColorFormat format) {
    pool->oam = oam;
    pool->count = 0;
    pool->size = size;
    pool->format = format;

    for (int i = 0; i < MAX_POOL; i++) {
        pool->pool[i] = oamAllocateGfx(pool->oam, pool->size, pool->format);
    }
}
void pool_destroy(pool_t* pool) {
    for (int i = 0; i < MAX_POOL; i++) {
        oamFreeGfx(pool->oam, pool->pool[i]);
    }
}

u16 pool_aquire(pool_t* pool) {
    if ( pool->freed_top == 0 ) {
        return pool->count++;
    }

    u16 idx = pool->freed[--pool->freed_top];
    return idx;
}

void pool_release(pool_t* pool, u16 idx) {
    pool->freed[pool->freed_top++] = idx;
}
