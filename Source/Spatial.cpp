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

void Spatial::setBoundingBox(const Space& space, const BoundingBox& boundingBox) {
    if (space == Spatial::Local) {
        m_localBoundingBox = boundingBox;
        m_worldBoundingBox = boundingBox.transform(m_worldTransform.getMatrix());
    } else {
        m_worldBoundingBox = boundingBox;
        m_localBoundingBox = boundingBox.transform(m_worldTransform.getMatrix().inverse());
    }
}

void Spatial::setTranslate(const Space& space, const Vec3& translate) {
    if (space == Spatial::Local) {
        m_localTransform.setTranslate(translate);
        // TODO Bounding Box
    } else {
        m_worldTransform.setTranslate(translate);
        // TODO Bounding Box
    }
}

void Spatial::setRotate(const Space& space, const Quat& rotate) {
    if (space == Spatial::Local) {
        m_localTransform.setRotate(rotate);
        // TODO Bounding Box
    } else {
        m_worldTransform.setRotate(rotate);
        // TODO Bounding Box
    }
}

void Spatial::setScale(const Space& space, const Vec3& scale) {
    if (space == Spatial::Local) {
        m_localTransform.setScale(scale);
        // TODO Bounding Box
    } else {
        m_worldTransform.setScale(scale);
        // TODO Bounding Box
    }
}

BoundingBox Spatial::getBoundingBox(const Space& space) {
    if (space == Spatial::Local) {
        return m_localBoundingBox;
    } else {
        return m_worldBoundingBox;
    }
}

Vec3 Spatial::getTranslate(const Space& space) {
    if (space == Spatial::Local) {
        return m_localTransform.getTranslate();
    } else {
        return m_worldTransform.getTranslate();
    }
}

Quat Spatial::getRotate(const Space& space) {
    if (space == Spatial::Local) {
        return m_localTransform.getRotate();
    } else {
        return m_worldTransform.getRotate();
    }
}

Vec3 Spatial::getScale(const Space& space) {
    if (space == Spatial::Local) {
        return m_localTransform.getScale();
    } else {
        return m_worldTransform.getScale();
    }
}
