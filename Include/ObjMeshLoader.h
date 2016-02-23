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
    void loadMaterial(VisualSpatial* const visual, const tinyobj::material_t& material, const std::string& filebase);
	void loadTexture(const std::string& base, const std::string& name, Texture2D& texture);
};

#endif /* ObjMeshLoader_h */
