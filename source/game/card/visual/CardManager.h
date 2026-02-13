#pragma once

#include "../../../core/Sprite/SpriteSheet.h"
#include "../../../core/Sprite/SpriteFrame.h"
#include "../../../core/video_allocator/pool.h"

#include "../logic/card_data.h"

#include "CardSprite.h"

#define ENHANCER_COUNT 26
#define SEAL_COUNT 4
#define CARD_COUNT 52
#define BONUS_COUNT 4

class CardManager {
    pool_t* m_pool;

    struct FrameEntry {
        SpriteFrame frame;
        u16 pool_idx;
        u16 count = 0;
    };

    SpriteFrame m_backFrame;
    u16 m_back_poolidx;

    SpriteSheet m_enhancers;
    FrameEntry m_enhancerFrames[ENHANCER_COUNT];

    SpriteFrame m_sealsFrames[SEAL_COUNT];

    SpriteSheet m_bonuses;
    FrameEntry m_bonusFrames[BONUS_COUNT];

    // SpriteSheet m_cards;
    // SpriteFrame m_cardFrames[CARD_COUNT];

    inline void loadEntry(FrameEntry* frame, SpriteSheet* sheet, int fidx);

    inline void loadEnhancer(u8 enhancer);
    inline void loadPCard(u8 rank, u8 suit);
    inline void loadBonus(u8 bonus);

    inline void unloadEntry(FrameEntry* frame);

    inline void unloadEnhancer(u8 enhancer);
    inline void unloadPCard(u8 rank, u8 suit);
    inline void unloadBonus(u8 bonus);

public:
    CardManager(pool_t* pool, u16 back);
    ~CardManager();

    CardSprite loadCard(card_data_t card);
    void unloadCard(card_data_t card);
};
