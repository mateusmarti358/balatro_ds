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

CardManager::CardManager(pool_t *pool) : m_pool(pool),
    m_enhancers(enhancer_sprsTiles, enhancer_sprsTilesLen, SpriteSize_32x32, SpriteColorFormat_256Color),
{
    SpriteSheet seals_sprsheet;
    SpriteSheet_init(&seals_sprsheet, seal_sprsTiles, SpriteSize_8x8, SpriteColorFormat_16Color);

    for ( int i = 0; i < SEAL_COUNT; i++ ) {
        void* seal_sprite_addr = SpriteSheet_getSpriteData(&seals_sprsheet, i).ptr;
        m_sealsFrames[i] = { pool->oam, NULL, SpriteSize_8x8, SpriteColorFormat_16Color };
        m_sealsFrames[i].gfx = oamAllocateGfx(pool->oam, m_sealsFrames[i].size, m_sealsFrames[i].format);
        dmaCopy(seal_sprite_addr, m_sealsFrames[i].gfx, oamBytesForSprite(m_sealsFrames[i].size, m_sealsFrames[i].format));
    }
}

#pragma region load

void CardManager::loadEntry(FrameEntry* frame, int fidx) {
    if ( frame->count != 0 ) {
        sassert(frame->frame.valid(), "invalid frame: %d", fidx);
        frame->count++;
        return;
    }

    m_seals.loadFrame(&frame->frame, m_oam, fidx);
    frame->count++;
}

void CardManager::loadEnhancer(u8 enhancer) {
    sassert(enhancer < ENHANCER_COUNT, "invalid seal");
    FrameEntry* frame = &m_enhancerFrames[enhancer];
    loadEntry(frame, enhancer);
}
void CardManager::loadPCard(u8 rank, u8 suit) {
    // TODO!
}
void CardManager::loadBonus(u8 bonus) {
    sassert(bonus < BONUS, "invalid bonus");

    if ( bonus == BONUS_NONE )
        return;

    bonus = bonusToIdx(bonus);

    FrameEntry* frame = &m_enhancerFrames[bonus];

    loadEntry(frame, bonus);
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

void CardManager::loadCard(card_data_t card) {
    u8 enhancement = ENHANCEMENT(card);
    u8 enhancerIdx = enhancementToIdx(enhancement);
    loadEnhancer(enhancerIdx);
    
    u8 bonus = BONUS(card) + 13;
    sassert(bonus < 4, "invalid bonus");
    if ( !m_enhancerFrames[bonus].valid() ) {
        m_enhancers.loadFrame(&m_enhancerFrames[bonus], nullptr, bonus);
    }

    // u8 rank = RANK(card);
    // u8 suit = SUIT(card);
}

void CardManager::draw(card_data_t card, int id, int x, int y) {
    u8 enhancement = ENHANCEMENT(card);
    sassert(m_enhancerFrames[enhancement].valid(), "invalid enhancement, poss cause: card not loaded");

    u8 seal = SEAL(card);
    if ( seal != NO_SEAL ) {
        Sprite_draw(&m_sealsFrames[seal], id, x, y);
    }
}

void CardManager::unloadCard(CardSprite card) {
    
}
