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
	SDL_Init(SDL_INIT_VIDEO);
	sdlWindow = SDL_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (sdlWindow == 0) {
		std::fprintf(stderr, "sdlWindow == 0");
	}
}

Window::~Window() {
	if (sdlWindow != 0) {
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
	}
}

void Window::onMove(const int& x, const int& y) {
	m_xOrigin = x;
	m_yOrigin = y;
}

bool Window::onResize(const int& xSize, const int& ySize) {
	m_minimized = false;
	m_maximized = false;
	if (xSize != m_xSize || ySize != m_ySize) {
		m_xSize = xSize;
		m_ySize = ySize;
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
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		handleEvent(event);
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

