#include "SpriteFrame.h"

void initSpriteFrame(SpriteFrame* frame, SpriteData data, OamState* oam) {
    frame->oam = oam;
    frame->gfx = NULL;
    frame->size = data.sprite_size;
    frame->format = data.format;
}

void allocateSpriteFrame(SpriteFrame* frame, OamState* oam, SpriteData data) {
    frame->oam = oam;
    frame->gfx = NULL;
    frame->size = data.sprite_size;
    frame->format = data.format;

    frame->gfx = oamAllocateGfx(frame->oam, data.sprite_size, data.format);
    dmaCopy(data.ptr, frame->gfx, data.size);
    frame->size = data.sprite_size;
    frame->format = data.format;
}

void deleteSpriteFrame(SpriteFrame* frame) {
    if (frame->gfx)
        oamFreeGfx(frame->oam, frame->gfx);
}

bool SpriteFrame_valid(SpriteFrame* frame) {
    return frame->oam && frame->gfx;
}
