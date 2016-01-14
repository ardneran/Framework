//
//  Spatial.cpp
//  Framework
//
//  Created by Narendra Umate on 8/23/15.
//
//

#include "Spatial.h"

Spatial::Spatial() {
}

Spatial::~Spatial() {
}

void Spatial::update() {
}

void Spatial::updateWorldBoundingBox() {
}

void Spatial::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateWorldBoundingBox();
}

void Spatial::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateWorldBoundingBox();
}

void Spatial::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateWorldBoundingBox();
}

Vec3 Spatial::getTranslate() {
    return m_worldTransform.getTranslate();
}

Quat Spatial::getRotate() {
    return m_worldTransform.getRotate();
}

Vec3 Spatial::getScale() {
    return m_worldTransform.getScale();
}

BoundingBox Spatial::getWorldBoundingBox() {
    return m_worldBoundingBox;
}
