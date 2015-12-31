//
//  Visual.cpp
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#include "Visual.h"

Visual::Visual() {
}

Visual::~Visual() {
}

bool Visual::updateModelBounds() {
    BoundingBox oldModelBoundingBox = m_modelBoundingBox;
    // TODO
    // update
    return (m_modelBoundingBox != oldModelBoundingBox);
}

bool Visual::updateWorldBounds() {
    BoundingBox oldWorldBoundingBox = m_worldBoundingBox;
    // TODO
    // update
    return (m_worldBoundingBox != oldWorldBoundingBox);
}
