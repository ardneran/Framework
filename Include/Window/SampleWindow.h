//
//  SampleWindow.h
//  Framework
//
//  Created by Narendra Umate on 8/18/15.
//
//

#ifndef Framework_SampleWindow_h
#define Framework_SampleWindow_h

#include <list>
#include "Spatial.h"
#include "GLFWWindow.h"
#include "MetalWindow.h"
#include "SDLWindow.h"

#define USE_SDL 1

#if USE_SDL
class SampleWindow : public SDLWindow {
#else
class SampleWindow : public NativeWindow {
#endif
public:
    SampleWindow(Parameters& parameters);
    virtual ~SampleWindow();

private:
    void createEffects();
    void createScene();
    void destroyEffects();
    void destroyScene();
};

#endif
