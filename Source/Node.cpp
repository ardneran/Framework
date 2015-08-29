//
//  Node.cpp
//  Framework
//
//  Created by Narendra Umate on 8/29/15.
//
//

#include "Node.h"

Node::~Node() {
}


Node::Node() {
}

void Node::updateWorldTransforms() {
	Spatial::updateWorldTransforms();
	for (std::vector<Spatial*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		if (*it) {
			(*it)->update();
		}
	}
}

bool Node::updateWorldBounds() {
	BoundingBox oldWorldBoundingBox = m_worldBoundingBox;
	m_worldBoundingBox.update(Vec3::zero, Vec3::zero);
	for (std::vector<Spatial*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
		if (*it) {
			// TODO add to bound
		}
	}
	return (oldWorldBoundingBox != m_worldBoundingBox);
}
