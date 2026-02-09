#include "CardInstance.h"

static int indexFromRankSuit(char rank, char suit) {
    return (rank - 1) + (suit * 13);
}
static inline EnhancerSpriteIndex sealToIndex(char seal) {
    switch (seal) {
        case GOLD_SEAL: return EnhancerSpriteIndex::GoldSeal;
        case PURPLE_SEAL: return EnhancerSpriteIndex::PurpleSeal;
        case RED_SEAL: return EnhancerSpriteIndex::RedSeal;
        case BLUE_SEAL: return EnhancerSpriteIndex::BlueSeal;
    }
}
static inline EnhancerSpriteIndex enhancementToIndex(char enhancement) {
    switch (enhancement) {
        case GOLD_ENHANCEMENT: return EnhancerSpriteIndex::Gold;
        case LUCKY_ENHANCEMENT: return EnhancerSpriteIndex::Lucky;
        case GLASS_ENHANCEMENT: return EnhancerSpriteIndex::Glass;
        case STEEL_ENHANCEMENT: return EnhancerSpriteIndex::Steel;
    }
} 
static inline EnhancerSpriteIndex bonusToIndex(char bonus) {
    switch (bonus) {
        case BONUS_CHIPS: return EnhancerSpriteIndex::Bonus;
        case BONUS_MULT: return EnhancerSpriteIndex::Mult;
        case BONUS_WILD: return EnhancerSpriteIndex::Wild;
    }
}
