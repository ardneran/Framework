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

    virtual void update();
    virtual void setTranslate(const Vec3& translate);
    virtual void setRotate(const Quat& rotate);
    virtual void setScale(const Vec3& scale);

    Vec3 getTranslate();
    Quat getRotate();
    Vec3 getScale();

    BoundingBox getWorldBoundingBox();

protected:
    virtual void updateWorldBoundingBox();

    BoundingBox m_worldBoundingBox;
    Transform m_worldTransform;
};

#endif /* Spatial_h */
