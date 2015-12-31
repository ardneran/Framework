//
//  Node.cpp
//  Framework
//
//  Created by Narendra Umate on 8/29/15.
//
//

#include "Node.h"

Node::Node() {
}

Node::~Node() {
}

void Node::updateWorldTransforms() {
    Spatial::updateWorldTransforms();
    for (std::vector<Spatial*>::iterator spatialPointerPointer = m_children.begin(); spatialPointerPointer != m_children.end(); ++spatialPointerPointer) {
        if (*spatialPointerPointer) {
            (*spatialPointerPointer)->update();
        }
    }
}

bool Node::updateWorldBounds() {
    BoundingBox oldWorldBoundingBox = m_worldBoundingBox;
    std::vector<BoundingBox> boxes;
    for (std::vector<Spatial*>::iterator spatialPointerPointer = m_children.begin(); spatialPointerPointer != m_children.end(); ++spatialPointerPointer) {
        boxes.push_back((*spatialPointerPointer)->m_worldBoundingBox);
    }
    m_worldBoundingBox.create(boxes);
    return (oldWorldBoundingBox != m_worldBoundingBox);
}
