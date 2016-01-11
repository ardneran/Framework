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

    enum Space {
        Local,
        World
    };

    void setBoundingBox(const Space& space, const BoundingBox& boundingBox);
    void setTranslate(const Space& space, const Vec3& translate);
    void setRotate(const Space& space, const Quat& rotate);
    void setScale(const Space& space, const Vec3& scale);

    BoundingBox getBoundingBox(const Space& space);
    Vec3 getTranslate(const Space& space);
    Quat getRotate(const Space& space);
    Vec3 getScale(const Space& space);

private:
    BoundingBox m_worldBoundingBox;
    BoundingBox m_localBoundingBox;
    Transform m_worldTransform;
    Transform m_localTransform;
};

#endif /* Spatial_h */
