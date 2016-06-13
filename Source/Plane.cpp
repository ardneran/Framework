//
//  Plane.cpp
//  Framework
//
//  Created by Narendra Umate on 3/22/16.
//
//

#include "Plane.h"

Plane::Plane()
: m_normal(Vec3::zero)
, m_constant(0.0f) {
}

Plane::~Plane() {
}

void Plane::normalize() {
	float length = m_normal.norm();
	m_normal /= length;
	m_constant /= length;
}

float Plane::distance(const Vec3& point) {
	return dot(point, m_normal) + m_constant;
}
