//
//  Spatial.cpp
//  Framework
//
//  Created by Narendra Umate on 8/23/15.
//
//

#include "Spatial.h"

Spatial::Spatial()
: m_parent(0) {
}

Spatial::~Spatial() {
}

void Spatial::setParent(Spatial* const parent) {
    m_parent = parent;
}

Spatial* Spatial::getParent() const {
    return m_parent;
}

void Spatial::update(const bool& initiator) {
    updateWorldTransforms();
    bool boundsDirty = updateWorldBounds();
    if (boundsDirty && initiator) {
        propagateWorldBoundsToParent();
    }
}

void Spatial::updateWorldTransforms() {
    if (m_parent) {
        m_worldTransform = m_parent->m_worldTransform * m_localTransform;
    } else {
        m_worldTransform = m_localTransform;
    }
}

bool Spatial::updateWorldBounds() {
    return true;
}

void Spatial::propagateWorldBoundsToParent() {
    if (m_parent) {
        bool parentBoundsDirty = m_parent->updateWorldBounds();
        if (parentBoundsDirty) {
            m_parent->propagateWorldBoundsToParent();
        }
    }
}
