#pragma once
#include <nds/arm9/sprite.h>

#include <nds/arm9/sassert.h>

#include <nds.h>

#include "SpriteFrame.h"

typedef SpriteFrame* Sprite;

typedef struct {
    int id;
    int x, y;
    int priority;
    int palette;
    int affine;
    bool sizeDouble;
    bool hide;
    bool hflip, vflip;
    bool mosaic;
} DrawingParams;

void Sprite_draw(Sprite sprite, DrawingParams params);
