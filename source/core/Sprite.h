#pragma once
#include <nds/arm9/sprite.h>

#include <nds/arm9/sassert.h>

#include <nds.h>

#include "SpriteFrame.h"

typedef struct {
    SpriteFrame* frame;
} Sprite;

void Sprite_draw(Sprite* sprite, int id, int x, int y);
