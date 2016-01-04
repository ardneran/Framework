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

    void setParent(Spatial* const parent);
    Spatial* getParent() const;
    void update(const bool& initiator = true);

    Transform m_localTransform;
    Transform m_worldTransform;
    BoundingBox m_worldBoundingBox;

protected:
    virtual void updateWorldTransforms();
    virtual bool updateWorldBounds();
    void propagateWorldBoundsToParent();

private:
    Spatial* m_parent;
};

#endif /* Spatial_h */
