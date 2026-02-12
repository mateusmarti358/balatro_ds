#include "SpriteFrame.h"
#include "SpriteSheet.h"

inline u16 getTileSize(SpriteSize size, SpriteColorFormat format) {
    u32 pixels;
    switch(size) {
        case SpriteSize_8x8: pixels = 8*8; break;
        case SpriteSize_16x16: pixels = 16*16; break;
        case SpriteSize_32x32: pixels = 32*32; break;
        case SpriteSize_64x64: pixels = 64*64; break;
        
        case SpriteSize_16x8: pixels = 16*8; break;
        case SpriteSize_32x8: pixels = 32*8; break;
        case SpriteSize_32x16: pixels = 32*16; break;
        case SpriteSize_64x32: pixels = 64*32; break;
        
        case SpriteSize_8x16: pixels = 8*16; break;
        case SpriteSize_8x32: pixels = 8*32; break;
        case SpriteSize_16x32: pixels = 16*32; break;
        case SpriteSize_32x64: pixels = 32*64; break;
        
        default:
            return 0;
    }

    if (format == SpriteColorFormat_256Color) {
        return pixels;
    } else {
        return pixels / 2;
    }
}

void SpriteSheet_init(SpriteSheet* sheet, const void* source, SpriteSize sprite_size, SpriteColorFormat format) {
    sheet->source = source;
    sheet->sprite_size = sprite_size;
    sheet->format = format;
    sheet->sprite_size_bytes = getTileSize(sprite_size, format);
}

SpriteData SpriteSheet_getSpriteData(SpriteSheet* sheet, u16 index) {
    sassert(sheet->sprite_size_bytes != 0, "invalid sprite sheet");
    u32 offset = index * sheet->sprite_size_bytes;
    return (SpriteData){ (void*)sheet->source + offset, sheet->sprite_size_bytes, sheet->sprite_size, sheet->format };
}
