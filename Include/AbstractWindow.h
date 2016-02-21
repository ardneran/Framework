//
//  AbstractWindow.h
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#ifndef ____AbstractWindow__
#define ____AbstractWindow__

#include <cassert>
#include <iostream>

#include "Culler.h"
#include "Renderer.h"
#include "ObjMeshLoader.h"
#include "Octree.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Renderer;

class AbstractWindow {
public:
    struct Parameters {
        Parameters()
        : title("")
        , xOrigin(0)
        , yOrigin(0)
        , xSize(0)
        , ySize(0)
        , renderer(NULL) {
        }
        std::string title;
        int xOrigin;
        int yOrigin;
        int xSize;
        int ySize;
        Renderer* renderer;
    };

	AbstractWindow(Parameters& parameters); // Abstract base class
    virtual ~AbstractWindow() = 0;

    inline void setTitle(const std::string& title) { m_title = title; }
    inline std::string getTitle() { return m_title; }
    inline void setXOrigin(const int& xOrigin) { m_xOrigin = xOrigin; }
    inline int getXOrigin() { return m_xOrigin; }
    inline void setYOrigin(const int& yOrigin) { m_yOrigin = yOrigin; }
    inline int getYOrigin() { return m_yOrigin; }
    inline void setXSize(const int& xSize) { m_xSize = xSize; }
    inline int getXSize() { return m_xSize; }
    inline void setYSize(const int& ySize) { m_ySize = ySize; }
    inline int getYSize() { return m_ySize; }

    inline bool isMinimized() const { return m_minimized; }
    inline bool isMaximized() const { return m_maximized; }
    inline bool isActive() const { return m_active; }

    void handlePollEvent();

    virtual void onMove(const int& x, const int& y);
    virtual bool onResize(const int& xSize, const int& ySize);
    virtual void onMinimize();
    virtual void onMaximize();
    virtual void onRestore();
    virtual void onDisplay();
    virtual void onIdle();

	virtual void setSwapInterval(const int& syncInterval);
	virtual void swapWindow();

protected:

    std::string m_title;
    int m_xOrigin;
    int m_yOrigin;
    int m_xSize;
    int m_ySize;
    Renderer* m_renderer;

    bool m_minimized;
    bool m_maximized;
    bool m_active;
    Camera* m_camera;
    Culler* m_culler;
    Octree* m_octree;
    ObjMeshLoader* m_objMeshLoader;

private:
    void initializeSDL();
    void initializeSDLimage();
    void initializeSDLttf();
    void initializeOpenGL();
    void initializeOther();
    void deinitializeSDL();
    void deinitializeSDLimage();
    void deinitializeSDLttf();
    void deinitializeOpenGL();
    void deinitializeOther();

    void handleWindowEvent();
    void handleKeyUpEvent();
    void handleKeyDownEvent();

    SDL_Event m_sdlEvent;
    SDL_Window* m_sdlWindow;
    SDL_GLContext m_sdlContext;
};

#endif /* defined(____AbstractWindow__) */
