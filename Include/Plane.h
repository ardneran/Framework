//
//  Plane.h
//  Framework
//
//  Created by Narendra Umate on 3/22/16.
//
//

#ifndef Plane_h
#define Plane_h

#include "Vector.h"

class Plane {
public:
	Plane();
	~Plane();

	void SetNormal(const Vec3& normal);
	void SetConstant(const float& constant);
};

#endif /* Plane_h */
