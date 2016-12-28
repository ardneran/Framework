//
//  Frustum.cpp
//  
//
//  Created by Narendra Umate on 4/13/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#include "Frustum.h"

////////////////////////////////////////////////////////////////////////////////

Frustum2::Frustum2() {
}

Frustum2::~Frustum2() {
}

void Frustum2::setMatrix(const Mat3& matrix) {
	// TODO
}

////////////////////////////////////////////////////////////////////////////////

Frustum3::Frustum3() {
}

Frustum3::~Frustum3() {
}

void Frustum3::setMatrix(const Mat4& matrix) {
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

	m_points[0] = pointFromPlanes(m_planes[1], m_planes[2], m_planes[4]);
	m_points[1] = pointFromPlanes(m_planes[0], m_planes[2], m_planes[4]);
	m_points[2] = pointFromPlanes(m_planes[0], m_planes[3], m_planes[4]);
	m_points[3] = pointFromPlanes(m_planes[1], m_planes[3], m_planes[4]);
	m_points[4] = pointFromPlanes(m_planes[1], m_planes[2], m_planes[5]); // left,  bottom, near = -right, -top, near
	m_points[5] = pointFromPlanes(m_planes[0], m_planes[2], m_planes[5]); // right, bottom, near =  right, -top, near
	m_points[6] = pointFromPlanes(m_planes[0], m_planes[3], m_planes[5]); // right, top,    near
	m_points[7] = pointFromPlanes(m_planes[1], m_planes[3], m_planes[5]); // left,  top,    near = -right,  top, near
}

////////////////////////////////////////////////////////////////////////////////
