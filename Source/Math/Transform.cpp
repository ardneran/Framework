//
//  Transform.cpp
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#include "Transform.h"

Transform::Transform()
: m_translate(Vec3::zero)
, m_rotate(Quat::identity)
, m_scale(Vec3::one) {
    compose();
}

Transform::Transform(const Vec3& translate, const Quat& rotate, const Vec3& scale)
: m_translate(translate)
, m_rotate(rotate)
, m_scale(scale) {
    compose();
}

Transform::~Transform() {
}

void Transform::setMatrix(const Mat4& matrix) {
    m_matrix = matrix;
    decompose();
}

Mat4 Transform::getMatrix() const {
    return m_matrix;
}

void Transform::setTranslate(const Vec3& translate) {
    m_translate = translate;
    compose();
}

Vec3 Transform::getTranslate() const {
    return m_translate;
}

void Transform::setRotate(const Quat& rotate) {
    m_rotate = rotate;
    compose();
}

Quat Transform::getRotate() const {
    return m_rotate;
}

void Transform::setScale(const Vec3& scale) {
    m_scale = scale;
    compose();
}

Vec3 Transform::getScale() const {
    return m_scale;
}

void Transform::setTranslateRotateScale(const Vec3& translate, const Quat& rotate, const Vec3& scale) {
    m_translate = translate;
    m_rotate = rotate;
    m_scale = scale;
    compose();
}

void Transform::getTranslateRotateScale(Vec3& translate, Quat& rotate, Vec3& scale) const {
    translate = m_translate;
    rotate = m_rotate;
    scale = m_scale;
}

Transform Transform::operator*(const Transform& other) {
    Transform t;
    t.m_matrix = m_matrix * other.m_matrix;
    t.decompose();
    return t;
}

Transform Transform::operator*=(const Transform& other) {
    return (*this * other);
}

void Transform::compose() {
    // Unoptimized but correct multiplication order SRT. This needs to be optimized further.
    m_matrix = Mat4::scale(m_scale) * Mat4::rotate(m_rotate) * Mat4::translate(m_translate);
}

void Transform::decompose() {
    float xs = 0.0f;
    float ys = 0.0f;
    float zs = 0.0f;

    m_translate.x = m_matrix.d30;
    m_translate.y = m_matrix.d31;
    m_translate.z = m_matrix.d32;

    if ((m_matrix.d00 * m_matrix.d01 * m_matrix.d02 * m_matrix.d03) < 0) {
        xs = -1.0f;
    } else {
        xs = 1.0f;
    }

    if ((m_matrix.d10 * m_matrix.d11 * m_matrix.d12 * m_matrix.d13) < 0) {
        ys = -1.0f;
    } else {
        ys = 1.0f;
    }

    if ((m_matrix.d20 * m_matrix.d21 * m_matrix.d22 * m_matrix.d23) < 0) {
        zs = -1.0f;
    } else {
        zs = 1.0f;
    }

    m_scale.x = xs * sqrtf(m_matrix.d00 * m_matrix.d00 + m_matrix.d01 * m_matrix.d01 + m_matrix.d02 * m_matrix.d02);
    m_scale.y = ys * sqrtf(m_matrix.d10 * m_matrix.d10 + m_matrix.d11 * m_matrix.d11 + m_matrix.d12 * m_matrix.d12);
    m_scale.z = zs * sqrtf(m_matrix.d20 * m_matrix.d20 + m_matrix.d21 * m_matrix.d21 + m_matrix.d22 * m_matrix.d22);

    if (m_scale.x == 0.0 || m_scale.y == 0.0 || m_scale.z == 0.0) {
        m_rotate = Quat::identity;
    } else {
        Mat4 rotateMatrix = Mat4(m_matrix.d00 / m_scale.x, m_matrix.d01 / m_scale.x, m_matrix.d02 / m_scale.x, 0,
                                 m_matrix.d10 / m_scale.y, m_matrix.d11 / m_scale.y, m_matrix.d12 / m_scale.y, 0,
                                 m_matrix.d20 / m_scale.z, m_matrix.d21 / m_scale.z, m_matrix.d22 / m_scale.z, 0,
                                 0.0f, 0.0f, 0.0f, 1.0f);
        m_rotate = Quat(rotateMatrix);
    }
}
