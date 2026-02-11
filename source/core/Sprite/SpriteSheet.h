#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

#include "SpriteData.h"

u16 getTileSize(SpriteSize size, SpriteColorFormat format);

typedef struct {
    const void* source;
    SpriteSize sprite_size;
    SpriteColorFormat format;
} SpriteSheet;

SpriteData SpriteSheet_getSpriteData(SpriteSheet* sheet, u32 index);
