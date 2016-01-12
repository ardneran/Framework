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

void Spatial::updateBoundingBox(const Space& space) {
    if (space == Space::Local) {
        m_localBoundingBox = m_startBoundingBox.transform(m_localTransform.getStraightMatrix());
        m_worldBoundingBox = m_localBoundingBox.transform(m_worldTransform.getStraightMatrix());
    } else {
        m_worldBoundingBox = m_localBoundingBox.transform(m_worldTransform.getStraightMatrix());
    }
}

void Spatial::setTranslate(const Space& space, const Vec3& translate) {
    if (space == Space::Local) {
        m_localTransform.setTranslate(translate);
        updateBoundingBox(space);
    } else {
        m_worldTransform.setTranslate(translate);
        updateBoundingBox(space);
    }
}

void Spatial::setRotate(const Space& space, const Quat& rotate) {
    if (space == Space::Local) {
        m_localTransform.setRotate(rotate);
        updateBoundingBox(space);
    } else {
        m_worldTransform.setRotate(rotate);
        updateBoundingBox(space);
    }
}

void Spatial::setScale(const Space& space, const Vec3& scale) {
    if (space == Space::Local) {
        m_localTransform.setScale(scale);
        updateBoundingBox(space);
    } else {
        m_worldTransform.setScale(scale);
        updateBoundingBox(space);
    }
}

Vec3 Spatial::getTranslate(const Space& space) {
    if (space == Space::Local) {
        return m_localTransform.getTranslate();
    } else {
        return m_worldTransform.getTranslate();
    }
}

Quat Spatial::getRotate(const Space& space) {
    if (space == Space::Local) {
        return m_localTransform.getRotate();
    } else {
        return m_worldTransform.getRotate();
    }
}

Vec3 Spatial::getScale(const Space& space) {
    if (space == Space::Local) {
        return m_localTransform.getScale();
    } else {
        return m_worldTransform.getScale();
    }
}

BoundingBox Spatial::getBoundingBox(const Space& space) {
	if (space == Space::Local) {
		return m_localBoundingBox;
	} else {
		return m_worldBoundingBox;
	}
}
