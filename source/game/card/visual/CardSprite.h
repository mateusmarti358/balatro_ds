#pragma once

#include "../../../core/Sprite/Sprite.h"

typedef struct {
    Sprite back;
    Sprite enhancer;
    Sprite bonus;
    Sprite card;
    Sprite seal;

    bool flipped;
} CardSprite;

void CardSprite_draw(CardSprite* sprite, int idx, int x, int y);
