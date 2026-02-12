#include "CardSprite.h"

void CardSprite_draw(CardSprite* sprite, int id, int x, int y) {
    if ( sprite->flipped ) {
        Sprite_draw(sprite->back, id, x, y);
    } else {
        // TODO!
    }
}
