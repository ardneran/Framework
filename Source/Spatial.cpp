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

BoundingBox Spatial::getWorldBoundingBox() {
    return m_worldBoundingBox;
}

BoundingBox Spatial::getLocalBoundingBox() {
    return m_localBoundingBox;
}

Transform Spatial::getWorldTransform() {
    return m_worldTransform;
}

Transform Spatial::getLocalTransform() {
    return m_localTransform;
}

void Spatial::update() {
}
