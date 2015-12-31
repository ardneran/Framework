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
    Visual();
    virtual ~Visual() = 0;

    bool updateModelBounds();

protected:
    virtual bool updateWorldBounds();

private:
    BoundingBox m_modelBoundingBox;
};

#endif /* Visual_h */
