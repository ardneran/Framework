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

    BoundingBox getWorldBoundingBox();
    BoundingBox getLocalBoundingBox();
    Transform getWorldTransform();
    Transform getLocalTransform();

    virtual void update();

protected:
    BoundingBox m_worldBoundingBox;
    BoundingBox m_localBoundingBox;
    Transform m_worldTransform;
    Transform m_localTransform;
};

#endif /* Spatial_h */
