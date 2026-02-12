#include "Sprite.h"

void Sprite_draw(Sprite sprite, int id, int x, int y) {
    if (!sprite) return;
    if (!SpriteFrame_valid(sprite)) return;

    oamSet(
        sprite->oam, id,
        x, y,
        0, 0,
        sprite->size, sprite->format,
        sprite->gfx,
        0,
        false, false,
        false, false,
        false
    );
}
