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

CardManager::CardManager(
    OamState* oam
) : m_oam(oam),
    m_enhancers(enhancer_sprsTiles, enhancer_sprsTilesLen, SpriteSize_32x32, SpriteColorFormat_256Color),
    m_seals(seal_sprsTiles, seal_sprsTilesLen, SpriteSize_16x16, SpriteColorFormat_16Color)
{}

#pragma region load
void loadEnhancement(OamState*u8 enhancer) {

}
void loadPCard(OamState*u8 rank, u8 suit) {

}
void CardManager::loadSeal(OamState*seal_t seal) {
    u8 seal = SEAL(card);
    sassert(seal < SEAL_COUNT, "invalid seal");

    if ( seal == NO_SEAL )
        return;

    FrameEntry* frame = &m_sealFrames[seal - 1];

    if ( frame->count != 0 ) {
        sassert(frame->frame.valid(), "invalid frame");
        frame->count++;
        return;
    }
    
    m_seals.loadFrame(&frame->frame, nullptr, seal - 1);
    frame->count++;
}
void loadBonus(OamState*u8 bonus) {

}

#pragma endregion
#pragma region unload

void unloadEnhancement(OamState*u8 enhancer) {

}
void unloadPCard(OamState*u8 rank, u8 suit) {

}
void unloadSeal(OamState*seal_t seal) {

}
void unloadBonus(OamState*u8 bonus) {

}

#pragma endregion

void CardManager::loadCard(OamState*card_data_t card) {
    u8 enhancement = ENHANCEMENT(card);
    sassert(enhancement < ENHANCER_COUNT, "invalid enhancement");
    int enh_idx = enhancementToIdx(enhancement);
    if ( !m_enhancerFrames[enh_idx].valid() ) {
        m_enhancers.loadFrame(&m_enhancerFrames[enhancement], nullptr, enh_idx);
    }

    loadSeal(SEAL(card));
    
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
    if ( !m_sealFrames[seal].valid() ) {
        
    }
}
