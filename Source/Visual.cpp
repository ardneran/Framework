//
//  Visual.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "Visual.h"

Visual::Visual()
: m_name(NULL)
, m_positions(NULL)
, m_normals(NULL)
, m_textureCoordinates(NULL)
, m_indices(NULL)
, m_materialIds(NULL)
, m_program(NULL)
, m_modelBoundingBox()
, m_modelNormals() {
}

Visual::~Visual() {
    if (m_name) {
        delete m_name;
    }
    if (m_positions) {
        delete m_positions;
    }
    if (m_normals) {
        delete m_normals;
    }
    if (m_textureCoordinates) {
        delete m_textureCoordinates;
    }
    if (m_indices) {
        delete m_indices;
    }
    if (m_materialIds) {
        delete m_materialIds;
    }
    if (m_program) {
        delete m_program;
    }
}

void Visual::update() {
}

void Visual::updateWorldBoundingBox() {
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform.getStraightMatrix());
}

void Visual::updateWorldNormals() {
    m_normMatrix = (m_viewMatrix * m_worldTransform.getStraightMatrix()).inverse().transpose();
    // TODO
}

void Visual::updateWorldViewProjectionMatrix() {
    m_worldViewProjectionMatrix = m_viewProjectionMatrix * m_worldTransform.getStraightMatrix();
}

void Visual::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateWorldBoundingBox();
    updateWorldNormals(); // does translate affect normals ??
    updateWorldViewProjectionMatrix();
}

void Visual::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateWorldBoundingBox();
    updateWorldNormals();
    updateWorldViewProjectionMatrix();
}

void Visual::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateWorldBoundingBox();
    updateWorldNormals();
    updateWorldViewProjectionMatrix();
}

void Visual::setViewMatrix(const Mat4& viewMatrix) {
    if (m_viewMatrix != viewMatrix) {
        m_viewMatrix = viewMatrix;
        updateWorldNormals();
    }
}

void Visual::setViewProjectionMatrix(const Mat4& viewProjectionMatrix) {
    if (m_viewProjectionMatrix != viewProjectionMatrix) {
        m_viewProjectionMatrix = viewProjectionMatrix;
        updateWorldViewProjectionMatrix();
    }
}

void Visual::setName(const std::string& name) {
    m_nameSize = name.size() + 1;
    m_name = new char[m_nameSize];
    std::strcpy(m_name, name.c_str());
}

void Visual::setPositions(const std::vector<float>& positions) {
    m_positionsSize = positions.size();
    m_positions = new float[m_positionsSize];
    unsigned int i = 0;
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        m_positions[i++] = *it;
    }
    // TODO move bounding box calculation to a better place
    Vec3 bbmin = Vec3::max;
    Vec3 bbmax = Vec3::min;
    unsigned int j = 0;
    for (j = 0; j < m_positionsSize;) {
        if (bbmin.x > m_positions[j]) {
            bbmin.x = m_positions[j];
        }
        if (bbmax.x < m_positions[j]) {
            bbmax.x = m_positions[j];
        }
        j++;
        if (bbmin.y > m_positions[j]) {
            bbmin.y = m_positions[j];
        }
        if (bbmax.y < m_positions[j]) {
            bbmax.y = m_positions[j];
        }
        j++;
        if (bbmin.z > m_positions[j]) {
            bbmin.z = m_positions[j];
        }
        if (bbmax.z < m_positions[j]) {
            bbmax.z = m_positions[j];
        }
        j++;
    }
    m_modelBoundingBox.updateMinMax(bbmin, bbmax);
    updateWorldBoundingBox();
}

void Visual::setNormals(const std::vector<float>& normals) {
    m_modelNormals = normals;
    m_normalsSize = m_modelNormals.size();
    m_normals = new float[m_normalsSize];
    unsigned int i = 0;
    for (auto it = normals.begin(); it != normals.end(); ++it) {
        m_normals[i++] = *it;
    }
    updateWorldNormals();
}

void Visual::setTextureCoordinates(const std::vector<float>& texcoords) {
    m_textureCoordinatesSize = texcoords.size();
    m_textureCoordinates = new float[m_textureCoordinatesSize];
    unsigned int i = 0;
    for (auto it = texcoords.begin(); it != texcoords.end(); ++it) {
        m_textureCoordinates[i++] = *it;
    }
}

void Visual::setIndices(const std::vector<unsigned int>& indices) {
    m_indicesSize = indices.size();
    m_indices = new unsigned int[m_indicesSize];
    unsigned int i = 0;
    for (auto it = indices.begin(); it != indices.end(); ++it) {
        m_indices[i++] = *it;
    }
}

void Visual::setMaterialIds(const std::vector<int>& materialIds) {
    m_materialIdsSize = materialIds.size();
    m_materialIds = new int[m_materialIdsSize];
    unsigned int i = 0;
    for (auto it = materialIds.begin(); it != materialIds.end(); ++it) {
        m_materialIds[i++] = *it;
    }
}

void Visual::setProgram(GlProgram* program) {
    m_program = program;
}
