//
//  Renderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Renderer.h"

//namespace Engine
//{

Renderer::Renderer(const int& width, const int& height)
: m_width(width)
, m_height(height)
, m_clearColor(Gray)
, m_clearDepth(10)
, m_clearStencil(10) {
}

Renderer::~Renderer() {
    m_width = 0;
    m_height = 0;
}

void Renderer::setType(const Type& type) {
	m_type = type;
}

Renderer::Type Renderer::getType() {
	return m_type;
}

void Renderer::setWidth(const int& width) {
    m_width = width;
}

int Renderer::getWidth() {
    return m_width;
}

void Renderer::setHeight(const int& height) {
    m_height = height;
}

int Renderer::getHeight() {
    return m_height;
}

void Renderer::setWindow(AbstractWindow* const window) {
    m_window = window;
}

AbstractWindow* Renderer::getWindow() const {
    return m_window;
}

//}
