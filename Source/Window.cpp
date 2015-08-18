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
,	m_ySize(parameters.ySize) {
/*
	SDL_Init(SDL_INIT_VIDEO);
	sdlWindow = SDL_CreateWindow(m_title.c_str(), m_xOrigin, m_yOrigin, m_xSize, m_ySize, SDL_WINDOW_OPENGL);
	if (sdlWindow == 0) {
		std::fprintf(stderr, "sdlWindow == 0");
	}
*/
}

Window::~Window() {
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

void Window::onDisplay() {
}

void Window::onIdle() {
}
