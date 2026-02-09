#include <nds/arm9/video.h>

#include <nds/arm9/input.h>

#include <nds.h>
#include <stdio.h>

#include "core/SpriteSheet.h"
#include "core/SpriteFrame.h"
#include "core/Sprite.h"

#include <enhancer_sprs.h>

void dsInit() {
    videoSetMode(MODE_0_2D);
    oamInit(&oamMain, SpriteMapping_1D_128, false);
    
    videoSetModeSub(MODE_0_2D);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

    vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

    consoleDemoInit();

    dmaCopy(enhancer_sprsPal, SPRITE_PALETTE, enhancer_sprsPalLen);
    // dmaCopy(enhancer_sprsPal, SPRITE_PALETTE_SUB, enhancer_sprsPalLen);
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

    SpriteSheet sheet(enhancer_sprsTiles, enhancer_sprsTilesLen, SpriteSize_64x64, SpriteColorFormat_256Color);

    SpriteFrame frames[NUMBER_OF_FRAMES];
    Sprite sprites[NUMBER_OF_FRAMES];

    int loaded = 0;
    u32 bytes_used = 0;

    while(1) {
        scanKeys();

        for (int i = 0; i < loaded; i++) {
            if (!sprites[i].frame()->valid()) {
                printf("Invalid frame %d\n", i);
            }

            int x = (i % 5) * 48;
            int y = ((i / 5) * 64) % 192;

            sprites[i].draw(i, x, y);
        }

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    
        printf("Loaded %d/%d\nBytes used: %d\n--\n", loaded, NUMBER_OF_FRAMES, bytes_used);

        do {
            scanKeys();
        } while(!keysDown());

        bytes_used += oamBytesForSprite(SpriteSize_64x64, SpriteColorFormat_256Color);
        int err = sheet.loadFrame(&frames[loaded], &oamMain, loaded % 34);
        if (err) {
            printf("Failed to load frame %d\n", loaded + 1);
            break;
        }
        sprites[loaded].setFrame(&frames[loaded]);
        loaded++;
    }

    do {
        scanKeys();
    } while(!keysDown());

    return 0;
}
