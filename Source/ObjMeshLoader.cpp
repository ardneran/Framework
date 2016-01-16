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
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;
    if (LoadObj(shapes, materials, error, filepath.c_str(), filebase.c_str())) {
        for (std::vector<tinyobj::shape_t>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
            Visual* visual = new Visual();
            VertexBuffer* vb = visual->getVertexBuffer();
            vb->initialize(it->mesh.positions, it->mesh.normals, it->mesh.texcoords);
            IndexBuffer* ib = visual->getIndexBuffer();
            ib->initialize(it->mesh.indices);
            visuals.push_back(visual);
        }
    } else {
        printf("%s", error.c_str());
    }
    return visuals;
}
