#pragma once

#include "../../../core/Sprite/Sprite.h"

typedef struct {
    Sprite back;
    Sprite enhancer;
    Sprite card;
    Sprite seal;
    Sprite bonus;

    bool flipped;
} CardSprite;

void CardSprite_draw(CardSprite* sprite, int idx, int x, int y);
