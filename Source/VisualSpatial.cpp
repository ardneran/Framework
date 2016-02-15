//
//  VisualSpatial.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "VisualSpatial.h"

VisualSpatial::VisualSpatial()
: m_vertexBuffer(new VertexBuffer())
, m_indexBuffer(new IndexBuffer())
, m_visualEffect(NULL)
, m_modelBoundingBox() {
}

VisualSpatial::~VisualSpatial() {
    if (m_vertexBuffer) {
        m_vertexBuffer->deinitialize();
        delete m_vertexBuffer;
    }
    if (m_indexBuffer) {
        m_indexBuffer->deinitialize();
        delete m_indexBuffer;
    }
}

void VisualSpatial::update() {
}

void VisualSpatial::updateWorldBoundingBox() {
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform.getStraightMatrix());
}

void VisualSpatial::updateWorldViewMatrix() {
    m_worldViewMatrix = m_viewMatrix * m_worldTransform.getStraightMatrix();
}

void VisualSpatial::updateWorldViewProjectionMatrix() {
    m_worldViewProjectionMatrix = m_viewProjectionMatrix * m_worldTransform.getStraightMatrix();
}

void VisualSpatial::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setViewMatrix(const Mat4& viewMatrix) {
    if (m_viewMatrix != viewMatrix) {
        m_viewMatrix = viewMatrix;
        updateWorldViewMatrix();
    }
}

void VisualSpatial::setViewProjectionMatrix(const Mat4& viewProjectionMatrix) {
    if (m_viewProjectionMatrix != viewProjectionMatrix) {
        m_viewProjectionMatrix = viewProjectionMatrix;
        updateWorldViewProjectionMatrix();
    }
}
