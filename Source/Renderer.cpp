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

Renderer::Renderer()
: m_width(0)
, m_height(0)
, m_clearColor(Color4f(0.5f, 0.5f, 0.5f, 1.0f))
, m_clearDepth(10)
, m_clearStencil(10) {
}

Renderer::~Renderer() {
    m_width = 0;
    m_height = 0;
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

void Renderer::setClearColor(const Color4f& clearColor) {
    m_clearColor = clearColor;
}

Color4f Renderer::getClearColor() const {
    return m_clearColor;
}

void Renderer::setClearDepth(const float& clearDepth) {
    m_clearDepth = clearDepth;
}

float Renderer::getClearDepth() const {
    return m_clearDepth;
}

void Renderer::setClearStencil(const unsigned int& clearStencil) {
    m_clearStencil = clearStencil;
}

unsigned int Renderer::getClearStencil() const {
    return m_clearStencil;
}

void Renderer::setWindow(void* const window) {
    m_window = window;
}

void* Renderer::getWindow() const {
    return m_window;
}

//}
