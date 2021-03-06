//
//  MeshLoader.h
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#ifndef MeshLoader_h
#define MeshLoader_h

#include <list>

#include "VisualSpatial.h"
#include "TextureManager.h"

class MeshLoader {
public:
    MeshLoader();
    virtual ~MeshLoader() = 0;

    virtual std::list<VisualSpatial*> load(const std::string& filepath, const std::string& filebase) = 0;
    
protected:
    TextureManager* m_textureManager;
};

#endif /* MeshLoader_h */
