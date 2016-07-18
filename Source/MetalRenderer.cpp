//
//  MetalRenderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#if defined(__APPLE__)

#include "MetalRenderer.h"

//namespace Engine
//{

MetalRenderer::MetalRenderer(const int& width, const int& height)
: Renderer(width, height) {
	m_type = Metal;
}

MetalRenderer::~MetalRenderer() {
}

void MetalRenderer::initialize() {
}

void MetalRenderer::deinitialize() {
}

void MetalRenderer::setClearColor(const Color4f& clearColor) {
    m_clearColor = clearColor;
}

Color4f MetalRenderer::getClearColor() const {
    return m_clearColor;
}

void MetalRenderer::setClearDepth(const float& clearDepth) {
    m_clearDepth = clearDepth;
}

float MetalRenderer::getClearDepth() const {
    return m_clearDepth;
}

void MetalRenderer::setClearStencil(const unsigned int& clearStencil) {
    m_clearStencil = clearStencil;
}

unsigned int MetalRenderer::getClearStencil() const {
    return m_clearStencil;
}

void MetalRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h) {
}

void MetalRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const {
}

void MetalRenderer::setDepthRange(const float& zMin, const float& zMax) {
}

void MetalRenderer::getDepthRange(float& zMin, float& zMax) const {
}

void MetalRenderer::setSize(const int& width, const int& height) {
}

void MetalRenderer::getSize(int& width, int& height) {
}

void MetalRenderer::clearColorBuffer() {
}

void MetalRenderer::clearDepthBuffer() {
}

void MetalRenderer::clearStencilBuffer() {
}

void MetalRenderer::clearBuffers() {
}

void MetalRenderer::clearColorBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void MetalRenderer::clearDepthBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void MetalRenderer::clearStencilBuffer(const int& x, const int& y, const int& w, const int& h) {
}

void MetalRenderer::clearBuffers(const int& x, const int& y, const int& w, const int& h) {
}

void MetalRenderer::displayColorBuffer(const int& syncInterval) {
}

void MetalRenderer::draw(VisualSpatial* visual) {
}

void MetalRenderer::draw(BoundingBox* boundingBox) {
}

//}

#endif // defined(__APPLE__)
