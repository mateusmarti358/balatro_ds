#pragma once
#include <nds/arm9/sprite.h>

#include <nds/arm9/sassert.h>

#include <nds.h>

#include "SpriteFrame.h"

struct Sprite {
    SpriteFrame* frame = NULL;
};

void Sprite_draw(Sprite* sprite, int id, int x, int y);
