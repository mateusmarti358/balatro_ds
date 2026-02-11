#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

#include "SpriteData.h"

typedef struct {
    OamState* oam;
    void* gfx;
    SpriteSize size;
    SpriteColorFormat format;
} SpriteFrame;

void initSpriteFrame(SpriteFrame* frame, SpriteData data, OamState* oam);
void deleteSpriteFrame(SpriteFrame* frame);
bool SpriteFrame_valid(SpriteFrame* frame);
