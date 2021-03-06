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

DxRenderer::DxRenderer(const int& width, const int& height)
: Renderer(width, height) {
	m_type = DX;
}

DxRenderer::~DxRenderer() {
}

void DxRenderer::initialize() {
}

void DxRenderer::deinitialize() {
}

void DxRenderer::setClearColor(const Color4f& clearColor) {
    m_clearColor = clearColor;
}

Color4f DxRenderer::getClearColor() const {
    return m_clearColor;
}

void DxRenderer::setClearDepth(const float& clearDepth) {
    m_clearDepth = clearDepth;
}

float DxRenderer::getClearDepth() const {
    return m_clearDepth;
}

void DxRenderer::setClearStencil(const unsigned int& clearStencil) {
    m_clearStencil = clearStencil;
}

unsigned int DxRenderer::getClearStencil() const {
    return m_clearStencil;
}

void DxRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h) {
}

void DxRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const {
}

void DxRenderer::setDepthRange(const float& zMin, const float& zMax) {
}

void DxRenderer::getDepthRange(float& zMin, float& zMax) const {
}

void DxRenderer::setSize(const int& width, const int& height) {
}

void DxRenderer::getSize(int& width, int& height) {
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

void DxRenderer::draw(VisualSpatial* visual, const Vec3& lightColor, const Vec3& lightPosition, const Vec3& eyePosition) {
}

VisualEffect* DxRenderer::createVisualEffect(const std::string& vsfilename, const std::string& fsfilename) {
    return nullptr;
}

void DxRenderer::destroyVisualEffect(VisualEffect* visualEffect) {
    // do nothing
}

//}

#endif // defined(_WIN32)
