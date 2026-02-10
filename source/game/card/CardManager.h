#pragma once

#include "../../core/SpriteSheet.h"
#include "../../core/SpriteFrame.h"

#include "card_data.h"

#define ENHANCER_COUNT 26
#define SEAL_COUNT 4
#define CARD_COUNT 52
#define BONUS_COUNT 4

class CardManager {
    OamState* m_oam;

    struct FrameEntry {
        SpriteFrame frame;
        int count = 0;
    };

    SpriteSheet m_enhancers;
    FrameEntry m_enhancerFrames[ENHANCER_COUNT];

    SpriteSheet m_seals;
    FrameEntry m_sealFrames[SEAL_COUNT];

    // SpriteSheet m_bonuses;
    // FrameEntry m_bonusFrames[BONUS_COUNT];

    // SpriteSheet m_cards;
    // SpriteFrame m_cardFrames[CARD_COUNT];

    inline void loadEntry(FrameEntry* frame, int fidx);

    inline void loadEnhancer(u8 enhancer);
    inline void loadPCard(u8 rank, u8 suit);
    inline void loadSeal(seal_t seal);
    inline void loadBonus(u8 bonus);

    inline void unloadEntry(FrameEntry* frame, int fidx);

    inline void unloadEnhancer(u8 enhancer);
    inline void unloadPCard(u8 rank, u8 suit);
    inline void unloadSeal(seal_t seal);
    inline void unloadBonus(u8 bonus);
public:
    CardManager(OamState*);

    void loadCard(card_data_t card);

    void draw(card_data_t card, int id, int x, int y);
};
