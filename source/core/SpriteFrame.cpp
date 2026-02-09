#include "SpriteFrame.h"

SpriteFrame::SpriteFrame() {
    m_oam = nullptr;
    m_gfx = nullptr;
}

SpriteFrame::~SpriteFrame() {
    if (m_gfx) {
        oamFreeGfx(m_oam, m_gfx);
    }
}

int SpriteFrame::init(
    OamState* oam,
    const void* src,
    u32 sizeBytes,
    SpriteSize size,
    SpriteColorFormat format
) {
    if (!oam || !src) return -1;
    
    if (m_gfx)
        oamFreeGfx(m_oam, m_gfx);

    m_oam = oam;
    m_size = size;
    m_format = format;

    m_gfx = oamAllocateGfx(oam, size, format);
    if (!m_gfx) return -1;
    
    dmaCopy(src, m_gfx, sizeBytes);

    return 0;
}

bool SpriteFrame::valid() const {
    return m_oam && m_gfx;
}

OamState* SpriteFrame::oam() const { return m_oam; }
void* SpriteFrame::gfx() const { return m_gfx; }
SpriteSize SpriteFrame::size() const { return m_size; }
SpriteColorFormat SpriteFrame::format() const { return m_format; }
