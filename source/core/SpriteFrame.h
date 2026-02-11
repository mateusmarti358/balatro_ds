#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

typedef struct {
    OamState* oam;
    void* gfx;
    SpriteSize size;
    SpriteColorFormat format;
} SpriteFrame;

void deleteSpriteFrame(SpriteFrame* frame);
bool SpriteFrame_valid(SpriteFrame* frame);
