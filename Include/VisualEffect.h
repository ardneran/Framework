//
//  VisualEffect.h
//  Framework
//
//  Created by Narendra Umate on 1/15/16.
//
//

#ifndef VisualEffect_h
#define VisualEffect_h

#include "GlProgram.h"

class VisualEffect {
public:
    VisualEffect(GlProgram* program);
    ~VisualEffect();

    void setProgram(GlProgram* program);
    GlProgram* getProgram();

private:
    GlProgram* m_program;
};

#endif /* VisualEffect_h */
