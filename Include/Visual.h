//
//  Visual.h
//  Framework
//
//  Created by Narendra Umate on 8/28/15.
//
//

#ifndef Visual_h
#define Visual_h

#include "Spatial.h"

class Visual : public Spatial {
public:
    virtual ~Visual();
    Visual();
    bool updateModelBounds();

    BoundingBox m_modelBoundingBox;

protected:
    virtual bool updateWorldBounds();
};

#endif /* Visual_h */
