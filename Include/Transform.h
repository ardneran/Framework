//
//  Transform.h
//  Framework
//
//  Created by Narendra Umate on 8/24/15.
//
//

#ifndef Framework_Transform_h
#define Framework_Transform_h

#include "Matrix.h"

class Transform : public Mat4 {
public:
	Transform();
	~Transform();

	Transform operator*(const Transform &transform);
};

#endif
