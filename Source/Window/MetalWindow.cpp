//
//  MetalWindow.cpp
//
//
//  Created by Narendra Umate on 8/17/15.
//
//

#include "MetalWindow.h"

MetalWindow::MetalWindow(Parameters& parameters)
: AbstractWindow(parameters) {
	initializeNative();
	switch (m_renderer->getType()) {
		case Renderer::DX:
			break;
		case Renderer::Metal:
			initializeMetal();
		default:
			break;
	}
	m_renderer->initialize(); // Called here after the context is created.
}

MetalWindow::~MetalWindow() {
	m_renderer->deinitialize(); // Called here before the context is destroyed.
    switch (m_renderer->getType()) {
        case Renderer::DX:
            break;
        case Renderer::Metal:
            deinitializeMetal();
        default:
            break;
    }
	deinitializeNative();
}

void MetalWindow::handlePollEvent() {
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

void MetalWindow::setSwapInterval(const int& syncInterval) {
////Native_GL_SetSwapInterval(syncInterval);
}

void MetalWindow::swapWindow() {
////Native_GL_SwapWindow(m_MetalWindow);
}

void MetalWindow::initializeNative() {
////unsigned int flags = Native_INIT_VIDEO;
////assert(Native_Init(flags) == 0);
}

void MetalWindow::initializeMetal() {
}

void MetalWindow::deinitializeNative() {
////Native_Quit();
}

void MetalWindow::deinitializeMetal() {
}

void MetalWindow::handleWindowEvent() {
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

void MetalWindow::handleKeyUpEvent() {
/*
	switch (m_nativeEvent.key.keysym.sym) {
		case NativeK_ESCAPE:
			break;
		default:
			break;
	}
*/
}

void MetalWindow::handleKeyDownEvent() {
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
