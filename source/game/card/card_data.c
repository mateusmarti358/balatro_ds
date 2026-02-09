#include "card_data.h"

static inline void set_stone(card_data_t* card, bool is_stone) {
    *card = (is_stone ? 1 : 0);
}
static inline void set_rank(card_data_t* card, int rank) {
    *card &= ~RANK_MASK;             // Clear bits 1-4
    *card |= (rank & 0xF) << 1;      // Set new rank
}
static inline void set_suit(card_data_t* card, Suit suit) {
    *card &= ~SUIT_MASK;             // Clear bits 5-7
    *card |= (suit & 0b111) << 5;    // Set new suit
}
static inline void set_seal(card_data_t* card, int seal) {
    *card &= ~SEAL_MASK;             // Clear bits 8-10
    *card |= (seal & 0b111) << 8;    // Set new seal
}
static inline void set_enhancement(card_data_t* card, int enhancement) {
    *card &= ~ENHANCEMENT_MASK;      // Clear bits 11-13
    *card |= (enhancement & 0b111) << 11;
}
static inline void set_bonus(card_data_t* card, int bonus) {
    *card &= ~BONUS_MASK;            // Clear bits 14-15
    *card |= (bonus & 0b11) << 14;
}
