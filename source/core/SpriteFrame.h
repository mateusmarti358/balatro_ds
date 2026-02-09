#pragma once

#include <nds/arm9/sprite.h>

#include <nds.h>

class SpriteFrame {
    OamState* m_oam;
    void* m_gfx;
    SpriteSize m_size;
    SpriteColorFormat m_format;

public:
    SpriteFrame();
    ~SpriteFrame();
    int init(
        OamState* oam,
        const void* src,
        u32 sizeBytes,
        SpriteSize size,
        SpriteColorFormat format
    );

    bool valid() const;

    OamState* oam() const;
    void* gfx() const;
    SpriteSize size() const;
    SpriteColorFormat format() const;
};
