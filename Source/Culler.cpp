//
//  Culler.cpp
//  Framework
//
//  Created by Narendra Umate on 12/31/15.
//
//

#include "Culler.h"

Culler::Culler(Camera* camera)
: m_camera(camera)
, m_ovpt(Mat4::identity) {
}

Culler::~Culler() {
}

void Culler::updateFrustum() {
	// http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
	// Create the frustum matrix from the view matrix and projection matrix.
	// Transpose is OpenGL hack so that indices match DirectX matrix indices.
	if (m_camera) {
		Mat4 vpt = m_camera->getViewProjectionMatrix().transpose();
		if (m_ovpt != vpt) {
			m_ovpt = vpt;

			// near
			m_plane[CP_FMIN].m_normal.x = vpt.d03 + vpt.d02;
			m_plane[CP_FMIN].m_normal.y = vpt.d13 + vpt.d12;
			m_plane[CP_FMIN].m_normal.z = vpt.d23 + vpt.d22;
			m_plane[CP_FMIN].m_constant = vpt.d33 + vpt.d32;

			// far
			m_plane[CP_FMAX].m_normal.x = vpt.d03 - vpt.d02;
			m_plane[CP_FMAX].m_normal.y = vpt.d13 - vpt.d12;
			m_plane[CP_FMAX].m_normal.z = vpt.d23 - vpt.d22;
			m_plane[CP_FMAX].m_constant = vpt.d33 - vpt.d32;

			// left
			m_plane[CP_RMIN].m_normal.x = vpt.d03 + vpt.d00;
			m_plane[CP_RMIN].m_normal.y = vpt.d13 + vpt.d10;
			m_plane[CP_RMIN].m_normal.z = vpt.d23 + vpt.d20;
			m_plane[CP_RMIN].m_constant = vpt.d33 + vpt.d30;

			// right
			m_plane[CP_RMAX].m_normal.x = vpt.d03 - vpt.d00;
			m_plane[CP_RMAX].m_normal.y = vpt.d13 - vpt.d10;
			m_plane[CP_RMAX].m_normal.z = vpt.d23 - vpt.d20;
			m_plane[CP_RMAX].m_constant = vpt.d33 - vpt.d30;

			// bottom
			m_plane[CP_UMIN].m_normal.x = vpt.d03 + vpt.d01;
			m_plane[CP_UMIN].m_normal.y = vpt.d13 + vpt.d11;
			m_plane[CP_UMIN].m_normal.z = vpt.d23 + vpt.d21;
			m_plane[CP_UMIN].m_constant = vpt.d33 + vpt.d31;

			// top
			m_plane[CP_UMAX].m_normal.x = vpt.d03 - vpt.d01;
			m_plane[CP_UMAX].m_normal.y = vpt.d13 - vpt.d11;
			m_plane[CP_UMAX].m_normal.z = vpt.d23 - vpt.d21;
			m_plane[CP_UMAX].m_constant = vpt.d33 - vpt.d31;

			// normalize
			m_plane[CP_RMIN].normalize();
			m_plane[CP_RMAX].normalize();
			m_plane[CP_UMIN].normalize();
			m_plane[CP_UMAX].normalize();
			m_plane[CP_FMIN].normalize();
			m_plane[CP_FMAX].normalize();
		}
	}
}

void Culler::cull(Octree* octree, std::list<Spatial*>& spatials) {
	if (m_camera && octree) {
		switch (test(octree->boundingBox()))
		{
			case In:
				{
					octree->collectTree(spatials);
				}
				break;
			case Out:
				break;
			case Part:
				{
					/*
					std::list<Spatial*> currentSpatials;
					octree->collectNode(currentSpatials);
					for (auto currentSpatial : currentSpatials) {
						if (test(currentSpatial->getWorldBoundingBox()) != Out) {
							spatials.push_back(currentSpatial);
						}
					}
					*/
					octree->collectNode(spatials);
					for (int i = 0; i < 8; ++i) {
						cull(octree->node(i), spatials);
					}
				}
				break;
		}
	}
}

Culler::Result Culler::test(const Bound3& boundingBox) {
	int out = 0;

	Vec3 min = boundingBox.getCornerMin();
	Vec3 max = boundingBox.getCornerMax();

	out += (test(Vec3(min.x, min.y, min.z)) == Out);
	out += (test(Vec3(max.x, min.y, min.z)) == Out);
	out += (test(Vec3(min.x, max.y, min.z)) == Out);
	out += (test(Vec3(max.x, max.y, min.z)) == Out);
	out += (test(Vec3(min.x, min.y, max.z)) == Out);
	out += (test(Vec3(max.x, min.y, max.z)) == Out);
	out += (test(Vec3(min.x, max.y, max.z)) == Out);
	out += (test(Vec3(max.x, max.y, max.z)) == Out);

	if (out == 0) {
		return In;
	} else if (out == 8) {
		return Out;
	} else {
		return Part;
	}
}

Culler::Result Culler::test(const Vec3& point) {
	if (m_plane[0].distance(point) < 0) return Out;
	if (m_plane[1].distance(point) < 0) return Out;
	if (m_plane[2].distance(point) < 0) return Out;
	if (m_plane[3].distance(point) < 0) return Out;
	if (m_plane[4].distance(point) < 0) return Out;
	if (m_plane[5].distance(point) < 0) return Out;
	return In;
}
