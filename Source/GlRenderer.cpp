//
//  GlRenderer.cpp
//  Application
//
//  Created by Narendra Umate on 9/7/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#if defined(__APPLE__) || defined(__linux__)

#include "GlRenderer.h"

//namespace Engine
//{

GlRenderer::GlRenderer(const int& width, const int& height)
: Renderer(width, height) {
	m_type = GL;
}

GlRenderer::~GlRenderer() {
}

void GlRenderer::initialize() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); // GL_CW or GL_CCW
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL or GL_LINE
}

void GlRenderer::deinitialize() {
}

void GlRenderer::setClearColor(const Color4f& clearColor) {
    m_clearColor = clearColor;
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
}

Color4f GlRenderer::getClearColor() const {
    return m_clearColor;
}

void GlRenderer::setClearDepth(const float& clearDepth) {
    m_clearDepth = clearDepth;
    glClearDepth(m_clearDepth);
}

float GlRenderer::getClearDepth() const {
    return m_clearDepth;
}

void GlRenderer::setClearStencil(const unsigned int& clearStencil) {
    m_clearStencil = clearStencil;
    glClearStencil(m_clearStencil);
}

unsigned int GlRenderer::getClearStencil() const {
    return m_clearStencil;
}

void GlRenderer::setViewport(const int& xPos, const int& yPos, const int& w, const int& h) {
    glViewport(xPos, yPos, w, h);
}

void GlRenderer::getViewport(int& xPos, int& yPos, int& w, int& h) const {
    int params[4];
    glGetIntegerv(GL_VIEWPORT, params);
    xPos = params[0];
    yPos = params[1];
    w = params[2];
    h = params[3];
}

void GlRenderer::setDepthRange(const float& zMin, const float& zMax) {
    glDepthRange(zMin, zMax);
}

void GlRenderer::getDepthRange(float& zMin, float& zMax) const {
    int params[2];
    glGetIntegerv(GL_DEPTH_RANGE, params);
    zMin = params[0];
    zMax = params[1];
}

void GlRenderer::setSize(const int& width, const int& height) {
    m_width = width;
    m_height = height;
    int params[4];
    glGetIntegerv(GL_VIEWPORT, params);
    glViewport(params[0], params[1], width, height);
}

void GlRenderer::getSize(int& width, int& height) {
    width = m_width;
    height = m_height;
}

void GlRenderer::clearColorBuffer() {
    //glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void GlRenderer::clearDepthBuffer() {
    //glClearDepth(m_clearDepth);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void GlRenderer::clearStencilBuffer() {
    //glClearStencil(m_clearStencil);
    glClear(GL_STENCIL_BUFFER_BIT);
}

void GlRenderer::clearBuffers() {
    //glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    //glClearDepth(m_clearDepth);
    //glClearStencil(m_clearStencil);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GlRenderer::clearColorBuffer(const int& x, const int& y, const int& w, const int& h) {
    //glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}

void GlRenderer::clearDepthBuffer(const int& x, const int& y, const int& w, const int& h) {
    //glClearDepth(m_clearDepth);
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, w, h);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}

void GlRenderer::clearStencilBuffer(const int& x, const int& y, const int& w, const int& h) {
    //glClearStencil(m_clearStencil);
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, w, h);
    glClear(GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}

void GlRenderer::clearBuffers(const int& x, const int& y, const int& w, const int& h) {
    //glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    //glClearDepth(m_clearDepth);
    //glClearStencil(m_clearStencil);
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, w, h);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
}

void GlRenderer::displayColorBuffer(const int& syncInterval) {
	m_window->setSwapInterval(syncInterval);
	m_window->swapWindow();
}

void GlRenderer::draw(VisualSpatial* visual) {
    VisualEffect* vEffect = visual->getVisualEffect();
    VertexBuffer* vBuffer = visual->getVertexBuffer();
    IndexBuffer* iBuffer = visual->getIndexBuffer();
	Material* material = visual->getMaterial();
    if (vEffect && vBuffer && iBuffer && material) {
        // Set Program
        GLuint program = vEffect->getProgram()->getProgram();
        glUseProgram(program);
        // Set World View Norm Matrix
        GLint worldViewNormMatrixLocation = glGetUniformLocation(program, "worldViewNorm");
        glUniformMatrix3fv(worldViewNormMatrixLocation, 1, GL_FALSE, (float*)&(visual->getWorldViewNormMatrix()));
        // Set World View Projection Matrix.
        GLint worldViewProjectionMatrixLocation = glGetUniformLocation(program, "worldViewProjection");
        glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, (float*)&(visual->getWorldViewProjectionMatrix()));
		// Set Parameters
		vEffect->getProgram()->set3fv("ambient", 1, material->ambient);
		vEffect->getProgram()->set3fv("diffuse", 1, material->diffuse);
		vEffect->getProgram()->set3fv("specular", 1, material->specular);
		vEffect->getProgram()->set3fv("transmittance", 1, material->transmittance);
		vEffect->getProgram()->set3fv("emission", 1, material->emission);
		vEffect->getProgram()->set1f("shininess", material->shininess);
		vEffect->getProgram()->set1f("ior", material->ior);
		// Bind
		vBuffer->bind();
		iBuffer->bind();
		material->enable();
		// Draw
		glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		// Unbind
		material->disable();
		iBuffer->unbind();
		vBuffer->unbind();
        // Unset Program
        glUseProgram(0);
    }
}

void GlRenderer::draw(BoundingBox* boundingBox) {
	// Hack
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL or GL_LINE

	VisualEffect* vEffect = BoundingBox::visualEffect;
	VertexBuffer* vBuffer = 0; // TODO Populate
	IndexBuffer* iBuffer = 0; // TODO Populate

    if (vEffect && vBuffer && iBuffer) {
		// Set Program
		GLuint program = BoundingBox::visualEffect->getProgram()->getProgram();
		glUseProgram(program);
		// Set World View Norm Matrix
		Mat3 viewNorm = getWindow()->getCamera()->getViewNormMatrix();
		GLint worldViewNormMatrixLocation = glGetUniformLocation(program, "worldViewNorm");
		glUniformMatrix3fv(worldViewNormMatrixLocation, 1, GL_FALSE, (float*)&(viewNorm));
		// Set World View Projection Matrix.
		Mat4 viewProjection = getWindow()->getCamera()->getViewProjectionMatrix();
		GLint worldViewProjectionMatrixLocation = glGetUniformLocation(program, "worldViewProjection");
		glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, (float*)&(viewProjection));
		// Bind
		vBuffer->bind();
		iBuffer->bind();
		// Draw
		glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		// Unbind
		vBuffer->bind();
		iBuffer->bind();
		// Unset Program
		glUseProgram(0);
	}

	// Hack
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL or GL_LINE
}

//}

#endif // defined(__APPLE__) || defined(__linux__)
