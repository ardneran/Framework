//
//  VisualEffect.cpp
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#include "VisualEffect.h"

VisualEffect::VisualEffect(void* program)
: m_program(program) {
}

VisualEffect::~VisualEffect() {
    m_program = nullptr;
}

void VisualEffect::setProgram(void* program) {
    m_program = program;
}

void* VisualEffect::getProgram() {
    return m_program;
}

GlVisualEffect::GlVisualEffect(GlProgram* program)
: VisualEffect(program) {
}

GlVisualEffect::~GlVisualEffect() {
    delete static_cast<GlVisualEffect*>(m_program);
}

void GlVisualEffect::setProgram(GlProgram* program) {
    m_program = program;
}

GlProgram* GlVisualEffect::getProgram() {
    return static_cast<GlProgram*>(m_program);
}
