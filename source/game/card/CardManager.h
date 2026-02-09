#pragma once

#include "../../core/SpriteSheet.h"

#define ENHANCERS_MAX 26

class CardManager {
private:
    SpriteSheet m_enhancers;
    SpriteFrame m_enhancerFrames[ENHANCERS_MAX];

    SpriteSheet m_seals;
    SpriteFrame m_sealFrames[4];

    SpriteSheet m_cards;
    SpriteFrame m_cardFrames[52];

public:
    CardManager();

    void loadCard(card_data_t card);

    void draw(card_data_t card, int x, int y);
};