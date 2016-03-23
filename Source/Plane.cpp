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

void Plane::setNormal(const Vec3& normal) {
	m_normal = normal;
}

Vec3 Plane::getNormal() {
	return m_normal;
}

void Plane::setConstant(const float& constant) {
	m_constant = constant;
}

float Plane::getConstant() {
	return m_constant;
}
