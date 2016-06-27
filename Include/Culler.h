//
//  Culler.h
//  Framework
//
//  Created by Narendra Umate on 12/31/15.
//
//

#ifndef Culler_h
#define Culler_h

#include <list>
#include "Camera.h"
#include "Octree.h"
#include "Plane.h"
#include "Spatial.h"

class Culler {
public:
    Culler(Camera* camera);
    virtual ~Culler();

	void updateFrustum();
    void cull(Octree* octree, std::list<Spatial*>& spatials);

	enum Result {
		In,
		Out,
		Part
	};

	Result test(const BoundingBox& boundingBox);
	Result test(const Vec3& point);

private:
	Camera* m_camera;
	Mat4 m_ovpt;

	enum CullerPlane {
		CP_FMIN,
		CP_FMAX,
		CP_UMIN,
		CP_UMAX,
		CP_RMIN,
		CP_RMAX,
	};

	Plane m_plane[6];
};

#endif /* Culler_h */
