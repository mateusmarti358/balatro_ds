#include "CardSprite.h"

void CardSprite_draw(CardSprite* sprite, int id, int x, int y) {
    if ( sprite->flipped ) {
        Sprite_draw(sprite->back, id, x, y);
    } else {
        Sprite_draw(sprite->enhancer, id, x, y);
        Sprite_draw(sprite->card, id, x, y);
        Sprite_draw(sprite->seal, id, x, y);
        Sprite_draw(sprite->bonus, id, x, y);
    }
}
