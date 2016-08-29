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
            VisualSpatial* visual = new VisualSpatial(it->mesh.positions, it->mesh.normals, it->mesh.texcoords, it->mesh.indices);

			// Assume that every shape has only one material.
			loadMaterial(visual, materials[it->mesh.material_ids[0]], filebase);

            visual->setModelBoundingBox(it->mesh.positions);
            visuals.push_back(visual);
        }
    } else {
        printf("%s", error.c_str());
    }
    return visuals;
}

void ObjMeshLoader::loadMaterial(VisualSpatial* const visual, const tinyobj::material_t& material, const std::string& filebase) {
	Material* currentMaterial = visual->getMaterial();

	// TODO Optimize the array copies.
	currentMaterial->ambient[0] = material.ambient[0];
	currentMaterial->ambient[1] = material.ambient[1];
	currentMaterial->ambient[2] = material.ambient[2];
	currentMaterial->diffuse[0] = material.diffuse[0];
	currentMaterial->diffuse[1] = material.diffuse[1];
	currentMaterial->diffuse[2] = material.diffuse[2];
	currentMaterial->specular[0] = material.specular[0];
	currentMaterial->specular[1] = material.specular[1];
	currentMaterial->specular[2] = material.specular[2];
	currentMaterial->transmittance[0] = material.transmittance[0];
	currentMaterial->transmittance[1] = material.transmittance[1];
	currentMaterial->transmittance[2] = material.transmittance[2];
	currentMaterial->emission[0] = material.emission[0];
	currentMaterial->emission[1] = material.emission[1];
	currentMaterial->emission[2] = material.emission[2];

	currentMaterial->shininess = material.shininess;
	currentMaterial->ior = material.ior;
	currentMaterial->dissolve = material.dissolve;
	currentMaterial->illum = material.illum;
	currentMaterial->dummy = material.dummy;

	loadTexture(filebase, material.ambient_texname, currentMaterial->ambient_texname);
	loadTexture(filebase, material.diffuse_texname, currentMaterial->diffuse_texname);
	loadTexture(filebase, material.specular_texname, currentMaterial->specular_texname);
	loadTexture(filebase, material.specular_highlight_texname, currentMaterial->specular_highlight_texname);
	loadTexture(filebase, material.bump_texname, currentMaterial->bump_texname);
	loadTexture(filebase, material.displacement_texname, currentMaterial->displacement_texname);
	loadTexture(filebase, material.alpha_texname, currentMaterial->alpha_texname);
}

void ObjMeshLoader::loadTexture(const std::string& base, const std::string& name, Texture2D*& texture) {
	if (!base.empty() && !name.empty()) {
        texture = m_textureManager->loadTexture(base + name);
    } else {
        texture = NULL;
    }
}
