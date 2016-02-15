//
//  MeshLoader.h
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#ifndef MeshLoader_h
#define MeshLoader_h

#include "VisualSpatial.h"

class MeshLoader {
public:
    MeshLoader();
    virtual ~MeshLoader() = 0;

    virtual std::list<VisualSpatial*> load(const std::string& filepath, const std::string& filebase) = 0;
};

#endif /* MeshLoader_h */
