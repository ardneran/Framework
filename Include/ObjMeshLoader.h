//
//  ObjMeshLoader.h
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#ifndef ObjMeshLoader_h
#define ObjMeshLoader_h

#include <list>
#include "MeshLoader.h"
#include "tiny_obj_loader.h"
#include "tiny_obj_helper.h"

class ObjMeshLoader : public MeshLoader {
public:
    ObjMeshLoader();
    virtual ~ObjMeshLoader();

    std::list<VisualSpatial*> load(const std::string& filepath, const std::string& filebase);
    
private:
    void loadMaterial(const tinyobj::material_t& material);
};

#endif /* ObjMeshLoader_h */
