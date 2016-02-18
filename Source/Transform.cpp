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
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
}

Transform::Transform(const Vec3& translate, const Quat& rotate, const Vec3& scale)
: m_translate(translate)
, m_rotate(rotate)
, m_scale(scale) {
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
	m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
}

Transform::~Transform() {
}

void Transform::setStraightMatrix(const Mat4& matrix) {
    m_straightMatrix = matrix;
#if defined(SUPPORT_INVERTED)
	m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
    decomposeStraightMatrix();
}

Mat4 Transform::getStraightMatrix() {
    return m_straightMatrix;
}
#if defined(SUPPORT_INVERTED)
void Transform::setInvertedMatrix(const Mat4& matrix) {
    m_invertedMatrix = matrix;
    m_straightMatrix = m_invertedMatrix.inverse();
    decomposeStraightMatrix();
}

Mat4 Transform::getInvertedMatrix() {
    return m_invertedMatrix;
}
#endif // defined(SUPPORT_INVERTED)
void Transform::setTranslate(const Vec3& translate) {
    m_translate = translate;
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
}

Vec3 Transform::getTranslate() {
    return m_translate;
}

void Transform::setRotate(const Quat& rotate) {
    m_rotate = rotate;
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
}

Quat Transform::getRotate() {
    return m_rotate;
}

void Transform::setScale(const Vec3& scale) {
    m_scale = scale;
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
}

Vec3 Transform::getScale() {
    return m_scale;
}

void Transform::setTranslateRotateScale(const Vec3& translate, const Quat& rotate, const Vec3& scale) {
    m_translate = translate;
    m_rotate = rotate;
    m_scale = scale;
    composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
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
    t.m_straightMatrix = m_straightMatrix * other.m_straightMatrix;
#if defined(SUPPORT_INVERTED)
    t.m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
    t.decomposeStraightMatrix();
    return t;
}
#else
Transform Transform::operator*(const Transform& other) {
    // This is cheaper but needs plenty of work.
    // Make sure that results match those above.
    Transform t;
    t.m_translate = (other.m_rotate * (other.m_scale * m_translate)) + other.m_translate;
    t.m_rotate = m_rotate * other.m_rotate; // Fix this
    t.m_scale = m_scale * other.m_scale; // Fix this
    t.composeStraightMatrix();
#if defined(SUPPORT_INVERTED)
    t.m_invertedMatrix = m_straightMatrix.inverse();
#endif // defined(SUPPORT_INVERTED)
    return t;
}
#endif
Transform Transform::operator*=(const Transform& other) {
    return (*this * other);
}

void Transform::composeStraightMatrix() {
    // Unoptimized.
    Mat4 translate = Mat4::translate(m_translate);
    Mat4 rotate = Mat4::rotate(m_rotate);
    Mat4 scale = Mat4::scale(m_scale);
    m_straightMatrix = translate * rotate * scale;

    // Optimized.
	/*
	// TODO Fix this code so that it works as above.
    m_straightMatrix.d03 = 0.0f;
    m_straightMatrix.d13 = 0.0f;
    m_straightMatrix.d23 = 0.0f;
    m_straightMatrix.d33 = 1.0f;
    m_straightMatrix.d30 = m_translate.x;
    m_straightMatrix.d31 = m_translate.y;
    m_straightMatrix.d32 = m_translate.z;
    const float x2 = m_rotate.x + m_rotate.x;
    const float y2 = m_rotate.y + m_rotate.y;
    const float z2 = m_rotate.z + m_rotate.z;
    const float xx2 = m_rotate.x * x2;
    const float yy2 = m_rotate.y * y2;
    const float zz2 = m_rotate.z * z2;
    m_straightMatrix.d00 = (1.0f - yy2 - zz2) * m_scale.x;
    m_straightMatrix.d11 = (1.0f - xx2 - zz2) * m_scale.y;
    m_straightMatrix.d22 = (1.0f - xx2 - yy2) * m_scale.z;
    const float yz2 = m_rotate.y * z2;
    const float wx2 = m_rotate.w * x2;
    m_straightMatrix.d21 = (yz2 - wx2) * m_scale.z;
    m_straightMatrix.d12 = (yz2 + wx2) * m_scale.y;
    const float xy2 = m_rotate.x * y2;
    const float wz2 = m_rotate.w * z2;
    m_straightMatrix.d10 = (xy2 - wz2) * m_scale.y;
    m_straightMatrix.d01 = (xy2 + wz2) * m_scale.x;
    const float xz2 = m_rotate.x * z2;
    const float wy2 = m_rotate.w * y2;
    m_straightMatrix.d20 = (xz2 + wy2) * m_scale.z;
    m_straightMatrix.d02 = (xz2 - wy2) * m_scale.x;
	*/
}

void Transform::decomposeStraightMatrix() {
    float xs = 0.0f;
    float ys = 0.0f;
    float zs = 0.0f;

    m_translate.x = m_straightMatrix.d30;
    m_translate.y = m_straightMatrix.d31;
    m_translate.z = m_straightMatrix.d32;

    if ((m_straightMatrix.d00 * m_straightMatrix.d01 * m_straightMatrix.d02 * m_straightMatrix.d03) < 0) {
        xs = -1.0f;
    } else {
        xs = 1.0f;
    }

    if ((m_straightMatrix.d10 * m_straightMatrix.d11 * m_straightMatrix.d12 * m_straightMatrix.d13) < 0) {
        ys = -1.0f;
    } else {
        ys = 1.0f;
    }

    if ((m_straightMatrix.d20 * m_straightMatrix.d21 * m_straightMatrix.d22 * m_straightMatrix.d23) < 0) {
        zs = -1.0f;
    } else {
        zs = 1.0f;
    }

    m_scale.x = xs * sqrtf(m_straightMatrix.d00 * m_straightMatrix.d00 + m_straightMatrix.d01 * m_straightMatrix.d01 + m_straightMatrix.d02 * m_straightMatrix.d02);
    m_scale.y = ys * sqrtf(m_straightMatrix.d10 * m_straightMatrix.d10 + m_straightMatrix.d11 * m_straightMatrix.d11 + m_straightMatrix.d12 * m_straightMatrix.d12);
    m_scale.z = zs * sqrtf(m_straightMatrix.d20 * m_straightMatrix.d20 + m_straightMatrix.d21 * m_straightMatrix.d21 + m_straightMatrix.d22 * m_straightMatrix.d22);

    if (m_scale.x == 0.0 || m_scale.y == 0.0 || m_scale.z == 0.0) {
        m_rotate = Quat::identity;
    } else {
        Mat4 rotateMatrix = Mat4(m_straightMatrix.d00 / m_scale.x, m_straightMatrix.d01 / m_scale.x, m_straightMatrix.d02 / m_scale.x, 0,
                                 m_straightMatrix.d10 / m_scale.y, m_straightMatrix.d11 / m_scale.y, m_straightMatrix.d12 / m_scale.y, 0,
                                 m_straightMatrix.d20 / m_scale.z, m_straightMatrix.d21 / m_scale.z, m_straightMatrix.d22 / m_scale.z, 0,
                                 0.0f, 0.0f, 0.0f, 1.0f);
        m_rotate = Quat(rotateMatrix);
    }
}
