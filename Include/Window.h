//
//  Window.h
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#ifndef ____Window__
#define ____Window__

#include <cassert>
#include <iostream>
#include "Camera.h"
#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"

class Window {
public:
    struct Parameters {
        Parameters()
        : title("")
        , xOrigin(0)
        , yOrigin(0)
        , xSize(0)
        , ySize(0) {
        }
        std::string title;
        int xOrigin, yOrigin, xSize, ySize;
    };

    virtual ~Window();

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

    void handleEvent(const SDL_Event& event);

    virtual void onMove(const int& x, const int& y);
    virtual bool onResize(const int& xSize, const int& ySize);
    virtual void onMinimize();
    virtual void onMaximize();
    virtual void onRestore();
    virtual void onDisplay();
    virtual void onIdle();

protected:
    Window(Parameters& parameters); // Abstract base class

    std::string m_title;
    int m_xOrigin;
    int m_yOrigin;
    int m_xSize;
    int m_ySize;
    bool m_minimized;
    int m_maximized;
    int m_active;

    Renderer* m_renderer;
    Camera m_camera;

private:
    void initializeSDL();
    void initializeSDLimage();
    void initializeSDLttf();
    void initializeOpenGL();
    void deinitializeSDL();
    void deinitializeSDLimage();
    void deinitializeSDLttf();
    void deinitializeOpenGL();

    void handleWindowEvent(const SDL_Event& event);
    void handleKeyUpEvent(const SDL_Event& event);
    void handleKeyDownEvent(const SDL_Event& event);

    SDL_Window* m_sdlWindow;
    SDL_GLContext m_sdlContext;
};

#endif /* defined(____Window__) */
