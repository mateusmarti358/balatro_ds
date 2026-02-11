#include "SpriteFrame.h"

void deleteSpriteFrame(SpriteFrame* frame) {
    if (frame->gfx) {
        oamFreeGfx(frame->oam, frame->gfx);
    }
}

bool SpriteFrame_valid(SpriteFrame* frame) {
    return frame->oam && frame->gfx;
}
