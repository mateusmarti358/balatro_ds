#include "SpriteFrame.h"

void initSpriteFrame(SpriteFrame* frame, SpriteData data, OamState* oam) {
    frame->oam = oam;
    frame->gfx = data.gfx;
    frame->size = data.size;
    frame->format = data.format;
}

void deleteSpriteFrame(SpriteFrame* frame) {
    if (frame->gfx)
        oamFreeGfx(frame->oam, frame->gfx);
}

bool SpriteFrame_valid(SpriteFrame* frame) {
    return frame->oam && frame->gfx;
}
