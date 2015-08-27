//
//  Transform.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "Transform.h"

Transform::Transform()
:	m_rotation(Quat::identity)
,	m_translation(Vec3::zero)
,	m_scale(Vec3::one) {
}

Transform::~Transform() {
}

Transform Transform::operator*(const Transform& other) {
	Transform t;
	// TODO
	return t;
}

Transform Transform::operator*=(const Transform& other) {
	return (*this * other);
}
