//
//  SDLWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "SDLWindow.h"

SDLWindow::SDLWindow(Parameters& parameters)
: AbstractWindow(parameters) {
    initializeSDL();
    //initializeSDLimage();
    //initializeSDLttf();
    initializeOpenGL();
	m_renderer->initialize(); // Called here after the context is created.
}

SDLWindow::~SDLWindow() {
	m_renderer->deinitialize(); // Called here before the context is destroyed.
    deinitializeOpenGL();
    //deinitializeSDLttf();
    //deinitializeSDLimage();
    deinitializeSDL();
}

void SDLWindow::handlePollEvent() {
    while (SDL_PollEvent(&m_sdlEvent)) {
        switch (m_sdlEvent.type) {
            case SDL_WINDOWEVENT: {
                handleWindowEvent();
            } break;
            case SDL_KEYUP: {
                handleKeyUpEvent();
            } break;
            case SDL_KEYDOWN: {
                handleKeyDownEvent();
            } break;
            case SDL_QUIT: {
                m_active = false;
            } break;
        }
    }
}

void SDLWindow::setSwapInterval(const int& syncInterval) {
	SDL_GL_SetSwapInterval(syncInterval);
}

void SDLWindow::swapWindow() {
	SDL_GL_SwapWindow(m_sdlWindow);
}

void SDLWindow::initializeSDL() {
    unsigned int flags = SDL_INIT_VIDEO;
    assert(SDL_Init(flags) == 0);
}

void SDLWindow::initializeSDLimage() {
    unsigned int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
    assert(IMG_Init(flags) == flags);
}

void SDLWindow::initializeSDLttf() {
    assert(TTF_Init() == 0);
}

void SDLWindow::initializeOpenGL() {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 2);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 2);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 2);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 2);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_STEREO, 0);
#if not defined(__linux__)
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 32);
#endif // not defined(__linux__)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 0);
#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, CONTEXT_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, CONTEXT_MINOR_VERSION);
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG | SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG | SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);

    // Create Window
    m_sdlWindow = SDL_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (m_sdlWindow == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        assert(m_sdlWindow != NULL);
    }

#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
    // Create Context
    m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);
    if (m_sdlContext == NULL) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        assert(m_sdlContext != NULL);
    } else {
        std::cout << "OpenGL context: " << CONTEXT_MAJOR_VERSION << "." CONTEXT_MINOR_VERSION << std::endl;
    }
#else
    // Create Context
    const int major[] = { 4, 4, 4, 4, 4, 4, 3, 3, 3, 3 };
    const int minor[] = { 5, 4, 3, 2, 1, 0, 3, 2, 1, 0 };
    int index = 0;
    for (index = 0; index < 10; ++index) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major[index]);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor[index]);
        m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);
        if (m_sdlContext != NULL) {
            break;
        }
    }
    if (m_sdlContext == NULL) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        assert(m_sdlContext != NULL);
    } else {
        std::cout << "OpenGL context: " << major[index] << "." << minor[index] << std::endl;
    }
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)

    // Set Context to Current
    SDL_GL_MakeCurrent(m_sdlWindow, m_sdlContext);

    // Log relevant information
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "OpenGL GLEXT version: " << GL_GLEXT_VERSION << std::endl;
    std::cout << "OpenGL GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;

    GLint extensionsCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionsCount);
    std::cout << "OpenGL Extensions: " << extensionsCount << std::endl;

#if not defined(__APPLE__) && not defined(__linux__)
    // TODO Fix this for unsupported platforms
    for (GLint i = 0; i < extensionsCount; ++i) {
        std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
    }
#endif // defined(__APPLE__) && not defined(__linux__)

    int videoDrivers = SDL_GetNumVideoDrivers();
    std::cout << "Video Drivers: " << videoDrivers << std::endl;

    const std::string currentVideoDriver(SDL_GetCurrentVideoDriver());
    for (int i = 0; i < videoDrivers; ++i) {
        const std::string videoDriver(SDL_GetVideoDriver(i));
        std::cout << "Video Driver " << i << ": " << videoDriver;
        if (currentVideoDriver == videoDriver) {
            std::cout << " [Current]";
        }
        std::cout << std::endl;
    }

    int renderDrivers = SDL_GetNumRenderDrivers();
    std::cout << "Render Drivers: " << renderDrivers << std::endl;

    SDL_RendererInfo info;
    for (int i = 0; i < renderDrivers; ++i) {
        SDL_GetRenderDriverInfo(i, &info);
        std::cout << "Render Driver " << i << ": " << info.name;

        bool isSoftware = info.flags & SDL_RENDERER_SOFTWARE;
        bool isHardware = info.flags & SDL_RENDERER_ACCELERATED;
        bool isVSyncEnabled = info.flags & SDL_RENDERER_PRESENTVSYNC;
        bool isTargetTexture = info.flags & SDL_RENDERER_TARGETTEXTURE;

        std::cout << " [";
        if (isSoftware)
            std::cout << "SW";
        if (isHardware)
            std::cout << "HW";
        if (isVSyncEnabled)
            std::cout << ", VS";
        if (isTargetTexture)
            std::cout << ", TT";
        std::cout << "]" << std::endl;
    }

	m_renderer->setWindow(this);
}

void SDLWindow::deinitializeSDL() {
    SDL_Quit();
}

void SDLWindow::deinitializeSDLimage() {
    IMG_Quit();
}

void SDLWindow::deinitializeSDLttf() {
    TTF_Quit();
}

void SDLWindow::deinitializeOpenGL() {
    if (m_sdlWindow != NULL) {
        SDL_DestroyWindow(m_sdlWindow);
    }
}

void SDLWindow::handleWindowEvent() {
    switch (m_sdlEvent.window.event) {
        case SDL_WINDOWEVENT_MOVED:
            onMove(m_sdlEvent.window.data1, m_sdlEvent.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            onResize(m_sdlEvent.window.data1, m_sdlEvent.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            onMinimize();
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            onMaximize();
            break;
        case SDL_WINDOWEVENT_RESTORED:
            onRestore();
            break;
		case SDL_WINDOWEVENT_SHOWN:
			onDisplay();
			break;
        default:
            break;
    }
}

void SDLWindow::handleKeyUpEvent() {
    switch (m_sdlEvent.key.keysym.sym) {
        case SDLK_ESCAPE:
            break;
        default:
            break;
    }
}

void SDLWindow::handleKeyDownEvent() {
	const float increment = 0.50f;
    switch (m_sdlEvent.key.keysym.sym) {
        case SDLK_ESCAPE:
            m_active = false;
            break;
		case SDLK_UP:
			{
				Vec3 position;
				m_camera->getPosition(position);
				m_camera->setPosition(position + Vec3(0, 0, increment));
			}
			break;
		case SDLK_DOWN:
			{
				Vec3 position;
				m_camera->getPosition(position);
				m_camera->setPosition(position + Vec3(0, 0, -increment));
			}
			break;
		case SDLK_RIGHT:
			{
				Vec3 position;
				m_camera->getPosition(position);
				m_camera->setPosition(position + Vec3(increment, 0, 0));
			}
			break;
		case SDLK_LEFT:
			{
				Vec3 position;
				m_camera->getPosition(position);
				m_camera->setPosition(position + Vec3(-increment, 0, 0));
			}
			break;
        default:
            break;
    }
}
