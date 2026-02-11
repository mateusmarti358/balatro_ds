#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

#define MAX_POOL 128

typedef struct {
    OamState* oam;

    void* pool[MAX_POOL];

    u16 freed[MAX_POOL/2];
    u16 freed_top;

    SpriteSize size;
    SpriteColorFormat format;
} pool_t;

void pool_init(pool_t* pool, OamState* oam, SpriteSize size, SpriteColorFormat format);
void* pool_alloc(pool_t* pool, u16 size);
void pool_free(pool_t* pool, u16 idx);
