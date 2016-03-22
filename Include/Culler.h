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

	void setFrustum();
    void cull(Octree* octree, std::list<Spatial*>& spatials);

private:
	enum Result {
		Inside,
		Outside,
	};
	Result test(Octree* octree);

	Camera* m_camera;

	Plane m_plane[6];
};

#endif /* Culler_h */
