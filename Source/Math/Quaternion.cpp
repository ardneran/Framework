//
//  Quaternion.cpp
//  Camaleao
//
//  Created by Narendra Umate on 3/8/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Quaternion.h"

const Quat Quat::identity = Quat(0.0f, 0.0f, 0.0f, 1.0f);

Quat::Quat(void)
: x(0.0f)
, y(0.0f)
, z(0.0f)
, w(1.0f) {
}

Quat::Quat(const Vec4& vec4)
: x(vec4.x)
, y(vec4.y)
, z(vec4.z)
, w(vec4.w) {
}

Quat::Quat(const float& x, const float& y, const float& z, const float& w)
: x(x)
, y(y)
, z(z)
, w(w) {
}

Quat::Quat(const float& s, const Vec3& vec3)
: x(vec3.x)
, y(vec3.y)
, z(vec3.z)
, w(s) {
}

Quat::Quat(const Vec3& axis, const float& angle) {
    float angle_divide_2 = angle * 0.5f;
    Vec3 v = axis.normal() * sinf(angle_divide_2);
    x = v.x;
    y = v.y;
    z = v.z;
    w = /* s = */ cosf(angle_divide_2);
}

Quat::Quat(const Vec3& v0, const Vec3& v1) {
    // Reference
    // Game Programming Gems 1
    // 2.10 The Shortest Arc Quaternion Page 217 Author Stan Melax

    // r = v0normal x v1normal
    // s_multiply_2 = sqrt(2 * (1 + v0normal . v1normal))

    Vec3 v0normal = v0.normal();
    Vec3 v1normal = v1.normal();

    float s_multiply_2 = sqrtf(2.0f * (1.0f + dot(v0normal, v1normal)));

    Vec3 v = cross(v0normal, v1normal) / s_multiply_2;
    x = v.x;
    y = v.y;
    z = v.z;
    w = /* s = */ s_multiply_2 / 2.0f;
}

Quat::Quat(const float& yaw, const float& pitch, const float& roll) {
    // Reference
    // http://referencesource.microsoft.com/#System.Numerics/System/Numerics/Quaternion.cs
    // Roll first, about axis the object is facing, then
    // pitch upward, then yaw to face into the new heading
    const float halfRoll = roll * 0.5f;
    const float sr = sinf(halfRoll);
    const float cr = cosf(halfRoll);

    const float halfPitch = pitch * 0.5f;
    const float sp = sinf(halfPitch);
    const float cp = cosf(halfPitch);

    const float halfYaw = yaw * 0.5f;
    const float sy = sinf(halfYaw);
    const float cy = cosf(halfYaw);

    x = cy * sp * cr + sy * cp * sr;
    y = sy * cp * cr - cy * sp * sr;
    z = cy * cp * sr - sy * sp * cr;
    w = cy * cp * cr + sy * sp * sr;
}

Quat::Quat(const Mat4& matrix) {
    if ((matrix.d00 + matrix.d11 + matrix.d22) > 0.0f) {
        float m1 = (float)sqrtf((double)(matrix.d00 + matrix.d11 + matrix.d22 + 1.0f));
        w = m1 * 0.5f;
        m1 = 0.5f / m1;
        x = (matrix.d12 - matrix.d21) * m1;
        y = (matrix.d20 - matrix.d02) * m1;
        z = (matrix.d01 - matrix.d10) * m1;
    } else if ((matrix.d00 >= matrix.d11) && (matrix.d00 >= matrix.d22)) {
        float m2 = (float)sqrtf((double)(1.0f + matrix.d00 - matrix.d11 - matrix.d22));
        float m3 = 0.5f / m2;
        x = 0.5f * m2;
        y = (matrix.d01 + matrix.d10) * m3;
        z = (matrix.d02 + matrix.d20) * m3;
        w = (matrix.d12 - matrix.d21) * m3;
    } else if (matrix.d11 > matrix.d22) {
        float m4 = (float)sqrtf((double)(1.0f + matrix.d11 - matrix.d00 - matrix.d22));
        float m5 = 0.5f / m4;
        x = (matrix.d10 + matrix.d01) * m5;
        y = 0.5f * m4;
        z = (matrix.d21 + matrix.d12) * m5;
        w = (matrix.d20 - matrix.d02) * m5;
    } else {
        float m6 = (float)sqrtf((double)(1.0f + matrix.d22 - matrix.d00 - matrix.d11));
        float m7 = 0.5f / m6;
        x = (matrix.d20 + matrix.d02) * m7;
        y = (matrix.d21 + matrix.d12) * m7;
        z = 0.5f * m6;
        w = (matrix.d01 - matrix.d10) * m7;
    }
}

Vec3 Quat::axis() const {
    return Vec3(x, y, z);
}

float Quat::angle() const {
    // w = cos(angle / 2)
    // angle = acos(w) * 2
    return acosf(w) * 2.0f;
}

Quat Quat::inverse() const {
    float invmagsqr = 1.0f / dot(*this, *this);
    return Quat(-x * invmagsqr, -y * invmagsqr, -z * invmagsqr, w * invmagsqr);
}

Quat Quat::conjugate() const {
    return Quat(-x, -y, -z, w);
}

float Quat::norm(void) const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

Quat Quat::normal(void) const {
    float mag = norm();
    return Quat(x / mag, y / mag, z / mag, w / mag);
}

Quat Quat::normalize(void) {
    float mag = norm();
    x /= mag;
    y /= mag;
    z /= mag;
    w /= mag;
    return *this;
}

Mat3 Quat::mat3() const {
    return Mat3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y + w * z), 2.0f * (x * z - w * y),
                2.0f * (x * y - w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z + w * x),
                2.0f * (x * z + w * y), 2.0f * (y * z - w * x), 1.0f - 2.0f * (x * x + y * y));
}

Mat4 Quat::mat4() const {
    return Mat4(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y + w * z), 2.0f * (x * z - w * y), 0.0f,
                2.0f * (x * y - w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z + w * x), 0.0f,
                2.0f * (x * z + w * y), 2.0f * (y * z - w * x), 1.0f - 2.0f * (x * x + y * y), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

Vec3 Quat::operator*(const Vec3& a) const {
    Quat aq(a.x, a.y, a.z, 0.0f);
    Quat at;
    Quat ar;
    Quat in = inverse();
    at = *this * aq;
    ar = at * in;
    return Vec3(ar.x, ar.y, ar.z);
}

Quat Quat::operator+(const Quat& a) const {
    return Quat(x + a.x, y + a.y, z + a.z, w + a.w);
}

Quat Quat::operator-(const Quat& a) const {
    return Quat(x - a.x, y - a.y, z - a.z, w - a.w);
}

Quat Quat::operator*(const Quat& a) const {
    // P * Q = (p0 + p1i + p2j + p3k)(q0 + q1i + q2j + q3k)
    // P * Q = (p0q0 − p1q1 − p2q2 − p3q3) + . . . i + . . . j + . . . k
    // P * Q = (p0 + p)(q0 + q)
    // P * Q = (p0q0 + p0q + q0p + pq)	//	pq = p x q - p . q	//	cross - dot
    // P * Q = (p0q0 - p.q) + (p0q + q0p + p x q)

    return Quat(a.w * x + a.x * w - a.y * z + a.z * y,
                a.w * y + a.x * z + a.y * w - a.z * x,
                a.w * z - a.x * y + a.y * x + a.z * w,
                a.w * w - a.x * x - a.y * y - a.z * z);
}

Quat Quat::operator/(const Quat& a) const {
    float invmagsqr = 1.0f / dot(*this, *this);
    return Quat((a.w * x - a.x * w - a.y * z + a.z * y) * invmagsqr,
                (a.w * y + a.x * z - a.y * w - a.z * x) * invmagsqr,
                (a.w * z - a.x * y + a.y * x - a.z * w) * invmagsqr,
                (a.w * w + a.x * x + a.y * y + a.z * z) * invmagsqr);
}

void Quat::operator*=(const Quat& a) {
    *this = *this * a;
}

void Quat::operator/=(const Quat& a) {
    *this = *this / a;
}

float dot(const Quat& q0, const Quat& q1) {
    return (q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w);
}

Quat lerp(const Quat& q0, const Quat& q1, const float& t) {
    return Quat(lerp(q0.x, q1.x, t), lerp(q0.y, q1.y, t),
                lerp(q0.z, q1.z, t), lerp(q0.w, q1.w, t));
}

Quat slerp(const Quat& q0, const Quat& q1, const float& t) {
    return Quat::identity; // TODO implement this
}
