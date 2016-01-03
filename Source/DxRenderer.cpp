//
//  DxRenderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#if defined(_WIN32)

#include "DxRenderer.h"

//namespace Engine
//{

DxRenderer::DxRenderer()
: Renderer() {
}

DxRenderer::~DxRenderer() {
}

void DxRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h) {
}

void DxRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const {
}

void DxRenderer::setDepthRange(const float& zMin, const float& zMax) {
}

void DxRenderer::getDepthRange(float& zMin, float& zMax) const {
}

void DxRenderer::resize(const int& width, const int& height) {
}

void DxRenderer::clearColorBuffer() {
}

void DxRenderer::clearDepthBuffer() {
}

void DxRenderer::clearStencilBuffer() {
}

void DxRenderer::clearBuffers() {
}

void DxRenderer::clearColorBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void DxRenderer::clearDepthBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void DxRenderer::clearStencilBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void DxRenderer::clearBuffers(const int& x, const int& y, const int& w, const int& h) {
}

void DxRenderer::displayColorBuffer(const int& syncInterval) {
}

//}

#endif // defined(_WIN32)
