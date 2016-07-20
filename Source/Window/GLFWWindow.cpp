//
//  GLFWWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "GLFWWindow.h"

GLFWWindow::GLFWWindow(Parameters& parameters)
: AbstractWindow(parameters) {
	initializeGLFW();
	switch (m_renderer->getType()) {
		case Renderer::DX:
			break;
		case Renderer::GL:
			initializeOpenGL();
			break;
		default:
			break;
	}
	m_renderer->initialize(); // Called here after the context is created.
}

GLFWWindow::~GLFWWindow() {
	m_renderer->deinitialize(); // Called here before the context is destroyed.
    switch (m_renderer->getType()) {
        case Renderer::DX:
            break;
        case Renderer::GL:
            deinitializeOpenGL();
            break;
        default:
            break;
    }
	deinitializeGLFW();
}

void GLFWWindow::handlePollEvent() {
/*
	while (GLFW_PollEvent(&m_GLFWEvent)) {
		switch (m_GLFWEvent.type) {
			case GLFW_WINDOWEVENT: {
				handleWindowEvent();
			} break;
			case GLFW_KEYUP: {
				handleKeyUpEvent();
			} break;
			case GLFW_KEYDOWN: {
				handleKeyDownEvent();
			} break;
			case GLFW_QUIT: {
				m_active = false;
			} break;
		}
	}
*/
}

void GLFWWindow::setSwapInterval(const int& syncInterval) {
////GLFW_GL_SetSwapInterval(syncInterval);
}

void GLFWWindow::swapWindow() {
////GLFW_GL_SwapWindow(m_GLFWWindow);
}

void GLFWWindow::initializeGLFW() {
////unsigned int flags = GLFW_INIT_VIDEO;
////assert(GLFW_Init(flags) == 0);
}

void GLFWWindow::initializeOpenGL() {
/*
	GLFW_GL_SetAttribute(GLFW_GL_RED_SIZE, 2);
	GLFW_GL_SetAttribute(GLFW_GL_GREEN_SIZE, 2);
	GLFW_GL_SetAttribute(GLFW_GL_BLUE_SIZE, 2);
	GLFW_GL_SetAttribute(GLFW_GL_ALPHA_SIZE, 2);
	GLFW_GL_SetAttribute(GLFW_GL_BUFFER_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_DOUBLEBUFFER, 1);
	GLFW_GL_SetAttribute(GLFW_GL_DEPTH_SIZE, 24);
	GLFW_GL_SetAttribute(GLFW_GL_STENCIL_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_ACCUM_RED_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_ACCUM_GREEN_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_ACCUM_BLUE_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_ACCUM_ALPHA_SIZE, 0);
	GLFW_GL_SetAttribute(GLFW_GL_STEREO, 0);
#if not defined(__linux__)
	GLFW_GL_SetAttribute(GLFW_GL_MULTISAMPLEBUFFERS, 1);
	GLFW_GL_SetAttribute(GLFW_GL_MULTISAMPLESAMPLES, 32);
#endif // not defined(__linux__)
	GLFW_GL_SetAttribute(GLFW_GL_ACCELERATED_VISUAL, 1);
	GLFW_GL_SetAttribute(GLFW_GL_RETAINED_BACKING, 0);
#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_MAJOR_VERSION, CONTEXT_MAJOR_VERSION);
	GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_MINOR_VERSION, CONTEXT_MINOR_VERSION);
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_EGL, 0);
	GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_FLAGS, GLFW_GL_CONTEXT_DEBUG_FLAG | GLFW_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | GLFW_GL_CONTEXT_ROBUST_ACCESS_FLAG | GLFW_GL_CONTEXT_RESET_ISOLATION_FLAG);
	GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_PROFILE_MASK, GLFW_GL_CONTEXT_PROFILE_CORE);
	GLFW_GL_SetAttribute(GLFW_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
	GLFW_GL_SetAttribute(GLFW_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);

	// Create Window
	m_GLFWWindow = GLFW_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, GLFW_WINDOW_OPENGL | GLFW_WINDOW_RESIZABLE | GLFW_WINDOW_ALLOW_HIGHDPI);
	if (m_GLFWWindow == NULL) {
		printf("GLFW_CreateWindow Error: %s\n", GLFW_GetError());
		assert(m_GLFWWindow != NULL);
	}

#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	// Create Context
	m_GLFWContext = GLFW_GL_CreateContext(m_GLFWWindow);
	if (m_GLFWContext == NULL) {
		printf("GLFW_GL_CreateContext Error: %s\n", GLFW_GetError());
		assert(m_GLFWContext != NULL);
	} else {
		std::cout << "OpenGL context: " << CONTEXT_MAJOR_VERSION << "." CONTEXT_MINOR_VERSION << std::endl;
	}
#else
	// Create Context
	const int major[] = { 4, 4, 4, 4, 4, 4, 3, 3, 3, 3 };
	const int minor[] = { 5, 4, 3, 2, 1, 0, 3, 2, 1, 0 };
	int index = 0;
	for (index = 0; index < 10; ++index) {
		GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_MAJOR_VERSION, major[index]);
		GLFW_GL_SetAttribute(GLFW_GL_CONTEXT_MINOR_VERSION, minor[index]);
		m_GLFWContext = GLFW_GL_CreateContext(m_GLFWWindow);
		if (m_GLFWContext != NULL) {
			break;
		}
	}
	if (m_GLFWContext == NULL) {
		printf("GLFW_GL_CreateContext Error: %s\n", GLFW_GetError());
		assert(m_GLFWContext != NULL);
	} else {
		std::cout << "OpenGL context: " << major[index] << "." << minor[index] << std::endl;
	}
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)

	// Set Context to Current
	GLFW_GL_MakeCurrent(m_GLFWWindow, m_GLFWContext);

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

	int videoDrivers = GLFW_GetNumVideoDrivers();
	std::cout << "Video Drivers: " << videoDrivers << std::endl;

	const std::string currentVideoDriver(GLFW_GetCurrentVideoDriver());
	for (int i = 0; i < videoDrivers; ++i) {
		const std::string videoDriver(GLFW_GetVideoDriver(i));
		std::cout << "Video Driver " << i << ": " << videoDriver;
		if (currentVideoDriver == videoDriver) {
			std::cout << " [Current]";
		}
		std::cout << std::endl;
	}

	int renderDrivers = GLFW_GetNumRenderDrivers();
	std::cout << "Render Drivers: " << renderDrivers << std::endl;

	GLFW_RendererInfo info;
	for (int i = 0; i < renderDrivers; ++i) {
		GLFW_GetRenderDriverInfo(i, &info);
		std::cout << "Render Driver " << i << ": " << info.name;

		bool isSoftware = info.flags & GLFW_RENDERER_SOFTWARE;
		bool isHardware = info.flags & GLFW_RENDERER_ACCELERATED;
		bool isVSyncEnabled = info.flags & GLFW_RENDERER_PRESENTVSYNC;
		bool isTargetTexture = info.flags & GLFW_RENDERER_TARGETTEXTURE;

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
*/
}

void GLFWWindow::deinitializeGLFW() {
////GLFW_Quit();
}

void GLFWWindow::deinitializeOpenGL() {
/*
	if (m_GLFWWindow != NULL) {
		GLFW_DestroyWindow(m_GLFWWindow);
	}
*/
}

void GLFWWindow::handleWindowEvent() {
/*
	switch (m_GLFWEvent.window.event) {
		case GLFW_WINDOWEVENT_MOVED:
			onMove(m_GLFWEvent.window.data1, m_GLFWEvent.window.data2);
			break;
		case GLFW_WINDOWEVENT_RESIZED:
		case GLFW_WINDOWEVENT_SIZE_CHANGED:
			onResize(m_GLFWEvent.window.data1, m_GLFWEvent.window.data2);
			break;
		case GLFW_WINDOWEVENT_MINIMIZED:
			onMinimize();
			break;
		case GLFW_WINDOWEVENT_MAXIMIZED:
			onMaximize();
			break;
		case GLFW_WINDOWEVENT_RESTORED:
			onRestore();
			break;
		case GLFW_WINDOWEVENT_SHOWN:
			onDisplay();
			break;
		default:
			break;
	}
*/
}

void GLFWWindow::handleKeyUpEvent() {
/*
	switch (m_GLFWEvent.key.keysym.sym) {
		case GLFWK_ESCAPE:
			break;
		default:
			break;
	}
*/
}

void GLFWWindow::handleKeyDownEvent() {
/*
	const float increment = 0.50f;
	switch (m_GLFWEvent.key.keysym.sym) {
		case GLFWK_ESCAPE:
			m_active = false;
			break;
		case GLFWK_UP:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(0, 0, increment));
		}
			break;
		case GLFWK_DOWN:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(0, 0, -increment));
		}
			break;
		case GLFWK_RIGHT:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(increment, 0, 0));
		}
			break;
		case GLFWK_LEFT:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(-increment, 0, 0));
		}
			break;
		default:
			break;
	}
*/
}
