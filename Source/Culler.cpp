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
, m_oldViewProjectionMatrix(Mat4::identity) {
}

Culler::~Culler() {
}

void Culler::updateFrustum() {
	// http://gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
	if (m_camera) {
		Mat4 viewProjectionMatrix = m_camera->getViewProjectionMatrix();
		if (m_oldViewProjectionMatrix != viewProjectionMatrix) {
			m_oldViewProjectionMatrix = viewProjectionMatrix;

			// left
			m_plane[CP_RMIN].m_normal.x = viewProjectionMatrix.d03 + viewProjectionMatrix.d00;
			m_plane[CP_RMIN].m_normal.y = viewProjectionMatrix.d13 + viewProjectionMatrix.d10;
			m_plane[CP_RMIN].m_normal.z = viewProjectionMatrix.d23 + viewProjectionMatrix.d20;
			m_plane[CP_RMIN].m_constant = viewProjectionMatrix.d33 + viewProjectionMatrix.d30;

			// right
			m_plane[CP_RMAX].m_normal.x = viewProjectionMatrix.d03 - viewProjectionMatrix.d00;
			m_plane[CP_RMAX].m_normal.y = viewProjectionMatrix.d13 - viewProjectionMatrix.d10;
			m_plane[CP_RMAX].m_normal.z = viewProjectionMatrix.d23 - viewProjectionMatrix.d20;
			m_plane[CP_RMAX].m_constant = viewProjectionMatrix.d33 - viewProjectionMatrix.d30;

			// bottom
			m_plane[CP_UMIN].m_normal.x = viewProjectionMatrix.d03 + viewProjectionMatrix.d01;
			m_plane[CP_UMIN].m_normal.y = viewProjectionMatrix.d13 + viewProjectionMatrix.d11;
			m_plane[CP_UMIN].m_normal.z = viewProjectionMatrix.d23 + viewProjectionMatrix.d21;
			m_plane[CP_UMIN].m_constant = viewProjectionMatrix.d33 + viewProjectionMatrix.d31;

			// top
			m_plane[CP_UMAX].m_normal.x = viewProjectionMatrix.d03 - viewProjectionMatrix.d01;
			m_plane[CP_UMAX].m_normal.y = viewProjectionMatrix.d13 - viewProjectionMatrix.d11;
			m_plane[CP_UMAX].m_normal.z = viewProjectionMatrix.d23 - viewProjectionMatrix.d21;
			m_plane[CP_UMAX].m_constant = viewProjectionMatrix.d33 - viewProjectionMatrix.d31;

			// near
			m_plane[CP_FMIN].m_normal.x = viewProjectionMatrix.d03 + viewProjectionMatrix.d02;
			m_plane[CP_FMIN].m_normal.y = viewProjectionMatrix.d13 + viewProjectionMatrix.d12;
			m_plane[CP_FMIN].m_normal.z = viewProjectionMatrix.d23 + viewProjectionMatrix.d22;
			m_plane[CP_FMIN].m_constant = viewProjectionMatrix.d33 + viewProjectionMatrix.d32;

			// far
			m_plane[CP_FMAX].m_normal.x = viewProjectionMatrix.d03 - viewProjectionMatrix.d02;
			m_plane[CP_FMAX].m_normal.y = viewProjectionMatrix.d13 - viewProjectionMatrix.d12;
			m_plane[CP_FMAX].m_normal.z = viewProjectionMatrix.d23 - viewProjectionMatrix.d22;
			m_plane[CP_FMAX].m_constant = viewProjectionMatrix.d33 - viewProjectionMatrix.d32;

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
					octree->collectNode(spatials);
					for (int i = 0; i < 8; ++i) {
						cull(octree->node(i), spatials);
					}
				}
				break;
		}
	}
}

Culler::Result Culler::test(const BoundingBox& boundingBox) {
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
	for (int i = 0; i < 6; i++)
	{
		if (m_plane[i].distance(point) < 0)
		{
			return Out;
		}
	}
	return In;
}
