//
//  Frustum.h
//
//
//  Created by Narendra Umate on 4/13/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Frustum__
#define __Frustum__

#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////

class Frustum2 {
public:
	Frustum2();
	~Frustum2();

	void setMatrix(const Mat3& matrix);

	Vec3 m_lines[4];
	Vec3 m_points[4];
};

////////////////////////////////////////////////////////////////////////////////

class Frustum3 {
public:
	Frustum3();
	~Frustum3();

	void setMatrix(const Mat4& matrix);

	Vec4 m_planes[6];
	Vec3 m_points[8];
};

#endif /* defined(__Frustum__) */

////////////////////////////////////////////////////////////////////////////////
