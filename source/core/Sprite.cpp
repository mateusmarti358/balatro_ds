#include "Sprite.h"

Sprite::Sprite() : m_frame(nullptr) {}

Sprite::Sprite(SpriteFrame* frame) : m_frame(frame) {}

void Sprite::setFrame(SpriteFrame* frame) { m_frame = frame; }

SpriteFrame* Sprite::frame() const { return m_frame; }

void Sprite::draw(int id, int x, int y) {
    if (!m_frame) return;
    if (!m_frame->valid()) return;

    oamSet(
        m_frame->oam(), id,
        x, y,
        0, 0,
        m_frame->size(), m_frame->format(),
        m_frame->gfx(),
        0,
        false, false,
        false, false,
        false
    );
}
