#pragma once

#include <nds/arm9/sprite.h>

typedef struct {
    void *ptr;
    void *gfx;
    SpriteSize size;
    SpriteColorFormat format;
} SpriteData;