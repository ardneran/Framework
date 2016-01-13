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

void Spatial::updateBoundingBox() {
    m_worldBoundingBox = m_modelBoundingBox.transform(m_worldTransform.getStraightMatrix());
}

void Spatial::setTranslate(const Vec3& translate) {
    m_worldTransform.setTranslate(translate);
    updateBoundingBox();
}

void Spatial::setRotate(const Quat& rotate) {
    m_worldTransform.setRotate(rotate);
    updateBoundingBox();
}

void Spatial::setScale(const Vec3& scale) {
    m_worldTransform.setScale(scale);
    updateBoundingBox();
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

BoundingBox Spatial::getBoundingBox() {
    return m_worldBoundingBox;
}
