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

	void setNormal(const Vec3& normal);
	Vec3 getNormal();
	void setConstant(const float& constant);
	float getConstant();

private:
	Vec3 m_normal;
	float m_constant;
};

#endif /* Plane_h */
