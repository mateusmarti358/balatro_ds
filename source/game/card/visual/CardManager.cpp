#include "CardManager.h"

#include <back_sprs.h>
#include <enhancer_sprs.h>
#include <bonus_sprs.h>
// #include <deck.h>
#include <seal_sprs.h>

CardManager::CardManager(pool_t *pool, u16 back) : m_pool(pool) {
    SpriteSheet_init(&m_enhancers, enhancer_sprsTiles, SpriteSize_32x32, SpriteColorFormat_256Color);
    SpriteSheet_init(&m_bonuses, bonus_sprsTiles, SpriteSize_32x32, SpriteColorFormat_256Color);

    SpriteSheet back_sprsheet;
    SpriteSheet_init(&back_sprsheet, back_sprsTiles, SpriteSize_32x32, SpriteColorFormat_256Color);

    void* back_sprite_addr = SpriteSheet_getSpriteData(&back_sprsheet, back).ptr;
    m_backFrame = { pool->oam, NULL, SpriteSize_32x32, SpriteColorFormat_256Color };
    m_back_poolidx = pool_aquire(pool);
    m_backFrame.gfx = pool->pool[m_back_poolidx];
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
    for ( int i = 0; i < SEAL_COUNT; i++ )
        oamFreeGfx(m_pool->oam, m_sealsFrames[i].gfx);
    
}

#pragma region load

void CardManager::loadEntry(FrameEntry* frame, SpriteSheet* sheet, int fidx) {
    if ( frame->count != 0 ) {
        frame->count++;
        return;
    }

    SpriteData data = SpriteSheet_getSpriteData(sheet, fidx);
    initSpriteFrame(&frame->frame, data, m_pool->oam);
    
    u16 pool_idx = pool_aquire(m_pool);
    void* gfx = m_pool->pool[pool_idx];
    dmaCopy(data.ptr, gfx, data.size);
    
    frame->frame.gfx = gfx;
    frame->pool_idx = pool_idx;

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
    sassert(bonus < BONUS_COUNT, "invalid bonus");

    if ( bonus == BONUS_NONE )
        return;

    FrameEntry* frame = &m_bonusFrames[bonus - 1];
    loadEntry(frame, &m_bonuses, bonus - 1);
}

#pragma endregion
#pragma region unload

void CardManager::unloadEntry(FrameEntry* frame) {
    sassert(frame->count > 0, "unloading already unloaded frame");

    frame->count--;

    if ( frame->count != 0 )
        return;

    pool_release(m_pool, frame->pool_idx);
}

void CardManager::unloadEnhancer(u8 enhancer) {
    unloadEntry(&m_enhancerFrames[enhancer]);
}
void CardManager::unloadPCard(u8 rank, u8 suit) {

}
void CardManager::unloadBonus(u8 bonus) {
    if ( bonus == BONUS_NONE )
        return;

    unloadEntry(&m_bonusFrames[bonus - 1]);
}

#pragma endregion

CardSprite CardManager::loadCard(card_data_t card) {
    u8 enhancement = ENHANCEMENT(card);
    loadEnhancer(enhancement);
    
    u8 bonus = BONUS(card);
    loadBonus(bonus);

    u8 seal = SEAL(card);

    // u8 rank = RANK(card);
    // u8 suit = SUIT(card);

    return (CardSprite) {
        .back = &m_backFrame,
        .enhancer = &m_enhancerFrames[enhancement].frame,
        .bonus = (bonus > 0) ? &m_bonusFrames[bonus - 1].frame : NULL,
        .card = NULL,
        .seal = (seal > 0) ? &m_sealsFrames[seal - 1] : NULL
    };
}

void CardManager::unloadCard(card_data_t card) {
    unloadEnhancer(ENHANCEMENT(card));
    unloadBonus(BONUS(card));
}
