#include "CardManager.h"

#include "enhancer.h"
#include <seal_sprs.h>

int enhancementToIdx(u8 enhancement) {
    switch (enhancement) {
        case NOT_ENHANCED: return (int)EnhancerSpriteIndex::Normal;
        case GOLD_ENHANCEMENT: return (int)EnhancerSpriteIndex::Gold;
        case LUCKY_ENHANCEMENT: return (int)EnhancerSpriteIndex::Lucky;
        case GLASS_ENHANCEMENT: return (int)EnhancerSpriteIndex::Glass;
        case STEEL_ENHANCEMENT: return (int)EnhancerSpriteIndex::Steel;
    }
    return 0;
}
int bonusToIdx(u8 bonus) {
    switch (bonus) {
        case BONUS_CHIPS: return (int)EnhancerSpriteIndex::Bonus;
        case BONUS_MULT: return (int)EnhancerSpriteIndex::Mult;
        case BONUS_WILD: return (int)EnhancerSpriteIndex::Wild;
    }
    return 0;
}

CardManager::CardManager(pool_t *pool, u16 back) : m_pool(pool) {
    SpriteSheet_init(&m_enhancers, enhancer_sprsTiles, SpriteSize_32x32, SpriteColorFormat_256Color);

    void* back_sprite_addr = SpriteSheet_getSpriteData(&m_enhancers, back).ptr;
    m_backFrame = { pool->oam, NULL, SpriteSize_32x32, SpriteColorFormat_256Color };
    m_backFrame.gfx = pool_aquire(pool, m_backFrame.size);
    dmaCopy(back_sprite_addr, m_backFrame.gfx, 32*32);

    SpriteSheet seals_sprsheet;
    SpriteSheet_init(&seals_sprsheet, seal_sprsTiles, SpriteSize_8x8, SpriteColorFormat_16Color);

    for ( int i = 0; i < SEAL_COUNT; i++ ) {
        void* seal_sprite_addr = SpriteSheet_getSpriteData(&seals_sprsheet, i).ptr;
        m_sealsFrames[i] = { pool->oam, NULL, SpriteSize_8x8, SpriteColorFormat_16Color };
        m_sealsFrames[i].gfx = oamAllocateGfx(pool->oam, m_sealsFrames[i].size, m_sealsFrames[i].format);
        dmaCopy(seal_sprite_addr, m_sealsFrames[i].gfx, (8*8)/2);
    }
}
CardManager::~CardManager() {

}

#pragma region load

void CardManager::loadEntry(FrameEntry* frame, SpriteSheet* sheet, int fidx) {
    if ( frame->count != 0 ) {
        frame->count++;
        return;
    }

    SpriteData data = SpriteSheet_getSpriteData(sheet, fidx);
    SpriteFrame frameData;
    initSpriteFrame(&frameData, data, m_pool->oam);
    frame->frame = frameData;

    void* gfx = pool_aquire(m_pool, data.size);
    dmaCopy(data.ptr, gfx, data.size);

    frame->count++;
}

void CardManager::loadEnhancer(u8 enhancer) {
    sassert(enhancer < ENHANCER_COUNT, "invalid seal");
    FrameEntry* frame = &m_enhancerFrames[enhancer];
    loadEntry(frame, &m_enhancers, enhancer);
}
void CardManager::loadPCard(u8 rank, u8 suit) {
    // TODO!
}
void CardManager::loadBonus(u8 bonus) {
    // sassert(bonus < BONUS_COUNT, "invalid bonus");

    // if ( bonus == BONUS_NONE )
    //     return;

    // bonus = bonusToIdx(bonus);

    // FrameEntry* frame = &m_bonusFrames[bonus];

    // loadEntry(frame, &m_enhancers, bonus);
}

#pragma endregion
#pragma region unload

void CardManager::unloadEntry(FrameEntry* frame, int fidx) {

}

void CardManager::unloadEnhancer(u8 enhancer) {

}
void CardManager::unloadPCard(u8 rank, u8 suit) {

}
void CardManager::unloadBonus(u8 bonus) {

}

#pragma endregion

CardSprite CardManager::loadCard(card_data_t card) {
    u8 enhancement = ENHANCEMENT(card);
    u8 enhancerIdx = enhancementToIdx(enhancement);
    loadEnhancer(enhancerIdx);
    
    // u8 bonus = BONUS(card);
    // loadBonus(bonus);

    // u8 rank = RANK(card);
    // u8 suit = SUIT(card);

    return (CardSprite) {
        .back = &m_backFrame,
        .enhancer = &m_enhancerFrames[enhancerIdx].frame,
        .card = NULL,
        .seal = NULL,
        .bonus = NULL // &m_enhancerFrames[bonus].frame,
    };
}

void CardManager::unloadCard(CardSprite card) {
    
}
