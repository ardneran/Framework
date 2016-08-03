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
    VisualEffect(void* program);
    virtual ~VisualEffect();

    void setProgram(void* program);
    void* getProgram();

protected:
    void* m_program;
};

class GlVisualEffect : public VisualEffect {
public:
    GlVisualEffect(GlProgram* program);
    virtual ~GlVisualEffect();
    
    void setProgram(GlProgram* program);
    GlProgram* getProgram();
};

#endif /* VisualEffect_h */
