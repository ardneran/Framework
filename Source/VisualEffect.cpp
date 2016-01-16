//
//  VisualEffect.cpp
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#include "VisualEffect.h"

VisualEffect::VisualEffect(GlProgram* program)
: m_program(program) {
}

VisualEffect::~VisualEffect() {
    m_program = NULL;
}

void VisualEffect::setProgram(GlProgram* program) {
    m_program = program;
}

GlProgram* VisualEffect::getProgram() {
    return m_program;
}
