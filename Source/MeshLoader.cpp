//
//  MeshLoader.cpp
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#include "MeshLoader.h"

MeshLoader::MeshLoader()
: m_textureManager(new TextureManager()){
}

MeshLoader::~MeshLoader() {
    delete m_textureManager;
}

std::list<VisualSpatial*> MeshLoader::load(const std::string& filepath, const std::string& filebase) {
    std::list<VisualSpatial*> visuals;
    return visuals;
}
