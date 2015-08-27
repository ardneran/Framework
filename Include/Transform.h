//
//  Transform.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef Framework_Transform_h
#define Framework_Transform_h

#include "Quaternion.h"
#include "Matrix.h"

class Transform {
public:
	Transform();
	~Transform();

	Transform operator*(const Transform& other);
	Transform operator*=(const Transform& other);

protected:
	Quat m_rotation;
	Vec3 m_translation;
	Vec3 m_scale;
};

#endif
