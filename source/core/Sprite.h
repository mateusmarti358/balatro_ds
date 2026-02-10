#pragma once
#include <nds/arm9/sprite.h>

#include <nds/arm9/sassert.h>

#include <nds.h>

#include "SpriteFrame.h"

class Sprite {
    SpriteFrame* m_frame;

public:
    Sprite();
    Sprite(SpriteFrame* frame);

    inline void setFrame(SpriteFrame* frame);
    inline SpriteFrame* frame() const;

    void draw(int id, int x, int y);
};
