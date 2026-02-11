#include <nds/arm9/video.h>

#include <nds/arm9/input.h>

#include <nds.h>
#include <stdio.h>

#include "core/Sprite/SpriteSheet.h"
#include "core/Sprite/SpriteFrame.h"
#include "core/Sprite/Sprite.h"

#include <enhancer_sprs.h>

void dsInit() {
    videoSetMode(MODE_0_2D);
    oamInit(&oamMain, SpriteMapping_1D_128, false);
    
    videoSetModeSub(MODE_0_2D);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

    vramSetPrimaryBanks(VRAM_A_MAIN_SPRITE, VRAM_B_MAIN_SPRITE, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);

    consoleDemoInit();

    dmaCopy(enhancer_sprsPal, SPRITE_PALETTE, enhancer_sprsPalLen);
    dmaCopy(enhancer_sprsPal, SPRITE_PALETTE_SUB, enhancer_sprsPalLen);
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

    SpriteSheet sheet;
    sheet.source = enhancer_sprsTiles;
    sheet.sprite_size = SpriteSize_32x32;
    sheet.format = SpriteColorFormat_256Color;

    SpriteData sd = SpriteSheet_getSpriteData(&sheet, 25);

    void* gfx = oamAllocateGfx(&oamMain, sd.size, sd.format);
    dmaCopy(sd.ptr, gfx, oamBytesForSprite(sd.size, sd.format));
    sd.gfx = gfx;

    SpriteFrame frame;
    initSpriteFrame(&frame, sd, &oamMain);

    Sprite sprite;
    sprite.frame = &frame;

    while(1) {
        scanKeys();

        Sprite_draw(&sprite, 0, 0, 0);

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    do {
        scanKeys();
    } while(!keysDown());

    return 0;
}
