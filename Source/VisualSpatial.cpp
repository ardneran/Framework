//
//  VisualSpatial.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "VisualSpatial.h"

VisualSpatial::VisualSpatial()
: m_visualEffect(NULL)
, m_vertexBuffer(new VertexBuffer())
, m_indexBuffer(new IndexBuffer())
, m_material(new Material())
, m_modelBoundingBox() {
}

VisualSpatial::~VisualSpatial() {
	if (m_indexBuffer) {
		m_indexBuffer->deinitialize();
		delete m_indexBuffer;
	}
    if (m_vertexBuffer) {
        m_vertexBuffer->deinitialize();
        delete m_vertexBuffer;
    }
	if (m_material) {
		m_material->deinitialize();
		delete m_material;
	}
}

void VisualSpatial::update() {
}

void VisualSpatial::updateWorldBoundingBox() {
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform.getMatrix());
}

void VisualSpatial::updateWorldViewNormMatrix() {
    Mat4 normalMatrix = m_viewMatrix * m_worldTransform.getMatrix(); // TODO Verify if inverse transpose is needed?
    m_worldViewNormMatrix.d00 = normalMatrix.d00;
    m_worldViewNormMatrix.d01 = normalMatrix.d01;
    m_worldViewNormMatrix.d02 = normalMatrix.d02;
    m_worldViewNormMatrix.d10 = normalMatrix.d10;
    m_worldViewNormMatrix.d11 = normalMatrix.d11;
    m_worldViewNormMatrix.d12 = normalMatrix.d12;
    m_worldViewNormMatrix.d20 = normalMatrix.d20;
    m_worldViewNormMatrix.d21 = normalMatrix.d21;
    m_worldViewNormMatrix.d22 = normalMatrix.d22;
}

void VisualSpatial::updateWorldViewProjectionMatrix() {
    m_worldViewProjectionMatrix = m_viewProjectionMatrix * m_worldTransform.getMatrix();
}

void VisualSpatial::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateWorldBoundingBox();
    updateWorldViewNormMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateWorldBoundingBox();
    updateWorldViewNormMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateWorldBoundingBox();
    updateWorldViewNormMatrix();
    updateWorldViewProjectionMatrix();
}

void VisualSpatial::setViewMatrix(const Mat4& viewMatrix) {
    if (m_viewMatrix != viewMatrix) {
        m_viewMatrix = viewMatrix;
        updateWorldViewNormMatrix();
    }
}

void VisualSpatial::setViewProjectionMatrix(const Mat4& viewProjectionMatrix) {
    if (m_viewProjectionMatrix != viewProjectionMatrix) {
        m_viewProjectionMatrix = viewProjectionMatrix;
        updateWorldViewProjectionMatrix();
    }
}
