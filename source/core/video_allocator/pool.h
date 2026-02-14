#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

#define MAX_POOL 64

typedef struct {
    OamState* oam;

    void* pool[MAX_POOL];
    u16 count;

    u16 freed[MAX_POOL/2];
    u16 freed_top;

    SpriteSize size;
    SpriteColorFormat format;
} pool_t;

void pool_init(pool_t* pool, OamState* oam, SpriteSize size, SpriteColorFormat format);
void pool_destroy(pool_t* pool);
u16 pool_aquire(pool_t* pool);
void pool_release(pool_t* pool, u16 idx);
