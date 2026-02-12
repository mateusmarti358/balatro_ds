#pragma once

#include <nds/arm9/sprite.h>

typedef struct {
    void *ptr;
    u16 size;
    SpriteSize sprite_size;
    SpriteColorFormat format;
} SpriteData;
