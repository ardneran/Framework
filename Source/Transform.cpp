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

Mat4 Transform::getMatrix() {
    return m_matrix;
}

void Transform::setTranslate(const Vec3& translate) {
    m_translate = translate;
    compose();
}

Vec3 Transform::getTranslate() {
    return m_translate;
}

void Transform::setRotate(const Quat& rotate) {
    m_rotate = rotate;
    compose();
}

Quat Transform::getRotate() {
    return m_rotate;
}

void Transform::setScale(const Vec3& scale) {
    m_scale = scale;
    compose();
}

Vec3 Transform::getScale() {
    return m_scale;
}

void Transform::setTranslateRotateScale(const Vec3& translate, const Quat& rotate, const Vec3& scale) {
    m_translate = translate;
    m_rotate = rotate;
    m_scale = scale;
    compose();
}

void Transform::getTranslateRotateScale(Vec3& translate, Quat& rotate, Vec3& scale) {
    translate = m_translate;
    rotate = m_rotate;
    scale = m_scale;
}
#define CORRECT
#if defined(CORRECT)
Transform Transform::operator*(const Transform& other) {
    Transform t;
    t.m_matrix = m_matrix * other.m_matrix;
    t.decompose();
    return t;
}
#else
// This is cheaper but incorrect so far
Transform Transform::operator*(const Transform& other) {
    Transform t;
    t.m_translate = (other.m_rotate * (other.m_scale * m_translate)) + other.m_translate;
    t.m_rotate = m_rotate * other.m_rotate; // Fix this
    t.m_scale = m_scale * other.m_scale; // Fix this
    t.compose();
    return t;
}
#endif
Transform Transform::operator*=(const Transform& other) {
    return (*this * other);
}

void Transform::compose() {
    // Unoptimized.
    //Mat4 translate = Mat4::translate(m_translate);
    //Mat4 rotate = Mat4::rotate(m_rotate);
    //Mat4 scale = Mat4::scale(m_scale);
    //m_matrix = translate * rotate * scale;

    // Optimized.
    m_matrix.d03 = 0.0f;
    m_matrix.d13 = 0.0f;
    m_matrix.d23 = 0.0f;
    m_matrix.d33 = 1.0f;
    m_matrix.d30 = m_translate.x;
    m_matrix.d31 = m_translate.y;
    m_matrix.d32 = m_translate.z;
    const float x2 = m_rotate.x + m_rotate.x;
    const float y2 = m_rotate.y + m_rotate.y;
    const float z2 = m_rotate.z + m_rotate.z;
    const float xx2 = m_rotate.x * x2;
    const float yy2 = m_rotate.y * y2;
    const float zz2 = m_rotate.z * z2;
    m_matrix.d00 = (1.0f - yy2 - zz2) * m_scale.x;
    m_matrix.d11 = (1.0f - xx2 - zz2) * m_scale.y;
    m_matrix.d22 = (1.0f - xx2 - yy2) * m_scale.z;
    const float yz2 = m_rotate.y * z2;
    const float wx2 = m_rotate.w * x2;
    m_matrix.d21 = (yz2 - wx2) * m_scale.z;
    m_matrix.d12 = (yz2 + wx2) * m_scale.y;
    const float xy2 = m_rotate.x * y2;
    const float wz2 = m_rotate.w * z2;
    m_matrix.d10 = (xy2 - wz2) * m_scale.y;
    m_matrix.d01 = (xy2 + wz2) * m_scale.x;
    const float xz2 = m_rotate.x * z2;
    const float wy2 = m_rotate.w * y2;
    m_matrix.d20 = (xz2 + wy2) * m_scale.z;
    m_matrix.d02 = (xz2 - wy2) * m_scale.x;
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
