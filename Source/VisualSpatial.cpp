//
//  VisualSpatial.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "VisualSpatial.h"

VisualSpatial::VisualSpatial(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texcoords, const std::vector<unsigned int>& indices)
: m_visualEffect(NULL)
, m_vertexBuffer(new VertexBuffer(positions, normals, texcoords))
, m_indexBuffer(new IndexBuffer(indices))
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
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform);
}

void VisualSpatial::updateWorldViewNormMatrix() {
	m_worldViewNormMatrix = Mat3(m_viewMatrix * m_worldTransform.getMatrix()).inverse().transpose();
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
