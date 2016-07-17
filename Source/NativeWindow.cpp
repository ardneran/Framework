//
//  NativeWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "NativeWindow.h"

NativeWindow::NativeWindow(Parameters& parameters)
: AbstractWindow(parameters) {
	initializeNative();
	initializeOpenGL();
	m_renderer->initialize(); // Called here after the context is created.
}

NativeWindow::~NativeWindow() {
	m_renderer->deinitialize(); // Called here before the context is destroyed.
	deinitializeOpenGL();
	deinitializeNative();
}

void NativeWindow::handlePollEvent() {
/*
	while (Native_PollEvent(&m_nativeEvent)) {
		switch (m_nativeEvent.type) {
			case Native_WINDOWEVENT: {
				handleWindowEvent();
			} break;
			case Native_KEYUP: {
				handleKeyUpEvent();
			} break;
			case Native_KEYDOWN: {
				handleKeyDownEvent();
			} break;
			case Native_QUIT: {
				m_active = false;
			} break;
		}
	}
*/
}

void NativeWindow::setSwapInterval(const int& syncInterval) {
////Native_GL_SetSwapInterval(syncInterval);
}

void NativeWindow::swapWindow() {
////Native_GL_SwapWindow(m_nativeWindow);
}

void NativeWindow::initializeNative() {
////unsigned int flags = Native_INIT_VIDEO;
////assert(Native_Init(flags) == 0);
}

void NativeWindow::initializeOpenGL() {
/*
	Native_GL_SetAttribute(Native_GL_RED_SIZE, 2);
	Native_GL_SetAttribute(Native_GL_GREEN_SIZE, 2);
	Native_GL_SetAttribute(Native_GL_BLUE_SIZE, 2);
	Native_GL_SetAttribute(Native_GL_ALPHA_SIZE, 2);
	Native_GL_SetAttribute(Native_GL_BUFFER_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_DOUBLEBUFFER, 1);
	Native_GL_SetAttribute(Native_GL_DEPTH_SIZE, 24);
	Native_GL_SetAttribute(Native_GL_STENCIL_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_ACCUM_RED_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_ACCUM_GREEN_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_ACCUM_BLUE_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_ACCUM_ALPHA_SIZE, 0);
	Native_GL_SetAttribute(Native_GL_STEREO, 0);
#if not defined(__linux__)
	Native_GL_SetAttribute(Native_GL_MULTISAMPLEBUFFERS, 1);
	Native_GL_SetAttribute(Native_GL_MULTISAMPLESAMPLES, 32);
#endif // not defined(__linux__)
	Native_GL_SetAttribute(Native_GL_ACCELERATED_VISUAL, 1);
	Native_GL_SetAttribute(Native_GL_RETAINED_BACKING, 0);
#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	Native_GL_SetAttribute(Native_GL_CONTEXT_MAJOR_VERSION, CONTEXT_MAJOR_VERSION);
	Native_GL_SetAttribute(Native_GL_CONTEXT_MINOR_VERSION, CONTEXT_MINOR_VERSION);
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	Native_GL_SetAttribute(Native_GL_CONTEXT_EGL, 0);
	Native_GL_SetAttribute(Native_GL_CONTEXT_FLAGS, Native_GL_CONTEXT_DEBUG_FLAG | Native_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG | Native_GL_CONTEXT_ROBUST_ACCESS_FLAG | Native_GL_CONTEXT_RESET_ISOLATION_FLAG);
	Native_GL_SetAttribute(Native_GL_CONTEXT_PROFILE_MASK, Native_GL_CONTEXT_PROFILE_CORE);
	Native_GL_SetAttribute(Native_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
	Native_GL_SetAttribute(Native_GL_FRAMEBUFFER_SRGB_CAPABLE, 0);

	// Create Window
	m_nativeWindow = Native_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, Native_WINDOW_OPENGL | Native_WINDOW_RESIZABLE | Native_WINDOW_ALLOW_HIGHDPI);
	if (m_nativeWindow == NULL) {
		printf("Native_CreateWindow Error: %s\n", Native_GetError());
		assert(m_nativeWindow != NULL);
	}

#if defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)
	// Create Context
	m_nativeContext = Native_GL_CreateContext(m_nativeWindow);
	if (m_nativeContext == NULL) {
		printf("Native_GL_CreateContext Error: %s\n", Native_GetError());
		assert(m_nativeContext != NULL);
	} else {
		std::cout << "OpenGL context: " << CONTEXT_MAJOR_VERSION << "." CONTEXT_MINOR_VERSION << std::endl;
	}
#else
	// Create Context
	const int major[] = { 4, 4, 4, 4, 4, 4, 3, 3, 3, 3 };
	const int minor[] = { 5, 4, 3, 2, 1, 0, 3, 2, 1, 0 };
	int index = 0;
	for (index = 0; index < 10; ++index) {
		Native_GL_SetAttribute(Native_GL_CONTEXT_MAJOR_VERSION, major[index]);
		Native_GL_SetAttribute(Native_GL_CONTEXT_MINOR_VERSION, minor[index]);
		m_nativeContext = Native_GL_CreateContext(m_nativeWindow);
		if (m_nativeContext != NULL) {
			break;
		}
	}
	if (m_nativeContext == NULL) {
		printf("Native_GL_CreateContext Error: %s\n", Native_GetError());
		assert(m_nativeContext != NULL);
	} else {
		std::cout << "OpenGL context: " << major[index] << "." << minor[index] << std::endl;
	}
#endif // defined(CONTEXT_MAJOR_VERSION) && defined(CONTEXT_MINOR_VERSION)

	// Set Context to Current
	Native_GL_MakeCurrent(m_nativeWindow, m_nativeContext);

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

	int videoDrivers = Native_GetNumVideoDrivers();
	std::cout << "Video Drivers: " << videoDrivers << std::endl;

	const std::string currentVideoDriver(Native_GetCurrentVideoDriver());
	for (int i = 0; i < videoDrivers; ++i) {
		const std::string videoDriver(Native_GetVideoDriver(i));
		std::cout << "Video Driver " << i << ": " << videoDriver;
		if (currentVideoDriver == videoDriver) {
			std::cout << " [Current]";
		}
		std::cout << std::endl;
	}

	int renderDrivers = Native_GetNumRenderDrivers();
	std::cout << "Render Drivers: " << renderDrivers << std::endl;

	Native_RendererInfo info;
	for (int i = 0; i < renderDrivers; ++i) {
		Native_GetRenderDriverInfo(i, &info);
		std::cout << "Render Driver " << i << ": " << info.name;

		bool isSoftware = info.flags & Native_RENDERER_SOFTWARE;
		bool isHardware = info.flags & Native_RENDERER_ACCELERATED;
		bool isVSyncEnabled = info.flags & Native_RENDERER_PRESENTVSYNC;
		bool isTargetTexture = info.flags & Native_RENDERER_TARGETTEXTURE;

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
*/
}

void NativeWindow::deinitializeNative() {
////Native_Quit();
}

void NativeWindow::deinitializeOpenGL() {
/*
	if (m_nativeWindow != NULL) {
		Native_DestroyWindow(m_nativeWindow);
	}
*/
}

void NativeWindow::handleWindowEvent() {
/*
	switch (m_nativeEvent.window.event) {
		case Native_WINDOWEVENT_MOVED:
			onMove(m_nativeEvent.window.data1, m_nativeEvent.window.data2);
			break;
		case Native_WINDOWEVENT_RESIZED:
		case Native_WINDOWEVENT_SIZE_CHANGED:
			onResize(m_nativeEvent.window.data1, m_nativeEvent.window.data2);
			break;
		case Native_WINDOWEVENT_MINIMIZED:
			onMinimize();
			break;
		case Native_WINDOWEVENT_MAXIMIZED:
			onMaximize();
			break;
		case Native_WINDOWEVENT_RESTORED:
			onRestore();
			break;
		case Native_WINDOWEVENT_SHOWN:
			onDisplay();
			break;
		default:
			break;
	}
*/
}

void NativeWindow::handleKeyUpEvent() {
/*
	switch (m_nativeEvent.key.keysym.sym) {
		case NativeK_ESCAPE:
			break;
		default:
			break;
	}
*/
}

void NativeWindow::handleKeyDownEvent() {
/*
	const float increment = 0.50f;
	switch (m_nativeEvent.key.keysym.sym) {
		case NativeK_ESCAPE:
			m_active = false;
			break;
		case NativeK_UP:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(0, 0, increment));
		}
			break;
		case NativeK_DOWN:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(0, 0, -increment));
		}
			break;
		case NativeK_RIGHT:
		{
			Vec3 position;
			m_camera->getPosition(position);
			m_camera->setPosition(position + Vec3(increment, 0, 0));
		}
			break;
		case NativeK_LEFT:
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
