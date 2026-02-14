#include <nds/arm9/video.h>

#include <nds/arm9/input.h>

#include <nds.h>

// #include "core/Sprite/SpriteSheet.h"
// #include "core/Sprite/SpriteFrame.h"
// #include "core/Sprite/Sprite.h"

#include "core/video_allocator/pool.h"

#include <enhancer_sprs.h>

#include "game/card/visual/CardManager.h"

#include <deck.h>
#include <seal_sprs.h>

void loadSpritePalette256(const u16* palette, int slot) {
    dmaCopy(palette, &VRAM_F_EXT_SPR_PALETTE[slot][0], 512);
}

void loadSpritePalette16(const u16* palette, int slot) {
    dmaCopy(palette, &VRAM_F_EXT_SPR_PALETTE[slot][0], 512);
}

void dsInit() {
    videoSetMode(MODE_0_2D);
    oamInit(&oamMain, SpriteMapping_1D_128, true);
    
    videoSetModeSub(MODE_0_2D);
    oamInit(&oamSub, SpriteMapping_1D_128, true);

    vramSetPrimaryBanks(VRAM_A_MAIN_BG, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

    consoleDemoInit();
    
    vramSetBankF(VRAM_F_LCD);

    loadSpritePalette256(enhancer_sprsPal, 1);
    loadSpritePalette256(deckPal, 2);
    // loadSpritePalette16(seal_sprsPal, 2);

    vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

    dmaCopy(seal_sprsPal, SPRITE_PALETTE, seal_sprsPalLen);
}

#define NUMBER_OF_FRAMES 50

u32 oamBytesForSprite(SpriteSize size, SpriteColorFormat format) {
    int w = 0, h = 0;

    switch (size) {
        case SpriteSize_8x8:   w = 8;  h = 8;  break;
        case SpriteSize_16x16: w = 16; h = 16; break;
        case SpriteSize_32x32: w = 32; h = 32; break;
        case SpriteSize_64x64: w = 64; h = 64; break;

        case SpriteSize_16x8:  w = 16; h = 8;  break;
        case SpriteSize_32x8:  w = 32; h = 8;  break;
        case SpriteSize_32x16: w = 32; h = 16; break;
        case SpriteSize_64x32: w = 64; h = 32; break;

        case SpriteSize_8x16:  w = 8;  h = 16; break;
        case SpriteSize_8x32:  w = 8;  h = 32; break;
        case SpriteSize_16x32: w = 16; h = 32; break;
        case SpriteSize_32x64: w = 32; h = 64; break;
    }

    int tiles = (w / 8) * (h / 8);

    int bytesPerTile =
        (format == SpriteColorFormat_256Color) ? 64 : 32;

    return tiles * bytesPerTile;
}


int main(int argc, char** argv) {
    dsInit();

    pool_t pool;
    pool_init(&pool, &oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

    CardManager cardManager(&pool, 25);

    card_data_t card = 0;
    set_enhancement(&card, STEEL_ENHANCEMENT);
    set_seal(&card, RED_SEAL);
    CardSprite cs = cardManager.loadCard(card);

    cs.flipped = false;
    DrawingParams params = {
        0,
        10, 10,
        0,
        false,
        false,
        false, false,
        false
    };

    while(1) {
        scanKeys();

        CardSprite_draw(&cs, params);

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);

        // do {
        //     scanKeys();
        // } while(!keysDown());
    }

    do {
        scanKeys();
    } while(!keysDown());

    return 0;
}
