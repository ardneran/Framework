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

BoundingBox Spatial::getBoundingBox() {
    return m_worldBoundingBox;
}

Transform Spatial::getTransform() {
    return m_worldTransform;
}

void Spatial::update() {
}
