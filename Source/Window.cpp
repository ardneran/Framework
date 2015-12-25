//
//  Window.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "Window.h"

Window::Window(Parameters& parameters)
:	m_title(parameters.title)
,	m_xOrigin(parameters.xOrigin)
,	m_yOrigin(parameters.yOrigin)
,	m_xSize(parameters.xSize)
,	m_ySize(parameters.ySize)
,	m_active(true) {
	initializeSDL();
	initializeSDLimage();
	initializeSDLttf();
	initializeOpenGL();
}

Window::~Window() {
	deinitializeOpenGL();
	deinitializeSDLttf();
	deinitializeSDLimage();
	deinitializeSDL();
}

void Window::onMove(const int& x, const int& y) {
	m_xOrigin = x;
	m_yOrigin = y;
}

bool Window::onResize(const int& xSize, const int& ySize) {
	m_minimized = false;
	m_maximized = false;

	if (m_xSize != xSize || m_ySize != ySize) {
		m_xSize = xSize;
		m_ySize = ySize;

		if (m_renderer) {
			m_renderer->resize(xSize, ySize);
		}

		return  true;
	}
	return false;
}

void Window::onMinimize() {
	m_minimized = true;
	m_maximized = false;
}

void Window::onMaximize() {
	m_minimized = false;
	m_maximized = true;
}

void Window::onRestore() {
	m_minimized = false;
	m_maximized = false;
}

void Window::onDisplay() {
}

void Window::onIdle() {
}

void Window::initializeSDL() {
	unsigned int flags = SDL_INIT_VIDEO;
	assert(SDL_Init(flags) == 0);
}

void Window::initializeSDLimage() {
	unsigned int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	assert(IMG_Init(flags) == flags);
}

void Window::initializeSDLttf() {
	assert(TTF_Init() == 0);
}

void Window::initializeOpenGL() {
	// Set Attributes
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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 32);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 0);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 0);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG | SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG | SDL_GL_CONTEXT_RESET_ISOLATION_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);

	// Create Window
	m_sdlWindow = SDL_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
	assert(m_sdlWindow != nullptr);

	// Create Context
	const int major[] = { 4, 4, 4, 4, 4, 4, 3, 3, 3, 3 };
	const int minor[] = { 5, 4, 3, 2, 1, 0, 3, 2, 1, 0 };
	for (int i = 0; i < 10; ++i) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major[i]);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor[i]);
		m_sdlContext = SDL_GL_CreateContext(m_sdlWindow);
		if (m_sdlContext != nullptr) {
			break;
		}
	}
	assert(m_sdlContext != nullptr);

	// Set VSync
	if (SDL_GL_SetSwapInterval(-1) != 0) {
		if (SDL_GL_SetSwapInterval(1) != 0) {
			if (SDL_GL_SetSwapInterval(0) != 0) {
			}
		}
	}

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

#if not defined (__APPLE__)
	// TODO Fix this for Mac
	for (GLint i = 0 ; i < extensionsCount ; ++i) {
		std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
	}
#endif // defined (__APPLE__)

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
	for (int i = 0 ; i < renderDrivers ; ++i) {
		SDL_GetRenderDriverInfo(i, &info);
		std::cout << "Render Driver " << i << ": " << info.name;

		bool isSoftware      = info.flags & SDL_RENDERER_SOFTWARE;
		bool isHardware      = info.flags & SDL_RENDERER_ACCELERATED;
		bool isVSyncEnabled  = info.flags & SDL_RENDERER_PRESENTVSYNC;
		bool isTargetTexture = info.flags & SDL_RENDERER_TARGETTEXTURE;

		std::cout << " [";
		if (isSoftware) std::cout << "SW";
		if (isHardware) std::cout << "HW";
		if (isVSyncEnabled) std::cout << ", VS";
		if (isTargetTexture) std::cout << ", TT";
		std::cout << "]" << std::endl;
	}
}

void Window::deinitializeSDL() {
	SDL_Quit();
}

void Window::deinitializeSDLimage() {
	IMG_Quit();
}

void Window::deinitializeSDLttf() {
	TTF_Quit();
}

void Window::deinitializeOpenGL() {
	if (m_sdlWindow != 0) {
		SDL_DestroyWindow(m_sdlWindow);
	}
}

void Window::handleEvent(const SDL_Event& event) {
	switch (event.type) {
		case SDL_WINDOWEVENT: {
			handleWindowEvent(event);
		}
			break;
		case SDL_KEYUP: {
			handleKeyUpEvent(event);
		}
			break;
		case SDL_KEYDOWN: {
			handleKeyDownEvent(event);
		}
			break;
		case SDL_QUIT: {
			m_active = false;
		}
			break;
	}
}

void Window::handleWindowEvent(const SDL_Event &event) {
	switch (event.window.event) {
		case SDL_WINDOWEVENT_MOVED:
			onMove(event.window.data1, event.window.data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			onResize(event.window.data1, event.window.data2);
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
		default:
			break;
	}
}

void Window::handleKeyUpEvent(const SDL_Event& event) {
	switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			break;
		default:
			break;
	}
}

void Window::handleKeyDownEvent(const SDL_Event& event) {
	switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			m_active = false;
			break;
		default:
			break;
	}
}

