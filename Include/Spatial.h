//
//  Spatial.h
//  Framework
//
//  Created by Narendra Umate on 8/23/15.
//
//

#ifndef Spatial_h
#define Spatial_h

#include "BoundingBox.h"
#include "Transform.h"

class Spatial {
public:
    Spatial();
    virtual ~Spatial() = 0;

    BoundingBox getBoundingBox();
    Transform getTransform();

    virtual void update();

protected:
    BoundingBox m_worldBoundingBox;
    Transform m_worldTransform;
};

#endif /* Spatial_h */
