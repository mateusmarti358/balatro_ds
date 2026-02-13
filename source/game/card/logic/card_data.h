#pragma once

#include <nds.h>

enum class Suit {
    DIAMONDS = 0,
    CLUBS = 1,
    HEARTS = 2,
    SPADES = 3
};

typedef u16 card_data_t;
typedef u8 seal_t;

#pragma region card_data_macros

#define NO_SEAL 0
#define GOLD_SEAL 1
#define PURPLE_SEAL 2
#define RED_SEAL 3
#define BLUE_SEAL 4

#define NOT_ENHANCED 0
#define LUCKY_ENHANCEMENT 1
#define GLASS_ENHANCEMENT 2
#define GOLD_ENHANCEMENT 3
#define STEEL_ENHANCEMENT 4

#define BONUS_NONE 0
#define BONUS_CHIPS 1
#define BONUS_MULT 2
#define BONUS_WILD 3

#define IS_STONE(card) ((card >> 0) & 1)
#define RANK(card) ((card >> 1) & 0xF)
#define SUIT(card) (Suit)((card >> 5) & 0b111)
#define SEAL(card) ((card >> 8) & 0b111)
#define ENHANCEMENT(card) ((card >> 11) & 0b111)
#define BONUS(card) ((card >> 14) & 0b11)

#define STONE_MASK       (0x1 << 0)
#define RANK_MASK        (0xF << 1)
#define SUIT_MASK        (0x7 << 5)
#define SEAL_MASK        (0x7 << 8)
#define ENHANCEMENT_MASK (0x7 << 11)
#define BONUS_MASK       (0x3 << 14)

#pragma endregion

void set_stone(card_data_t* card, bool is_stone);
void set_rank(card_data_t* card, int rank);
void set_suit(card_data_t* card, Suit suit);
void set_seal(card_data_t* card, int seal);
void set_enhancement(card_data_t* card, int enhancement);
void set_bonus(card_data_t* card, int bonus);
