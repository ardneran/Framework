//
//  Culler.h
//  Framework
//
//  Created by Narendra Umate on 12/31/15.
//
//

#ifndef Culler_h
#define Culler_h

#include <list>
#include "Camera.h"
#include "Octree.h"
#include "Spatial.h"

class Culler {
public:
    Culler();
    virtual ~Culler();

    std::list<Spatial*> cull(Camera* camera, Octree* octree);
};

#endif /* Culler_h */
