#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

class SpriteFrame;

u16 getTileSize(SpriteSize size, SpriteColorFormat format);

class SpriteSheet {
    const void* m_source;
    u32 m_size;
    SpriteSize m_sprite_size;
    SpriteColorFormat m_format;

public:
    SpriteSheet(const void* src, u32 size, SpriteSize sprite_size, SpriteColorFormat format);

    int loadFrame(SpriteFrame *frame, OamState* oam, int idx);
};

