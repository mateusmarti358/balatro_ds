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

    void setFrame(SpriteFrame* frame);
    SpriteFrame* frame() const;

    void draw(int id, int x, int y);
};
