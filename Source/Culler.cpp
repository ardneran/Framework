//
//  Culler.cpp
//  Framework
//
//  Created by Narendra Umate on 12/31/15.
//
//

#include "Culler.h"

Culler::Culler(Camera* camera)
: m_camera(camera) {
}

Culler::~Culler() {
}

void Culler::setFrustum() {
	if (!m_camera) {
		return;
	}

	Vec3 position;
	Vec3 right;
	Vec3 up;
	Vec3 front;
	m_camera->getFrame(position, right, up, front);

	float rightMin;
	float rightMax;
	float upMin;
	float upMax;
	float frontMin;
	float frontMax;
	m_camera->getFrustum(rightMin, rightMax, upMin, upMax, frontMin, frontMax);

	float fMin2 = frontMin * frontMin;
	float uMin2 = upMin * upMin;
	float uMax2 = upMax * upMax;
	float rMin2 = rightMin * rightMin;
	float rMax2 = rightMax * rightMax;

	float dirDotEye = dot(position, front);

	// Update the near plane.
	m_plane[Camera::VF_DMIN].SetNormal(front);
	m_plane[Camera::VF_DMIN].SetConstant(dirDotEye + frontMin);

	// Update the far plane.
	m_plane[Camera::VF_DMAX].SetNormal(-front);
	m_plane[Camera::VF_DMAX].SetConstant(-(dirDotEye + frontMax));

	// Update the bottom plane
	float invLength = invsqrt(fMin2 + uMin2);
	float c0 = -upMin*invLength;  // D component
	float c1 = +frontMin*invLength;  // U component
	Vec3 normal = front * c0 + up * c1;
	float constant = dot(position, normal);
	m_plane[Camera::VF_UMIN].SetNormal(normal);
	m_plane[Camera::VF_UMIN].SetConstant(constant);

	// Update the top plane.
	invLength = invsqrt(fMin2 + uMax2);
	c0 = +upMax*invLength;  // D component
	c1 = -frontMin*invLength;  // U component
	normal = front * c0 + up * c1;
	constant = dot(position, normal);
	m_plane[Camera::VF_UMAX].SetNormal(normal);
	m_plane[Camera::VF_UMAX].SetConstant(constant);

	// Update the left plane.
	invLength = invsqrt(fMin2 + rMin2);
	c0 = -rightMin*invLength;  // D component
	c1 = +frontMin*invLength;  // R component
	normal = front * c0 + right * c1;
	constant = dot(position, normal);
	m_plane[Camera::VF_RMIN].SetNormal(normal);
	m_plane[Camera::VF_RMIN].SetConstant(constant);

	// Update the right plane.
	invLength = invsqrt(fMin2 + rMax2);
	c0 = +rightMax*invLength;  // D component
	c1 = -frontMin*invLength;  // R component
	normal = front * c0 + right * c1;
	constant = dot(position, normal);
	m_plane[Camera::VF_RMAX].SetNormal(normal);
	m_plane[Camera::VF_RMAX].SetConstant(constant);
}

void Culler::cull(Octree* octree, std::list<Spatial*>& spatials) {
	if (m_camera && octree) {
		Result result = test(octree);
		if (result == Outside) {
			return;
		}
		else if (result == Inside) {
			octree->collectTree(spatials);
		}
		else {
			octree->collectNode(spatials);
			for (int i = 0; i < 8; ++i) {
				cull(octree->node(i), spatials);
			}
		}
	}
}

Culler::Result Culler::test(Octree* octree) {
	// TODO fix this function so it actually does the thing it is supposed to do
	return Inside;
}

