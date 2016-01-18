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

GlRenderer::GlRenderer()
: Renderer() {
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
    SDL_GL_SetSwapInterval(syncInterval);
    SDL_GL_SwapWindow(static_cast<SDL_Window*>(m_window));
}

void GlRenderer::draw(Visual* visual) {
    VertexBuffer* vBuffer = visual->getVertexBuffer();
    IndexBuffer* iBuffer = visual->getIndexBuffer();
    VisualEffect* vEffect = visual->getVisualEffect();
    if (vBuffer != NULL && iBuffer != NULL && vEffect != NULL) {
        // Set Program
        GLuint program = vEffect->getProgram()->getProgram();
        glUseProgram(program);
        // Set World View Matrix
        GLint worldViewMatrixLocation = glGetUniformLocation(program, "worldView");
        glUniformMatrix3fv(worldViewMatrixLocation, 1, GL_FALSE, (float*)&(visual->getWorldViewMatrix()));
        // Set World View Projection Matrix
        GLint worldViewProjectionMatrixLocation = glGetUniformLocation(program, "worldViewProjection");
        glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, (float*)&(visual->getWorldViewProjectionMatrix()));
        draw(vBuffer, iBuffer, vEffect);
        // Unset Program
        glUseProgram(0);
    }
}

void GlRenderer::draw(VertexBuffer* vBuffer, IndexBuffer* iBuffer, VisualEffect* vEffect) {
    // Bind
    vBuffer->bind();
    iBuffer->bind();
    // Draw
    glDrawElements(GL_TRIANGLES, iBuffer->getCount(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    // Unbind
    iBuffer->unbind();
    vBuffer->unbind();
}

// TODO FIX THIS FUNCTION AS SOON AS POSSIBLE TERRIBLE LEAKS HERE
/*void GlRenderer::draw(Visual* visual) {
    GLuint program = visual->getProgram()->getProgram();
    glUseProgram(program);
    //------------------------------------------------------------------------//
    // Push World View Projection Matrix
    Mat4 worldViewProjectionMatrix = visual->getWorldViewProjectionMatrix();
    GLint worldViewProjectionMatrixLocation = glGetUniformLocation(program, "worldViewProjection");
    glUniformMatrix4fv(worldViewProjectionMatrixLocation, 1, GL_FALSE, (float*)&(worldViewProjectionMatrix));
    //------------------------------------------------------------------------//
    // One Time Setup
    enum Ebo { EboTriangles,
               EboCount };
    enum Vao { VaoTriangles,
               VaoCount };
    enum Vbo { VboTriangles,
               VboCount };

    enum AttributeType { AttributePosition,
                         AttributeNormal,
                         AttributeTexcoord,
                         AttributeCount };
    enum TextureType { TextureAmbient,
                       TextureDiffuse,
                       TextureSpecular,
                       TextureNormal,
                       TextureCount };

    GLuint m_ebos[EboCount];
    GLuint m_vaos[VaoCount];
    GLuint m_vbos[VboCount];

    const float* positions = visual->getPositions();
    const float* normals = visual->getNormals();
    const float* texcoords = visual->getTextureCoordinates();
    const unsigned int* indices = visual->getIndices();

    const unsigned int sizeOfPositions = sizeof(positions[0]) * visual->getPositionsSize();
    const unsigned int sizeOfNormals = sizeof(normals[0]) * visual->getNormalsSize();
    const unsigned int sizeOfTexcoords = sizeof(texcoords[0]) * visual->getTexcoordsSize();
    const unsigned int sizeOfIndices = sizeof(indices[0]) * visual->getIndicesSize();

    glGenBuffers(EboCount, m_ebos);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices, &indices[0], GL_STATIC_DRAW);
    //No Vertex Attrib Pointer for Index buffer

    glGenVertexArrays(VaoCount, m_vaos);
    glBindVertexArray(m_vaos[VaoTriangles]);

    glGenBuffers(VboCount, m_vbos);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbos[VboTriangles]);
    glBufferData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals + sizeOfTexcoords, NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeOfPositions, &positions[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions, sizeOfNormals, &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeOfPositions + sizeOfNormals, sizeOfTexcoords, &texcoords[0]);

    glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(sizeOfPositions));
    glVertexAttribPointer(AttributeTexcoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeOfPositions + sizeOfNormals));

    glEnableVertexAttribArray(AttributePosition);
    glEnableVertexAttribArray(AttributeNormal);
    glEnableVertexAttribArray(AttributeTexcoord);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //------------------------------------------------------------------------//
    // Draw
    glBindVertexArray(m_vaos[VaoTriangles]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebos[EboTriangles]);
    glDrawElements(GL_TRIANGLES, visual->getIndicesSize(), GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //------------------------------------------------------------------------//
    glUseProgram(0);
}*/

//}

#endif // defined(__APPLE__) || defined(__linux__)
