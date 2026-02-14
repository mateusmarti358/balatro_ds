#include "Sprite.h"

void Sprite_draw(Sprite sprite, DrawingParams params) {
    if (!sprite) return;
    if (!SpriteFrame_valid(sprite)) return;

    oamSet(
        sprite->oam, params.id,
        params.x, params.y,
        params.priority,
        params.palette,
        sprite->size, sprite->format,
        sprite->gfx,
        params.affine,
        params.sizeDouble,
        params.hide,
        params.hflip, params.vflip,
        params.mosaic
    );
}
