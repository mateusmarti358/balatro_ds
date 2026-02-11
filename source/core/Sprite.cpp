#include "Sprite.h"

void Sprite_draw(Sprite* sprite, int id, int x, int y) {
    if (!sprite->frame) return;
    if (!SpriteFrame_valid(sprite->frame)) return;

    oamSet(
        sprite->frame->oam, id,
        x, y,
        0, 0,
        sprite->frame->size, sprite->frame->format,
        sprite->frame->gfx,
        0,
        false, false,
        false, false,
        false
    );
}
