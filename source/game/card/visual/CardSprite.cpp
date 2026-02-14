#include "CardSprite.h"

void CardSprite_draw(CardSprite* sprite, DrawingParams params) {
    if ( sprite->flipped ) {
        Sprite_draw(sprite->back, params);
    } else {
        params.palette = 0;

        if ( sprite->seal )
            Sprite_draw(sprite->seal, params);
        
        params.id++;
        
        params.palette = 2;
        
        Sprite_draw(sprite->card, params);
        
        params.id++;
        
        if ( sprite->bonus )
            Sprite_draw(sprite->bonus, params);
        
        params.palette = 1;
            
        params.id++;
        Sprite_draw(sprite->enhancer, params);
    }
}
