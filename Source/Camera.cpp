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
	updateFrustumPlanesAndPoints();
}

Camera::~Camera() {
}

void Camera::setType(const Type& type) {
    m_type = type;
	updateProjectionMatrix();
	updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
}

void Camera::setFrame(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front) {
    m_position = position;
    m_right = right;
    m_up = up;
    m_front = front;
    updateViewMatrix();
    updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
}

void Camera::setPosition(const Vec3& position) {
    m_position = position;
    updateViewMatrix();
    updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
}

void Camera::setAxes(const Vec3& right, const Vec3& up, const Vec3& front) {
    m_right = right;
    m_up = up;
    m_front = front;
    updateViewMatrix();
    updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
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
	updateFrustumPlanesAndPoints();
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
	updateFrustumPlanesAndPoints();
}

void Camera::setSize(const int& screenWidth, const int& screenHeight) {
    if (m_type == Camera::Orthographic) {
		// TODO Verify that this works
		setFrustum(-float(screenWidth) / 2.0f, float(screenWidth) / 2.0f, -float(screenHeight) / 2.0f, float(screenHeight) / 2.0f, m_frontMin, m_frontMax);
    } else if (m_type == Camera::Perspective) {
		setFrustum(m_upFovDegrees, float(screenWidth) / float(screenHeight), m_frontMin, m_frontMax);
	}
}

void Camera::setPreViewMatrix(const Mat4& preViewMatrix) {
    m_preViewMatrix = preViewMatrix;
    updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
}

void Camera::setPostProjectionMatrix(const Mat4& postProjectionMatrix) {
    m_postProjectionMatrix = postProjectionMatrix;
    updateViewProjectionMatrix();
	updateFrustumPlanesAndPoints();
}

void Camera::getFrame(Vec3& position, Vec3& right, Vec3& up, Vec3& front) {
    position = m_position;
    right = m_right;
    up = m_up;
    front = m_front;
}

void Camera::getAxes(Vec3& right, Vec3& up, Vec3& front) {
    right = m_right;
    up = m_up;
    front = m_front;
}

void Camera::getFrustum(float& rightMin, float& rightMax, float& upMin, float& upMax, float& frontMin, float& frontMax) {
	rightMin = m_rightMin;
	rightMax = m_rightMax;
	upMin = m_upMin;
	upMax = m_upMax;
	frontMin = m_frontMin;
	frontMax = m_frontMax;
}

void Camera::getFrustum(float& upFovDegrees, float& aspectRatio, float& frontMin, float& frontMax) {
    upFovDegrees = m_upFovDegrees;
    aspectRatio = m_aspectRatio;
    frontMin = m_frontMin;
    frontMax = m_frontMax;
}

void Camera::getSize(int& screenWidth, int& screenHeight) {
	screenWidth = m_rightMax - m_rightMin;
	screenHeight = m_upMax - m_upMin;
}

Camera::Type Camera::getType() {
	return m_type;
}

Vec3 Camera::getPosition() {
	return m_position;
}

Mat4 Camera::getPreViewMatrix() {
    return m_preViewMatrix;
}

Mat4 Camera::getPostProjectionMatrix() {
    return m_postProjectionMatrix;
}

Mat4 Camera::getViewMatrix() {
	return m_viewMatrix;
}

Mat3 Camera::getViewNormMatrix() {
	return Mat3(m_viewMatrix).inverse().transpose();
}

Mat4 Camera::getViewProjectionMatrix() {
	if (m_type == Camera::Orthographic) {
		return m_viewOrthographicProjectionMatrix;
	} else {
		return m_viewPerspectiveProjectionMatrix;
	}
}

Mat4 Camera::getProjectionMatrix() {
	if (m_type == Camera::Orthographic) {
		return m_orthographicProjectionMatrix;
	} else {
		return m_perspectiveProjectionMatrix;
	}
}

bool Camera::boundInFrustum(const Bound3& bound) const {
	// Reference
	// http://www.iquilezles.org/www/articles/frustumcorrect/frustumcorrect.htm

	const float band = 0.0f;
	Vec3 boundMin = bound.getCornerMin();
	Vec3 boundMax = bound.getCornerMax();

	// check box outside/inside of frustum
	for (unsigned int i = 0; i < 6; ++i) {
		int out = 0;
		out += ((dot(m_planes[i], Vec4(boundMin.x, boundMin.y, boundMin.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMax.x, boundMin.y, boundMin.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMin.x, boundMax.y, boundMin.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMax.x, boundMax.y, boundMin.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMin.x, boundMin.y, boundMax.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMax.x, boundMin.y, boundMax.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMin.x, boundMax.y, boundMax.z, 1.0f)) < -band) ? 1 : 0);
		out += ((dot(m_planes[i], Vec4(boundMax.x, boundMax.y, boundMax.z, 1.0f)) < -band) ? 1 : 0);
		if (out == 8) return 0;
	}
#if defined UNOPTIMIZED
	// check frustum outside/inside box
	int out;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].x > (boundMax.x + band)) ? 1 : 0); if (out == 8) return 0;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].x < (boundMin.x - band)) ? 1 : 0); if (out == 8) return 0;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].y > (boundMax.y + band)) ? 1 : 0); if (out == 8) return 0;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].y < (boundMin.y - band)) ? 1 : 0); if (out == 8) return 0;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].z > (boundMax.z + band)) ? 1 : 0); if (out == 8) return 0;
	out = 0; for(int i = 0; i < 8; ++i) out += ((m_points[i].z < (boundMin.z - band)) ? 1 : 0); if (out == 8) return 0;
#endif // defined UNOPTIMIZED
	return 1;
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

    if (m_type == Camera::Orthographic) {
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
    } else if (m_type == Camera::Perspective) {
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
        m_perspectiveProjectionMatrix.d22 = m_frontMax * invFDiff;
        m_perspectiveProjectionMatrix.d23 = -m_frontMin * m_frontMax * invFDiff;
        m_perspectiveProjectionMatrix.d30 = 0.0f;
        m_perspectiveProjectionMatrix.d31 = 0.0f;
        m_perspectiveProjectionMatrix.d32 = 1.0f;
        m_perspectiveProjectionMatrix.d33 = 0.0f;
    }
}

void Camera::updateViewProjectionMatrix() {
    if (m_type == Camera::Orthographic) {
        m_viewOrthographicProjectionMatrix = m_orthographicProjectionMatrix * m_viewMatrix;
    } else if (m_type == Camera::Perspective) {
        m_viewPerspectiveProjectionMatrix = m_perspectiveProjectionMatrix * m_viewMatrix;
    }

    if (m_postProjectionMatrix != Mat4::identity) {
        if (m_type == Camera::Orthographic) {
            m_viewOrthographicProjectionMatrix = m_postProjectionMatrix * m_viewOrthographicProjectionMatrix;
        } else if (m_type == Camera::Perspective) {
            m_viewPerspectiveProjectionMatrix = m_postProjectionMatrix * m_viewPerspectiveProjectionMatrix;
        }
    }

    if (m_preViewMatrix != Mat4::identity) {
        if (m_type == Camera::Orthographic) {
            m_viewOrthographicProjectionMatrix = m_viewOrthographicProjectionMatrix * m_preViewMatrix;
        } else if (m_type == Camera::Perspective) {
            m_viewPerspectiveProjectionMatrix = m_viewPerspectiveProjectionMatrix * m_preViewMatrix;
        }
    }
}

void Camera::updateFrustumPlanesAndPoints() {
	// Reference
	// http://www.iquilezles.org/www/articles/frustumcorrect/frustumcorrect.htm

	Mat4 matrix;
	if (m_type == Camera::Orthographic) {
		matrix = m_viewOrthographicProjectionMatrix.transpose();
	} else if (m_type == Camera::Perspective) {
		matrix = m_viewPerspectiveProjectionMatrix.transpose();
	}

	m_planes[0].x = matrix.data[12] - matrix.data[ 0];
	m_planes[0].y = matrix.data[13] - matrix.data[ 1];
	m_planes[0].z = matrix.data[14] - matrix.data[ 2];
	m_planes[0].w = matrix.data[15] - matrix.data[ 3];
	m_planes[1].x = matrix.data[12] + matrix.data[ 0];
	m_planes[1].y = matrix.data[13] + matrix.data[ 1];
	m_planes[1].z = matrix.data[14] + matrix.data[ 2];
	m_planes[1].w = matrix.data[15] + matrix.data[ 3];
	m_planes[2].x = matrix.data[12] + matrix.data[ 4];
	m_planes[2].y = matrix.data[13] + matrix.data[ 5];
	m_planes[2].z = matrix.data[14] + matrix.data[ 6];
	m_planes[2].w = matrix.data[15] + matrix.data[ 7];
	m_planes[3].x = matrix.data[12] - matrix.data[ 4];
	m_planes[3].y = matrix.data[13] - matrix.data[ 5];
	m_planes[3].z = matrix.data[14] - matrix.data[ 6];
	m_planes[3].w = matrix.data[15] - matrix.data[ 7];
	m_planes[4].x = matrix.data[12] - matrix.data[ 8];
	m_planes[4].y = matrix.data[13] - matrix.data[ 9];
	m_planes[4].z = matrix.data[14] - matrix.data[10];
	m_planes[4].w = matrix.data[15] - matrix.data[11];
	m_planes[5].x = matrix.data[12] + matrix.data[ 8];
	m_planes[5].y = matrix.data[13] + matrix.data[ 9];
	m_planes[5].z = matrix.data[14] + matrix.data[10];
	m_planes[5].w = matrix.data[15] + matrix.data[11];

	m_planes[0] /= m_planes[0].project().norm();
	m_planes[1] /= m_planes[1].project().norm();
	m_planes[2] /= m_planes[2].project().norm();
	m_planes[3] /= m_planes[3].project().norm();
	m_planes[4] /= m_planes[4].project().norm();
	m_planes[5] /= m_planes[5].project().norm();

#if defined UNOPTIMIZED
	m_points[0] = pointFromPlanes(m_planes[1], m_planes[2], m_planes[4]);
	m_points[1] = pointFromPlanes(m_planes[0], m_planes[2], m_planes[4]);
	m_points[2] = pointFromPlanes(m_planes[0], m_planes[3], m_planes[4]);
	m_points[3] = pointFromPlanes(m_planes[1], m_planes[3], m_planes[4]);
	m_points[4] = pointFromPlanes(m_planes[1], m_planes[2], m_planes[5]); // left,  bottom, near = -right, -top, near
	m_points[5] = pointFromPlanes(m_planes[0], m_planes[2], m_planes[5]); // right, bottom, near =  right, -top, near
	m_points[6] = pointFromPlanes(m_planes[0], m_planes[3], m_planes[5]); // right, top,    near
	m_points[7] = pointFromPlanes(m_planes[1], m_planes[3], m_planes[5]); // left,  top,    near = -right,  top, near
#endif // defined UNOPTIMIZED
}
