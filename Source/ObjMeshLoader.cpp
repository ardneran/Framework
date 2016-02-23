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

std::list<VisualSpatial*> ObjMeshLoader::load(const std::string& filepath, const std::string& filebase) {
    std::list<VisualSpatial*> visuals;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;
    if (LoadObj(shapes, materials, error, filepath.c_str(), filebase.c_str())) {
        for (std::vector<tinyobj::shape_t>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            VisualSpatial* visual = new VisualSpatial();
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

void ObjMeshLoader::loadMaterial(const tinyobj::material_t& material) {
    // TODO
}
