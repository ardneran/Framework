//
//  Transform.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "Transform.h"

Transform::Transform()
: m_rotation(Quat::identity)
, m_translation(Vec3::zero)
, m_scale(Vec3::one) {
}

Transform::~Transform() {
}

Transform Transform::operator*(const Transform& other) {
    // TODO verify this
    Transform t;
    t.m_rotation = other.m_rotation * m_rotation;
    t.m_scale = m_scale * other.m_scale;
    t.m_translation = (other.m_rotation * (other.m_scale * m_translation)) + other.m_translation;
    return t;
}

Transform Transform::operator*=(const Transform& other) {
    return (*this * other);
}
