//
//  Camera.cpp
//  Framework
//
//  Created by Narendra Umate on 11/29/15.
//
//

#include "Camera.h"

Camera::Camera(const Type& type)
: m_type(type)
, m_position(Vec3::zero)
, m_right(Vec3::xxx)
, m_up(Vec3::yyy)
, m_front(Vec3::zzz)
, m_upFovDegrees(0.0f)
, m_aspectRatio(0.0f)
, m_rightMin(0.0f)
, m_rightMax(0.0f)
, m_upMin(0.0f)
, m_upMax(0.0f)
, m_frontMin(0.0f)
, m_frontMax(0.0f)
, m_preViewMatrix(Mat4::identity)
, m_viewMatrix(Mat4::identity)
, m_orthographicProjectionMatrix(Mat4::identity)
, m_perspectiveProjectionMatrix(Mat4::identity)
, m_viewOrthographicProjectionMatrix(Mat4::identity)
, m_viewPerspectiveProjectionMatrix(Mat4::identity)
, m_postProjectionMatrix(Mat4::identity) {
    updateViewMatrix();
    updateProjectionMatrix();
    updateViewProjectionMatrix();
}

Camera::~Camera() {
}

void Camera::setType(const Type& type) {
    m_type = type;
}

void Camera::setFrame(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front) {
    m_position = position;
    m_right = right;
    m_up = up;
    m_front = front;
    updateViewMatrix();
    updateViewProjectionMatrix();
}

void Camera::setPosition(const Vec3& position) {
    m_position = position;
    updateViewMatrix();
    updateViewProjectionMatrix();
}

void Camera::setAxes(const Vec3& right, const Vec3& up, const Vec3& front) {
    m_right = right;
    m_up = up;
    m_front = front;
    updateViewMatrix();
    updateViewProjectionMatrix();
}

void Camera::setFrustum(const float& upFovDegrees, const float& aspectRatio, const float& frontMin, const float& frontMax) {
    m_upFovDegrees = upFovDegrees;
    m_aspectRatio = aspectRatio;
    m_frontMin = frontMin;
    m_frontMax = frontMax;
    m_upMax = frontMin * tan(0.5f * upFovDegrees * M_DEGREE_TO_RADIAN);
    m_rightMax = aspectRatio * m_upMax;
    m_upMin = -m_upMax;
    m_rightMin = -m_rightMax;
    updateProjectionMatrix();
    updateViewProjectionMatrix();
}

void Camera::setFrustum(const float& rightMin, const float& rightMax, const float& upMin, const float& upMax, const float& frontMin, const float& frontMax) {
    m_rightMin = rightMin;
    m_rightMax = rightMax;
    m_upMin = upMin;
    m_upMax = upMax;
    m_frontMin = frontMin;
    m_frontMax = frontMax;
    updateProjectionMatrix();
    updateViewProjectionMatrix();
}

void Camera::setPreViewMatrix(const Mat4& preViewMatrix) {
    m_preViewMatrix = preViewMatrix;
    updateViewProjectionMatrix();
}

void Camera::setPostProjectionMatrix(const Mat4& postProjectionMatrix) {
    m_postProjectionMatrix = postProjectionMatrix;
    updateViewProjectionMatrix();
}

Camera::Type Camera::getType() {
    return m_type;
}

void Camera::getFrame(Vec3& position, Vec3& right, Vec3& up, Vec3& front) {
    position = m_position;
    right = m_right;
    up = m_up;
    front = m_front;
}

void Camera::getPosition(Vec3& position) {
    position = m_position;
}

void Camera::getAxes(Vec3& right, Vec3& up, Vec3& front) {
    right = m_right;
    up = m_up;
    front = m_front;
}

void Camera::getFrustum(float& upFovDegrees, float& aspectRatio, float& frontMin, float& frontMax) {
    upFovDegrees = m_upFovDegrees;
    aspectRatio = m_aspectRatio;
    frontMin = m_frontMin;
    frontMax = m_frontMax;
}

void Camera::getFrustum(float& rightMin, float& rightMax, float& upMin, float& upMax, float& frontMin, float& frontMax) {
    rightMin = m_rightMin;
    rightMax = m_rightMax;
    upMin = m_upMin;
    upMax = m_upMax;
    frontMin = m_frontMin;
    frontMax = m_frontMax;
}

void Camera::getPreViewMatrix(Mat4& preViewMatrix) {
    preViewMatrix = m_preViewMatrix;
}

void Camera::getPostProjectionMatrix(Mat4& postProjectionMatrix) {
    postProjectionMatrix = m_postProjectionMatrix;
}

void Camera::updateViewMatrix() {
    // update view matrix
    m_viewMatrix.d00 = m_right[0];
    m_viewMatrix.d01 = m_right[1];
    m_viewMatrix.d02 = m_right[2];
    m_viewMatrix.d03 = -dot(m_position, m_right);
    m_viewMatrix.d10 = m_up[0];
    m_viewMatrix.d11 = m_up[1];
    m_viewMatrix.d12 = m_up[2];
    m_viewMatrix.d13 = -dot(m_position, m_up);
    m_viewMatrix.d20 = m_front[0];
    m_viewMatrix.d21 = m_front[1];
    m_viewMatrix.d22 = m_front[2];
    m_viewMatrix.d23 = -dot(m_position, m_front);
    m_viewMatrix.d30 = 0.0f;
    m_viewMatrix.d31 = 0.0f;
    m_viewMatrix.d32 = 0.0f;
    m_viewMatrix.d33 = 1.0f;
}

void Camera::updateProjectionMatrix() {
    float invRDiff = 1.0f / (m_rightMax - m_rightMin);
    float invUDiff = 1.0f / (m_upMax - m_upMin);
    float invFDiff = 1.0f / (m_frontMax - m_frontMin);

    if (m_type == Camera::Type::Orthographic) {
        // update orthographic projection matrix
        // TODO fix this matrix so that it works
        m_orthographicProjectionMatrix.d00 = 2.0f * invRDiff;
        m_orthographicProjectionMatrix.d01 = 0.0f;
        m_orthographicProjectionMatrix.d02 = 0.0f;
        m_orthographicProjectionMatrix.d03 = -(m_rightMin + m_rightMax) * invRDiff;
        m_orthographicProjectionMatrix.d10 = 0.0f;
        m_orthographicProjectionMatrix.d11 = 2.0f * invUDiff;
        m_orthographicProjectionMatrix.d12 = 0.0f;
        m_orthographicProjectionMatrix.d13 = -(m_upMin + m_upMax) * invUDiff;
        m_orthographicProjectionMatrix.d20 = 0.0f;
        m_orthographicProjectionMatrix.d21 = 0.0f;
        m_orthographicProjectionMatrix.d22 = invFDiff;
        m_orthographicProjectionMatrix.d23 = -m_frontMin * invFDiff;
        m_orthographicProjectionMatrix.d30 = 0.0f;
        m_orthographicProjectionMatrix.d31 = 0.0f;
        m_orthographicProjectionMatrix.d32 = 0.0f;
        m_orthographicProjectionMatrix.d33 = 1.0f;
    } else if (m_type == Camera::Type::Perspective) {
        // update perspective projection matrix
        m_perspectiveProjectionMatrix.d00 = 2.0f * m_frontMin * invRDiff;
        m_perspectiveProjectionMatrix.d01 = 0.0f;
        m_perspectiveProjectionMatrix.d02 = -(m_rightMin + m_rightMax) * invRDiff;
        m_perspectiveProjectionMatrix.d03 = 0.0f;
        m_perspectiveProjectionMatrix.d10 = 0.0f;
        m_perspectiveProjectionMatrix.d11 = 2.0f * m_frontMin * invUDiff;
        m_perspectiveProjectionMatrix.d12 = -(m_upMin + m_upMax) * invUDiff;
        m_perspectiveProjectionMatrix.d13 = 0.0f;
        m_perspectiveProjectionMatrix.d20 = 0.0f;
        m_perspectiveProjectionMatrix.d21 = 0.0f;
        m_perspectiveProjectionMatrix.d22 = -(m_frontMax)*invFDiff; // previously m_frontMax * invFDiff;
        m_perspectiveProjectionMatrix.d23 = -2.0f * m_frontMin * m_frontMax * invFDiff; // previously -m_frontMin * m_frontMax * invFDiff;
        m_perspectiveProjectionMatrix.d30 = 0.0f;
        m_perspectiveProjectionMatrix.d31 = 0.0f;
        m_perspectiveProjectionMatrix.d32 = -1.0f; // previously 1.0f;
        m_perspectiveProjectionMatrix.d33 = 0.0f;
    }
}

void Camera::updateViewProjectionMatrix() {
    if (m_type == Camera::Type::Orthographic) {
        m_viewOrthographicProjectionMatrix = m_orthographicProjectionMatrix * m_viewMatrix;
    } else if (m_type == Camera::Type::Perspective) {
        m_viewPerspectiveProjectionMatrix = m_perspectiveProjectionMatrix * m_viewMatrix;
    }

    if (m_postProjectionMatrix != Mat4::identity) {
        if (m_type == Camera::Type::Orthographic) {
            m_viewOrthographicProjectionMatrix = m_postProjectionMatrix * m_viewOrthographicProjectionMatrix;
        } else if (m_type == Camera::Type::Perspective) {
            m_viewPerspectiveProjectionMatrix = m_postProjectionMatrix * m_viewPerspectiveProjectionMatrix;
        }
    }

    if (m_preViewMatrix != Mat4::identity) {
        if (m_type == Camera::Type::Orthographic) {
            m_viewOrthographicProjectionMatrix = m_viewOrthographicProjectionMatrix * m_preViewMatrix;
        } else if (m_type == Camera::Type::Perspective) {
            m_viewPerspectiveProjectionMatrix = m_viewPerspectiveProjectionMatrix * m_preViewMatrix;
        }
    }
}

Mat4 Camera::getViewMatrix() {
    return m_viewMatrix;
}

Mat4 Camera::getViewProjectionMatrix() {
    if (m_type == Camera::Type::Orthographic) {
        return m_viewOrthographicProjectionMatrix;
    } else {
        return m_viewPerspectiveProjectionMatrix;
    }
}
