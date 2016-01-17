//
//  ObjMeshLoader.cpp
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#include "ObjMeshLoader.h"

ObjMeshLoader::ObjMeshLoader() {
}

ObjMeshLoader::~ObjMeshLoader() {
}

std::list<Visual*> ObjMeshLoader::load(const std::string& filepath, const std::string& filebase) {
    std::list<Visual*> visuals;
    std::vector<tinyobj::shape_t> oldshapes;
    std::vector<tinyobj::material_t> oldmaterials;
    std::string error;
    if (LoadObj(oldshapes, oldmaterials, error, filepath.c_str(), filebase.c_str())) {
        std::vector<tinyobj::shape_t> newshapes;
        std::vector<tinyobj::material_t> newmaterials;
        SortShapes(newshapes, newmaterials, oldshapes, oldmaterials);
        for (std::vector<tinyobj::shape_t>::iterator it = newshapes.begin(); it != newshapes.end(); ++it) {
            Visual* visual = new Visual();
            visual->getVertexBuffer()->initialize(it->mesh.positions, it->mesh.normals, it->mesh.texcoords);
            visual->getIndexBuffer()->initialize(it->mesh.indices);
            visual->setModelBoundingBox(it->mesh.positions);
            visuals.push_back(visual);
        }
    } else {
        printf("%s", error.c_str());
    }
    return visuals;
}
