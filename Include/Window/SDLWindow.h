//
//  SDLWindow.h
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#ifndef ____SDLWindow__
#define ____SDLWindow__

#if USE_SDL

#include <cassert>
#include <iostream>

#include "AbstractWindow.h"
#include "Culler.h"
#include "ObjMeshLoader.h"
#include "Octree.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

struct Parameters;

class SDLWindow : public AbstractWindow {

public:
	SDLWindow(Parameters& parameters);
    virtual ~SDLWindow() = 0;

    void handlePollEvent();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

private:
    void initializeSDL();
    void initializeSDLimage();
    void initializeSDLttf();
    void initializeOpenGL();
    void deinitializeSDL();
    void deinitializeSDLimage();
    void deinitializeSDLttf();
    void deinitializeOpenGL();

    void handleWindowEvent();
    void handleKeyUpEvent();
    void handleKeyDownEvent();

    SDL_Event m_sdlEvent;
    SDL_Window* m_sdlWindow;
    SDL_GLContext m_sdlGlContext;
};

#endif

#endif /* defined(____SDLWindow__) */
