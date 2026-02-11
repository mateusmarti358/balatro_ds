#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

struct SpriteFrame {
    OamState* m_oam = NULL;
    void* m_gfx = NULL;
    SpriteSize m_size;
    SpriteColorFormat m_format;
};

void deleteSpriteFrame(SpriteFrame* frame);
bool SpriteFrame_valid(SpriteFrame* frame);
