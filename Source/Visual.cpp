//
//  Visual.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "Visual.h"

Visual::Visual()
: m_vertexBuffer(new VertexBuffer())
, m_indexBuffer(new IndexBuffer())
, m_visualEffect(NULL)
, m_modelBoundingBox() {
}

Visual::~Visual() {
}

void Visual::update() {
}

void Visual::updateWorldBoundingBox() {
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform.getStraightMatrix());
}

void Visual::updateWorldViewMatrix() {
    m_worldViewMatrix = m_viewMatrix * m_worldTransform.getStraightMatrix();
}

void Visual::updateWorldViewProjectionMatrix() {
    m_worldViewProjectionMatrix = m_viewProjectionMatrix * m_worldTransform.getStraightMatrix();
}

void Visual::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void Visual::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void Visual::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateWorldBoundingBox();
    updateWorldViewMatrix();
    updateWorldViewProjectionMatrix();
}

void Visual::setViewMatrix(const Mat4& viewMatrix) {
    if (m_viewMatrix != viewMatrix) {
        m_viewMatrix = viewMatrix;
        updateWorldViewMatrix();
    }
}

void Visual::setViewProjectionMatrix(const Mat4& viewProjectionMatrix) {
    if (m_viewProjectionMatrix != viewProjectionMatrix) {
        m_viewProjectionMatrix = viewProjectionMatrix;
        updateWorldViewProjectionMatrix();
    }
}
