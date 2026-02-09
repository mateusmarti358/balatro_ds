#pragma once

#include "core/SpriteSheet"
#include "core/Sprite"

#include "card_data.c"

class CardInstance {
    Sprite m_enhancement;
    Sprite m_seal;
    Sprite m_card;
    Sprite m_bonus;

public:
    CardInstance(SpriteSheet* sheet, card_data_t card) {
        
    }
};